#pragma once

namespace linalg {

    struct Mat4 {
        double data[4][4] = {{0.0, 0.0, 0.0, 0.0},
                           {0.0, 0.0, 0.0, 0.0},
                           {0.0, 0.0, 0.0, 0.0},
                           {0.0, 0.0, 0.0, 0.0}};
    
        // Constructors
        Mat4() = default;

        Mat4(double d[4][4]);

        // --- Member operations ---
        Mat4 identity() const; // returns identity matrix
        Mat4 transpose() const; // returns transposed matrix
        Mat4 inverse() const; // returns inverse matrix (if invertible)
    };

    Mat4 operator*(const Mat4& a, const Mat4& b); // matrix multiplication

    double determinant(const Mat4& m); // helper function for inverse
}