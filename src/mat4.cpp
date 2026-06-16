#include <linalg/mat4.hpp>
#include <linalg/mat3.hpp>
#include <cmath> // for std::sqrt, etc. when you need it
#include <stdexcept> // for std::runtime_error if you choose to throw exceptions

namespace linalg {

    // implement constructor for Mat4
    Mat4::Mat4(double d[4][4]) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                data[i][j] = d[i][j];
            }
        }
    }

    Mat4 Mat4::identity() const {
        Mat4 I;
        for (int i = 0; i < 4; i++) {
            I.data[i][i] = 1.0;
        }
        return I;
    }

    Mat4 Mat4::transpose() const {
        Mat4 I;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                I.data[i][j] = data[j][i];
            }
        }
        return I;
    }

    Mat4 operator*(const Mat4& a, const Mat4& b) {
        Mat4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.data[i][j] = 0.0;
                for (int k = 0; k < 4; k++) {
                    result.data[i][j] += a.data[i][k] * b.data[k][j];
                }
            }
        }
        return result;
    }

    double determinant(const Mat4& m) {
        // For a 4x4 matrix, the determinant can be calculated using the rule of Sarrus or cofactor expansion.
        // Here we will use cofactor expansion along the first row.

        double det = 0.0;
        for (int col = 0; col < 4; col++) {
            Mat3 submatrix;
            for (int i = 1; i < 4; i++) {
                int subcol = 0;
                for (int j = 0; j < 4; j++) {
                    if (j == col) continue; // skip the current column
                    submatrix.data[i - 1][subcol] = m.data[i][j];
                    subcol++;
                }
            }
            double cofactor = ((col % 2 == 0) ? 1 : -1) * m.data[0][col] * determinant(submatrix);
            det += cofactor;
        }
        return det;
    }
}