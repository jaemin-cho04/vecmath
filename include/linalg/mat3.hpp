#pragma once //pragma stands for pragmatic directive

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
    };

    Mat3 operator*(const Mat3& a, const Mat3& b); // matrix multiplication

    double determinant(const Mat3& m); // helper function for inverse
}