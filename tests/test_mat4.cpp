#include <gtest/gtest.h>
#include <linalg/mat4.hpp>

using linalg::Mat4;

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