#include <gtest/gtest.h>
#include <linalg/mat3.hpp>

using linalg::Mat3;

// --- Sanity check ------------------------------------------------------------
TEST(Mat3Setup, ToolchainWorks) {   
    double d[3][3] = {{1.0, 2.0, 3.0},
                      {4.0, 5.0, 6.0},
                      {7.0, 8.0, 9.0}};
    Mat3 m(d);
    EXPECT_DOUBLE_EQ(m.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(m.data[1][1], 5.0);
    EXPECT_DOUBLE_EQ(m.data[2][2], 9.0);
}

TEST(Mat3, Identity) {
    Mat3 I = Mat3().identity();
    EXPECT_DOUBLE_EQ(I.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(I.data[1][1], 1.0);
    EXPECT_DOUBLE_EQ(I.data[2][2], 1.0);
    EXPECT_DOUBLE_EQ(I.data[0][1], 0.0);
    EXPECT_DOUBLE_EQ(I.data[0][2], 0.0);
    EXPECT_DOUBLE_EQ(I.data[1][0], 0.0);
    EXPECT_DOUBLE_EQ(I.data[1][2], 0.0);
    EXPECT_DOUBLE_EQ(I.data[2][0], 0.0);
    EXPECT_DOUBLE_EQ(I.data[2][1], 0.0);
}

TEST(Mat3, Transpose) {
    double d[3][3] = {{1.0, 2.0, 3.0},
                      {4.0, 5.0, 6.0},
                      {7.0, 8.0, 9.0}};
    Mat3 m(d);
    Mat3 t = m.transpose();
    EXPECT_DOUBLE_EQ(t.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(t.data[0][1], 4.0);
    EXPECT_DOUBLE_EQ(t.data[0][2], 7.0);
    EXPECT_DOUBLE_EQ(t.data[1][0], 2.0);
    EXPECT_DOUBLE_EQ(t.data[1][1], 5.0);
    EXPECT_DOUBLE_EQ(t.data[1][2], 8.0);
    EXPECT_DOUBLE_EQ(t.data[2][0], 3.0);
    EXPECT_DOUBLE_EQ(t.data[2][1], 6.0);
    EXPECT_DOUBLE_EQ(t.data[2][2], 9.0);
}

TEST(Mat3, Multiply) {
    double d1[3][3] = {{1.0, 2.0, 3.0},
                       {4.0, 5.0, 6.0},
                       {7.0, 8.0, 9.0}};
    double d2[3][3] = {{9.0, 8.0, 7.0},
                       {6.0, 5.0, 4.0},
                       {3.0, 2.0, 1.0}};
    Mat3 m1(d1);
    Mat3 m2(d2);
    Mat3 product = m1 * m2;
    EXPECT_DOUBLE_EQ(product.data[0][0], 30.0);
    EXPECT_DOUBLE_EQ(product.data[0][1], 24.0);
    EXPECT_DOUBLE_EQ(product.data[0][2], 18.0);
    EXPECT_DOUBLE_EQ(product.data[1][0], 84.0);
    EXPECT_DOUBLE_EQ(product.data[1][1], 69.0);
    EXPECT_DOUBLE_EQ(product.data[1][2], 54.0);
    EXPECT_DOUBLE_EQ(product.data[2][0], 138.0);
    EXPECT_DOUBLE_EQ(product.data[2][1], 114.0);
    EXPECT_DOUBLE_EQ(product.data[2][2], 90.0);
}

TEST(Mat3, MutiplyIdentity) {
    double d[3][3] = {{1.0, 2.0, 3.0},
                      {4.0, 5.0, 6.0},
                      {7.0, 8.0, 9.0}};
    Mat3 m(d);
    Mat3 I = Mat3().identity();
    Mat3 product = m * I;
    EXPECT_DOUBLE_EQ(product.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(product.data[1][1], 5.0);
    EXPECT_DOUBLE_EQ(product.data[2][2], 9.0);
    EXPECT_DOUBLE_EQ(product.data[0][1], 2.0);
    EXPECT_DOUBLE_EQ(product.data[0][2], 3.0);
    EXPECT_DOUBLE_EQ(product.data[1][0], 4.0);
    EXPECT_DOUBLE_EQ(product.data[1][2], 6.0);
    EXPECT_DOUBLE_EQ(product.data[2][0], 7.0);
    EXPECT_DOUBLE_EQ(product.data[2][1], 8.0);
}

TEST(Mat3, Determinant) {
    double d[3][3] = {{1.0, 2.0, 3.0},
                      {0.0, 1.0, 4.0},
                      {5.0, 6.0, 0.0}};
    Mat3 m(d);
    double det = determinant(m);
    EXPECT_DOUBLE_EQ(det, 1.0);
}

TEST(Mat3, DeterminantSingular) {
    double d[3][3] = {{0.0, 0.0, 0.0},
                      {4.0, 5.0, 6.0},
                      {7.0, 8.0, 9.0}};
    Mat3 m(d);
    double det = determinant(m);
    EXPECT_DOUBLE_EQ(det, 0.0);
}

TEST(Mat3, Inverse) {
    double d[3][3] = {{1.0, 2.0, 3.0},
                      {0.0, 1.0, 4.0},
                      {5.0, 6.0, 0.0}};
    Mat3 m(d);
    Mat3 inv = m.inverse();
    Mat3 I = m * inv;
    EXPECT_NEAR(I.data[0][0], 1.0, 1e-9);
    EXPECT_NEAR(I.data[1][1], 1.0, 1e-9);
    EXPECT_NEAR(I.data[2][2], 1.0, 1e-9);
    EXPECT_NEAR(I.data[0][1], 0.0, 1e-9);
    EXPECT_NEAR(I.data[0][2], 0.0, 1e-9);
    EXPECT_NEAR(I.data[1][0], 0.0, 1e-9);
    EXPECT_NEAR(I.data[1][2], 0.0, 1e-9);
    EXPECT_NEAR(I.data[2][0], 0.0, 1e-9);
    EXPECT_NEAR(I.data[2][1], 0.0, 1e-9);
}

TEST(Mat3, InverseSingular) {
    double d[3][3] = {{0.0, 0.0, 0.0},
                      {4.0, 5.0, 6.0},
                      {7.0, 8.0, 9.0}};
    Mat3 m(d);
    EXPECT_THROW(m.inverse(), std::runtime_error);
}