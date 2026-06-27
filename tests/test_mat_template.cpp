#include <gtest/gtest.h>
#include <linalg/mat.hpp>
#include <linalg/vec.hpp>
#include <stdexcept>

using linalg::Mat;
using linalg::Vec;

TEST(MatTemplate, ConstructsFromArray) {
    double d[3][3] = {{1.0, 2.0, 3.0},
                       {4.0, 5.0, 6.0},
                       {7.0, 8.0, 9.0}};
    Mat<double, 3, 3> m(d);
    EXPECT_DOUBLE_EQ(m.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(m.data[1][1], 5.0);
    EXPECT_DOUBLE_EQ(m.data[2][2], 9.0);
}

TEST(MatTemplate, Identity) {
    Mat<double, 3, 3> I = Mat<double, 3, 3>::identity();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_DOUBLE_EQ(I.data[i][j], (i == j) ? 1.0 : 0.0);
        }
    }
}

TEST(MatTemplate, Transpose) {
    double d[2][3] = {{1.0, 2.0, 3.0},
                       {4.0, 5.0, 6.0}};
    Mat<double, 2, 3> m(d);
    Mat<double, 3, 2> t = m.transpose();
    EXPECT_DOUBLE_EQ(t.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(t.data[0][1], 4.0);
    EXPECT_DOUBLE_EQ(t.data[1][0], 2.0);
    EXPECT_DOUBLE_EQ(t.data[1][1], 5.0);
    EXPECT_DOUBLE_EQ(t.data[2][0], 3.0);
    EXPECT_DOUBLE_EQ(t.data[2][1], 6.0);
}

TEST(MatTemplate, MultiplyNonSquare) {
    double d1[2][3] = {{1.0, 2.0, 3.0},
                        {4.0, 5.0, 6.0}};
    double d2[3][2] = {{7.0, 8.0},
                        {9.0, 10.0},
                        {11.0, 12.0}};
    Mat<double, 2, 3> a(d1);
    Mat<double, 3, 2> b(d2);
    Mat<double, 2, 2> product = a * b;
    EXPECT_DOUBLE_EQ(product.data[0][0], 58.0);
    EXPECT_DOUBLE_EQ(product.data[0][1], 64.0);
    EXPECT_DOUBLE_EQ(product.data[1][0], 139.0);
    EXPECT_DOUBLE_EQ(product.data[1][1], 154.0);
}

TEST(MatTemplate, MultiplyByIdentity) {
    double d[3][3] = {{1.0, 2.0, 3.0},
                       {4.0, 5.0, 6.0},
                       {7.0, 8.0, 9.0}};
    Mat<double, 3, 3> m(d);
    Mat<double, 3, 3> I = Mat<double, 3, 3>::identity();
    Mat<double, 3, 3> product = m * I;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_DOUBLE_EQ(product.data[i][j], m.data[i][j]);
        }
    }
}

TEST(MatTemplate, MultiplyByVector) {
    double d[3][3] = {{1.0, 0.0, 0.0},
                       {0.0, 2.0, 0.0},
                       {0.0, 0.0, 3.0}};
    Mat<double, 3, 3> m(d);
    Vec<double, 3> v{1.0, 1.0, 1.0};
    Vec<double, 3> result = m * v;
    EXPECT_DOUBLE_EQ(result.data[0], 1.0);
    EXPECT_DOUBLE_EQ(result.data[1], 2.0);
    EXPECT_DOUBLE_EQ(result.data[2], 3.0);
}

TEST(MatTemplate, Determinant2x2) {
    double d[2][2] = {{4.0, 3.0},
                       {6.0, 3.0}};
    Mat<double, 2, 2> m(d);
    EXPECT_DOUBLE_EQ(determinant(m), -6.0);
}

TEST(MatTemplate, Determinant3x3) {
    double d[3][3] = {{1.0, 2.0, 3.0},
                       {0.0, 1.0, 4.0},
                       {5.0, 6.0, 0.0}};
    Mat<double, 3, 3> m(d);
    EXPECT_DOUBLE_EQ(determinant(m), 1.0);
}

TEST(MatTemplate, Determinant4x4) {
    double d[4][4] = {{3.0, 2.0, 3.0, 4.0},
                       {5.0, 6.0, 7.0, 8.0},
                       {9.0, 10.0, 2.0, 12.0},
                       {13.0, 2.0, 4.0, 17.0}};
    Mat<double, 4, 4> m(d);
    EXPECT_DOUBLE_EQ(determinant(m), -304.0);
}

TEST(MatTemplate, Inverse) {
    double d[3][3] = {{1.0, 2.0, 3.0},
                       {0.0, 1.0, 4.0},
                       {5.0, 6.0, 0.0}};
    Mat<double, 3, 3> m(d);
    Mat<double, 3, 3> inv = inverse(m);
    Mat<double, 3, 3> identity = m * inv;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_NEAR(identity.data[i][j], (i == j) ? 1.0 : 0.0, 1e-9);
        }
    }
}

TEST(MatTemplate, InverseThrowsOnSingularMatrix) {
    double d[3][3] = {{0.0, 0.0, 0.0},
                       {4.0, 5.0, 6.0},
                       {7.0, 8.0, 9.0}};
    Mat<double, 3, 3> m(d);
    EXPECT_THROW(inverse(m), std::runtime_error);
}

// The point of the template: the same multiply/determinant/inverse code
// works for a 5x5 matrix with no new implementation, unlike the hand-written
// Mat3/Mat4 which only ever handle their one fixed size.
TEST(MatTemplate, WorksForLargerSquareMatrix) {
    double d[5][5] = {{2.0, 0.0, 0.0, 0.0, 0.0},
                       {0.0, 3.0, 0.0, 0.0, 0.0},
                       {0.0, 0.0, 4.0, 0.0, 0.0},
                       {0.0, 0.0, 0.0, 5.0, 0.0},
                       {0.0, 0.0, 0.0, 0.0, 6.0}};
    Mat<double, 5, 5> m(d);
    EXPECT_DOUBLE_EQ(determinant(m), 2.0 * 3.0 * 4.0 * 5.0 * 6.0);
}
