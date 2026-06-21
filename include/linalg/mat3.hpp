#pragma once //pragma stands for pragmatic directive
#include <linalg/vec3.hpp>

namespace linalg {

    struct Mat3 {
        double data[3][3] = {{0.0, 0.0, 0.0},
                           {0.0, 0.0, 0.0},
                           {0.0, 0.0, 0.0}};
    
        // Constructors
        Mat3() = default;

        Mat3(double d[3][3]);

        // --- Member operations ---
        Mat3 identity() const; // returns identity matrix
        Mat3 transpose() const; // returns transposed matrix
        Mat3 inverse() const; // returns inverse matrix (if invertible)

        static Mat3 rotationX(double theta); // returns a rotation matrix for rotating around the X-axis by theta radians
        static Mat3 rotationY(double theta); // returns a rotation matrix for rotating around the Y
        static Mat3 rotationZ(double theta); // returns a rotation matrix for rotating around the Z-axis by theta radians
    };

    Mat3 operator*(const Mat3& a, const Mat3& b); // matrix multiplication

    double determinant(const Mat3& m); // helper function for inverse

    Vec3 operator*(const Mat3& m, const Vec3& v); // matrix-vector multiplication

}