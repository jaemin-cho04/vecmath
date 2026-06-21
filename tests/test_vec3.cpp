#include <gtest/gtest.h>
#include <linalg/vec3.hpp>
#include <cmath>

using linalg::Vec3;

// --- Sanity check ------------------------------------------------------------
// This passes immediately so your CI is green from commit #1. Delete it once
// you have real tests below.
TEST(Setup, ToolchainWorks) {
    Vec3 v(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
    EXPECT_DOUBLE_EQ(v.z, 3.0);
}

// TEST(test suite, test name())

// --- YOUR TESTS GO HERE ------------------------------------------------------
// Write the test BEFORE or RIGHT AFTER each operation. The pattern:

// TEST, EXPECT... are macros, they look like functions but they do more 
// — they generate code that runs the test and reports results. 
// You can write multiple EXPECTs in one TEST, but if one fails, 
// the rest will still run (unlike ASSERT which aborts the test immediately).

TEST(Vec3, AddsComponentwise) {
    Vec3 a(1, 2, 3);
    Vec3 b(4, 5, 6);
    Vec3 c = a + b;
    // translates into operator+(a, b)
    EXPECT_DOUBLE_EQ(c.x, 5.0);
    EXPECT_DOUBLE_EQ(c.y, 7.0);
    EXPECT_DOUBLE_EQ(c.z, 9.0);
}

TEST(Vec3, SubtractsComponentwise) {
    Vec3 a(1, 2, 3);
    Vec3 b(4, 5, 6);
    Vec3 c = a - b;
    EXPECT_DOUBLE_EQ(c.x, -3.0);
    EXPECT_DOUBLE_EQ(c.y, -3.0);
    EXPECT_DOUBLE_EQ(c.z, -3.0);
}

TEST(Vec3, MultipliesComponentwise) {
    Vec3 a(1, 2, 3);
    double s = 3.0;
    Vec3 c = a * s;
    EXPECT_DOUBLE_EQ(c.x, 3.0);
    EXPECT_DOUBLE_EQ(c.y, 6.0);
    EXPECT_DOUBLE_EQ(c.z, 9.0);
}

TEST(Vec3, DotProduct) {
    EXPECT_DOUBLE_EQ(dot(Vec3(1, 0, 0), Vec3(0, 1, 0)), 0.0);  // perpendicular
    EXPECT_DOUBLE_EQ(dot(Vec3(1, 2, 3), Vec3(1, 2, 3)), 14.0); // = length^2
}

TEST(Vec3, Length) {
    Vec3 v(1, 0, 0);
    EXPECT_DOUBLE_EQ(v.length(), 1.0);
    EXPECT_DOUBLE_EQ(Vec3(0, 2, 0).length(), 2.0);
    EXPECT_DOUBLE_EQ(Vec3(0, 0, 3).length(), 3.0);
    EXPECT_DOUBLE_EQ(Vec3(1, 2, 3).length(), std::sqrt(14.0));
}

TEST(Vec3, Normalized) {
    Vec3 v(1, 0, 0);
    Vec3 n = v.normalized();
    // when writing v.normalized(), the compiler translates that into Vec3::normalized(v) 
    //— it passes v as the "this" pointer, which is how member functions work under the hood
    EXPECT_DOUBLE_EQ(n.x, 1.0);
    EXPECT_DOUBLE_EQ(n.y, 0.0);
    EXPECT_DOUBLE_EQ(n.z, 0.0);
    EXPECT_DOUBLE_EQ(n.length(), 1.0);
    Vec3 z(0, 0, 0);
    Vec3 nz = z.normalized();
    EXPECT_DOUBLE_EQ(nz.x, 0.0);
    EXPECT_DOUBLE_EQ(nz.y, 0.0);
    EXPECT_DOUBLE_EQ(nz.z, 0.0);
}

TEST(Vec3, NormalizedNonUnit) {
    Vec3 v(1, 2, 3);
    Vec3 n = v.normalized();
    EXPECT_NEAR(n.length(), 1.0, 1e-9);
    EXPECT_DOUBLE_EQ(n.x, 1.0 / std::sqrt(14.0));
    EXPECT_DOUBLE_EQ(n.y, 2.0 / std::sqrt(14.0));
    EXPECT_DOUBLE_EQ(n.z, 3.0 / std::sqrt(14.0));
}

TEST(Vec3, CrossProduct) {
    Vec3 a(1, 0, 0);
    Vec3 b(0, 1, 0);
    Vec3 c = cross(a, b);
    EXPECT_DOUBLE_EQ(c.x, 0.0);
    EXPECT_DOUBLE_EQ(c.y, 0.0);
    EXPECT_DOUBLE_EQ(c.z, 1.0);
}

TEST(Vec3, Compare) {
    Vec3 a(1.0, 2.0, 3.0);
    Vec3 b(1.0, 2.0, 3.0);
    Vec3 c(1.0 + 1e-10, 2.0 - 1e-10, 3.0 + 1e-10);
    EXPECT_TRUE(a == b); // should be exactly equal
    EXPECT_TRUE(a == c); // should be approximately equal within tolerance
}