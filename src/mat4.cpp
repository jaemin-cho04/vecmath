#include <linalg/mat4.hpp>
#include <linalg/mat3.hpp>
#include <cmath> // for std::sqrt, etc. when you need it
#include <stdexcept> // for std::runtime_error if you choose to throw exceptions

namespace linalg {

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

    Mat4 Mat4::inverse() const {
        double det = determinant(*this);
        // bail out if matrix is singular
        if (std::abs(det) < 1e-9) {
            throw std::runtime_error("Matrix is not invertible");
        }

        Mat4 inv;
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                Mat3 submatrix;
                int subrow = 0;
                for (int i = 0; i < 4; i++) {
                    if (i == row) continue; // skip the current row
                    int subcol = 0;
                    for (int j = 0; j < 4; j++) {
                        if (j == col) continue; // skip the current column
                        submatrix.data[subrow][subcol] = data[i][j];
                        subcol++;   
                    }
                    subrow++;
                }
                inv.data[row][col] = determinant(submatrix) * ((row + col) % 2 == 0 ? 1 : -1);
            }
        }
        Mat4 adjugate = inv.transpose(); // transpose to get the cofactor matrix
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                inv.data[i][j] = adjugate.data[i][j] / det;
            }
        }
        return inv;
    }

    Mat4 fromRotationTranslation(const Mat3& rotation, const Vec3& translation) {
        Mat4 result = Mat4().identity();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result.data[i][j] = rotation.data[i][j];
            }
        }
        result.data[0][3] = translation.x;
        result.data[1][3] = translation.y;
        result.data[2][3] = translation.z;
        return result;
    }

    Vec3 operator*(const Mat4& m, const Vec3& v) {
        double x = m.data[0][0] * v.x + m.data[0][1] * v.y + m.data[0][2] * v.z + m.data[0][3];
        double y = m.data[1][0] * v.x + m.data[1][1] * v.y + m.data[1][2] * v.z + m.data[1][3];
        double z = m.data[2][0] * v.x + m.data[2][1] * v.y + m.data[2][2] * v.z + m.data[2][3];
        return Vec3(x, y, z);
    }
}