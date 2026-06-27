#pragma once
#include <linalg/vec.hpp>
#include <cmath>
#include <stdexcept>

namespace linalg {

// A size- and type-generic matrix with R rows and C columns of type T (e.g.
// Mat<double, 3, 3> is equivalent in spirit to Mat3, Mat<double, 4, 4> to
// Mat4, and non-square sizes like Mat<double, 2, 3> are valid too).
// identity()/determinant()/inverse() are only meaningful for square
// matrices (R == C) and enforce that with static_assert / by construction.
template<typename T, int R, int C>
struct Mat {
    T data[R][C] = {};

    Mat() = default;

    Mat(const T (&arr)[R][C]) {
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                data[i][j] = arr[i][j];
            }
        }
    }

    static Mat<T, R, C> identity() {
        static_assert(R == C, "identity() is only defined for square matrices");
        Mat<T, R, C> result;
        for (int i = 0; i < R; i++) {
            result.data[i][i] = static_cast<T>(1);
        }
        return result;
    }

    Mat<T, C, R> transpose() const {
        Mat<T, C, R> result;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }
};

template<typename T, int R, int K, int C>
Mat<T, R, C> operator*(const Mat<T, R, K>& a, const Mat<T, K, C>& b) {
    Mat<T, R, C> result;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            T sum = static_cast<T>(0);
            for (int k = 0; k < K; k++) {
                sum += a.data[i][k] * b.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }
    return result;
}

template<typename T, int R, int C>
Vec<T, R> operator*(const Mat<T, R, C>& m, const Vec<T, C>& v) {
    Vec<T, R> result;
    for (int i = 0; i < R; i++) {
        T sum = static_cast<T>(0);
        for (int j = 0; j < C; j++) {
            sum += m.data[i][j] * v.data[j];
        }
        result.data[i] = sum;
    }
    return result;
}

// Builds the (N-1)x(N-1) submatrix obtained by removing row skipRow and
// column skipCol. Used by determinant()/inverse() for cofactor expansion.
template<typename T, int N>
Mat<T, N - 1, N - 1> submatrix(const Mat<T, N, N>& m, int skipRow, int skipCol) {
    Mat<T, N - 1, N - 1> result;
    int ri = 0;
    for (int i = 0; i < N; i++) {
        if (i == skipRow) continue;
        int rj = 0;
        for (int j = 0; j < N; j++) {
            if (j == skipCol) continue;
            result.data[ri][rj] = m.data[i][j];
            rj++;
        }
        ri++;
    }
    return result;
}

template<typename T, int N>
T determinant(const Mat<T, N, N>& m) {
    if constexpr (N == 1) {
        return m.data[0][0];
    } else {
        T det = static_cast<T>(0);
        for (int col = 0; col < N; col++) {
            T sign = (col % 2 == 0) ? static_cast<T>(1) : static_cast<T>(-1);
            det += sign * m.data[0][col] * determinant(submatrix(m, 0, col));
        }
        return det;
    }
}

template<typename T, int N>
Mat<T, N, N> inverse(const Mat<T, N, N>& m) {
    T det = determinant(m);
    if (std::abs(det) < static_cast<T>(1e-9)) {
        throw std::runtime_error("Matrix is not invertible");
    }

    Mat<T, N, N> result;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            T sign = ((row + col) % 2 == 0) ? static_cast<T>(1) : static_cast<T>(-1);
            T cofactor = sign * determinant(submatrix(m, row, col));
            result.data[col][row] = cofactor / det;  // transpose folded into the write
        }
    }
    return result;
}

}  // namespace linalg
