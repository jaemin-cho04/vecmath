#include <linalg/mat3.hpp>

#include <cmath> // for std::sqrt, etc. when you need it

namespace linalg {

    Mat3::Mat3(double d[3][3]) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                data[i][j] = d[i][j];
            }
        }
    }

    Mat3 Mat3::identity() const {
        Mat3 I;
        for (int i = 0; i < 3; i++) {
            I.data[i][i] = 1.0;
        }
        return I;
    }

    Mat3 Mat3::transpose() const {
        Mat3 T;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                T.data[j][i] = data[i][j];
            }
        }
        return T;
    }

    Mat3 operator*(const Mat3& a, const Mat3& b) {
        Mat3 result;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result.data[i][j] = 0.0;
                for (int k = 0; k < 3; k++) {
                    result.data[i][j] += a.data[i][k] * b.data[k][j];
                }
            }
        }
        return result;
    }

    double determinant(const Mat3& m) {
        // For a 3x3 matrix:
        // |a b c|
        // |d e f|
        // |g h i|
        // det = a(ei - fh) - b(di - fg) + c(dh - eg)

        double det = m.data[0][0] * (m.data[1][1] * m.data[2][2] - m.data[1][2] * m.data[2][1]) -
                     m.data[0][1] * (m.data[1][0] * m.data[2][2] - m.data[1][2] * m.data[2][0]) +
                     m.data[0][2] * (m.data[1][0] * m.data[2][1] - m.data[1][1] * m.data[2][0]);
        return det;
    }

}