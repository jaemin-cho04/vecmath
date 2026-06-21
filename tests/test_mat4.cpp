#include <gtest/gtest.h>
#include <linalg/mat4.hpp>
#include <linalg/mat3.hpp>
#include <linalg/vec3.hpp>

using linalg::Mat4;
using linalg::Mat3;
using linalg::Vec3;


// --- Sanity check ------------------------------------------------------------
TEST(Mat4Setup, ToolchainWorks) {
    double d[4][4] = {{1.0, 2.0, 3.0, 4.0},
                      {5.0, 6.0, 7.0, 8.0},
                      {9.0, 10.0, 11.0, 12.0},
                      {13.0, 14.0, 15.0, 16.0}};
    Mat4 m(d);
    EXPECT_DOUBLE_EQ(m.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(m.data[1][1], 6.0);
    EXPECT_DOUBLE_EQ(m.data[2][2], 11.0);
    EXPECT_DOUBLE_EQ(m.data[3][3], 16.0);
}

TEST(Mat4, Identity) {
    Mat4 I = Mat4().identity();
    EXPECT_DOUBLE_EQ(I.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(I.data[1][1], 1.0);
    EXPECT_DOUBLE_EQ(I.data[2][2], 1.0);
    EXPECT_DOUBLE_EQ(I.data[3][3], 1.0);
    EXPECT_DOUBLE_EQ(I.data[0][1], 0.0);
    EXPECT_DOUBLE_EQ(I.data[0][2], 0.0);
    EXPECT_DOUBLE_EQ(I.data[0][3], 0.0);
    EXPECT_DOUBLE_EQ(I.data[1][0], 0.0);
    EXPECT_DOUBLE_EQ(I.data[1][2], 0.0);
    EXPECT_DOUBLE_EQ(I.data[1][3], 0.0);
    EXPECT_DOUBLE_EQ(I.data[2][0], 0.0);
    EXPECT_DOUBLE_EQ(I.data[2][1], 0.0);
    EXPECT_DOUBLE_EQ(I.data[2][3], 0.0);
    EXPECT_DOUBLE_EQ(I.data[3][0], 0.0);
    EXPECT_DOUBLE_EQ(I.data[3][1], 0.0);
    EXPECT_DOUBLE_EQ(I.data[3][2], 0.0);
}

TEST(Mat4, Transpose) {
    double d[4][4] = {{1.0, 2.0, 3.0, 4.0},
                      {5.0, 6.0, 7.0, 8.0},
                      {9.0, 10.0, 11.0, 12.0},
                      {13.0, 14.0, 15.0, 16.0}};
    Mat4 m(d);
    Mat4 t = m.transpose();
    EXPECT_DOUBLE_EQ(t.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(t.data[0][1], 5.0);
    EXPECT_DOUBLE_EQ(t.data[0][2], 9.0);
    EXPECT_DOUBLE_EQ(t.data[0][3], 13.0);
    EXPECT_DOUBLE_EQ(t.data[1][0], 2.0);
    EXPECT_DOUBLE_EQ(t.data[1][1], 6.0);
    EXPECT_DOUBLE_EQ(t.data[1][2], 10.0);
    EXPECT_DOUBLE_EQ(t.data[1][3], 14.0);
    EXPECT_DOUBLE_EQ(t.data[2][0], 3.0);
    EXPECT_DOUBLE_EQ(t.data[2][1], 7.0);
    EXPECT_DOUBLE_EQ(t.data[2][2], 11.0);
    EXPECT_DOUBLE_EQ(t.data[2][3], 15.0);
    EXPECT_DOUBLE_EQ(t.data[3][0], 4.0);
    EXPECT_DOUBLE_EQ(t.data[3][1], 8.0);
    EXPECT_DOUBLE_EQ(t.data[3][2], 12.0);
    EXPECT_DOUBLE_EQ(t.data[3][3], 16.0);
}

TEST(Mat4, Multiply) {
    double d1[4][4] = {{1.0, 2.0, 3.0, 4.0},
                       {5.0, 6.0, 7.0, 8.0},
                       {9.0, 10.0, 11.0, 12.0},
                       {13.0, 14.0, 15.0, 16.0}};
    double d2[4][4] = {{16.0, 15.0, 14.0, 13.0},
                       {12.0, 11.0, 10.0, 9.0},
                       {8.0, 7.0, 6.0, 5.0},
                       {4.0, 3.0, 2.0, 1.0}};
    Mat4 m1(d1);
    Mat4 m2(d2);
    Mat4 product = m1 * m2;
    EXPECT_DOUBLE_EQ(product.data[0][0], 80.0);
    EXPECT_DOUBLE_EQ(product.data[0][1], 70.0);
    EXPECT_DOUBLE_EQ(product.data[0][2], 60.0);
    EXPECT_DOUBLE_EQ(product.data[0][3], 50.0);
    EXPECT_DOUBLE_EQ(product.data[1][0], 240.0);
    EXPECT_DOUBLE_EQ(product.data[1][1], 214.0);
    EXPECT_DOUBLE_EQ(product.data[1][2], 188.0);
    EXPECT_DOUBLE_EQ(product.data[1][3], 162.0);
    EXPECT_DOUBLE_EQ(product.data[2][0], 400.0);
    EXPECT_DOUBLE_EQ(product.data[2][1], 358.0);
    EXPECT_DOUBLE_EQ(product.data[2][2], 316.0);
    EXPECT_DOUBLE_EQ(product.data[2][3], 274.0);
    EXPECT_DOUBLE_EQ(product.data[3][0], 560.0);
    EXPECT_DOUBLE_EQ(product.data[3][1], 502.0);
    EXPECT_DOUBLE_EQ(product.data[3][2], 444.0);
    EXPECT_DOUBLE_EQ(product.data[3][3], 386.0);
}

TEST(Mat4, Determinant) {
    double d[4][4] = {{1.0, 2.0, 3.0, 4.0},
                      {5.0, 6.0, 7.0, 8.0},
                      {9.0, 10.0, 11.0, 12.0},
                      {13.0, 14.0, 15.0, 16.0}};
    Mat4 m(d);
    double det = determinant(m);
    EXPECT_DOUBLE_EQ(det, 0.0);
}

TEST(Mat4, DeterminantNonSingular) {
    double d[4][4] = {{3.0, 2.0, 3.0, 4.0},
                      {5.0, 6.0, 7.0, 8.0},
                      {9.0, 10.0, 2.0, 12.0},
                      {13.0, 2.0, 4.0, 17.0}}; // changed last element to make it non-singular
    Mat4 m(d);
    double det = determinant(m);
    EXPECT_DOUBLE_EQ(det, -304.0);
}

TEST(Mat4, Inverse) {
    double d[4][4] = {{3.0, 2.0, 3.0, 4.0},
                      {5.0, 6.0, 7.0, 8.0},
                      {9.0, 10.0, 2.0, 12.0},
                      {13.0, 2.0, 4.0, 17.0}}; // non-singular
    Mat4 m(d);
    Mat4 inv = m.inverse();
    Mat4 identity = m * inv;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                EXPECT_NEAR(identity.data[i][j], 1.0, 1e-9);
            } else {
                EXPECT_NEAR(identity.data[i][j], 0.0, 1e-9);
            }
        }
    } 
}

TEST(Mat4, InverseSingular) {
    double d[4][4] = {{1.0, 2.0, 3.0, 4.0},
                      {5.0, 6.0, 7.0, 8.0},
                      {9.0, 10.0, 11.0, 12.0},
                      {13.0, 14.0, 15.0, 16.0}}; // singular
    Mat4 m(d);
    EXPECT_THROW(m.inverse(), std::runtime_error);
}

TEST(Mat4, FromRotationTranslation) {
    Mat3 rotation = Mat3().identity();
    Vec3 translation(1.0, 2.0, 3.0);
    Mat4 transform = fromRotationTranslation(rotation, translation);
    EXPECT_DOUBLE_EQ(transform.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(transform.data[1][1], 1.0);
    EXPECT_DOUBLE_EQ(transform.data[2][2], 1.0);
    EXPECT_DOUBLE_EQ(transform.data[0][3], 1.0);
    EXPECT_DOUBLE_EQ(transform.data[1][3], 2.0);
    EXPECT_DOUBLE_EQ(transform.data[2][3], 3.0);
    EXPECT_DOUBLE_EQ(transform.data[3][3], 1.0);
}