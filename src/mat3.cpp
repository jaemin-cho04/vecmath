#include <linalg/mat3.hpp>

#include <cmath> // for std::sqrt, etc. when you need it

#include <stdexcept> // for std::runtime_error if you choose to throw exceptions

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

    Mat3 Mat3::inverse() const {
        double det = determinant(*this);
        if (std::abs(det) < 1e-9) {
            // Handle non-invertible case as you see fit (e.g., throw an exception, return identity, etc.)
            throw std::runtime_error("Matrix is not invertible");
        }

        // Step 1: compute the cofactor matrix
        Mat3 cofactor;
        cofactor.data[0][0] =  (data[1][1] * data[2][2] - data[1][2] * data[2][1]);
        cofactor.data[0][1] = -(data[1][0] * data[2][2] - data[1][2] * data[2][0]);
        cofactor.data[0][2] =  (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
        cofactor.data[1][0] = -(data[0][1] * data[2][2] - data[0][2] * data[2][1]);
        cofactor.data[1][1] =  (data[0][0] * data[2][2] - data[0][2] * data[2][0]);
        cofactor.data[1][2] = -(data[0][0] * data[2][1] - data[0][1] * data[2][0]);
        cofactor.data[2][0] =  (data[0][1] * data[1][2] - data[0][2] * data[1][1]);
        cofactor.data[2][1] = -(data[0][0] * data[1][2] - data[0][2] * data[1][0]);
        cofactor.data[2][2] =  (data[0][0] * data[1][1] - data[0][1] * data[1][0]);
    
        // Step 2: transpose the cofactor matrix to get the adjugate
        Mat3 adjugate = cofactor.transpose();

        // Step 3: divide the adjugate by the determinant to get the inverse
        Mat3 inverse;
        for (int i = 0; i < 3; i++) 
            for (int j = 0; j < 3; j++) 
                inverse.data[i][j] = adjugate.data[i][j] / det;
            
        return inverse;
    
    }

    Mat3 Mat3::rotationX(double theta) {
        Mat3 R = Mat3().identity();
        double c = std::cos(theta);
        double s = std::sin(theta);
        R.data[1][1] = c;
        R.data[1][2] = -s;
        R.data[2][1] = s;
        R.data[2][2] = c;
        return R;
    }

    Mat3 Mat3::rotationY(double theta) {
        Mat3 R = Mat3().identity();
        double c = std::cos(theta);
        double s = std::sin(theta);
        R.data[0][0] = c;
        R.data[0][2] = s;
        R.data[2][0] = -s;
        R.data[2][2] = c;
        return R;
    }

    Mat3 Mat3::rotationZ(double theta) {
        Mat3 R = Mat3().identity();
        double c = std::cos(theta);
        double s = std::sin(theta);
        R.data[0][0] = c;
        R.data[0][1] = -s;
        R.data[1][0] = s;
        R.data[1][1] = c;
        return R;
    }

    Vec3 operator*(const Mat3& m, const Vec3& v) {
        Vec3 result;
        result.x = m.data[0][0] * v.x + m.data[0][1] * v.y + m.data[0][2] * v.z;
        result.y = m.data[1][0] * v.x + m.data[1][1] * v.y + m.data[1][2] * v.z;
        result.z = m.data[2][0] * v.x + m.data[2][1] * v.y + m.data[2][2] * v.z;
        return result;
    }

}