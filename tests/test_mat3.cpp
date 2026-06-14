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