#include <gtest/gtest.h>
#include <linalg/vec3.hpp>
#include <cmath>

using linalg::Vec3;

TEST(Vec3, AddsComponentwise) {
    Vec3 a(1, 2, 3);
    Vec3 b(4, 5, 6);
    Vec3 c = a + b;
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

TEST(Vec3, UnaryNegation) {
    Vec3 v(1, -2, 3);
    Vec3 n = -v;
    EXPECT_DOUBLE_EQ(n.x, -1.0);
    EXPECT_DOUBLE_EQ(n.y, 2.0);
    EXPECT_DOUBLE_EQ(n.z, -3.0);
}

TEST(Vec3, DividesByScalar) {
    Vec3 v(2, 4, 6);
    Vec3 c = v / 2.0;
    EXPECT_DOUBLE_EQ(c.x, 1.0);
    EXPECT_DOUBLE_EQ(c.y, 2.0);
    EXPECT_DOUBLE_EQ(c.z, 3.0);
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

TEST(Vec3, CompoundAssignment) {
    Vec3 v(1, 2, 3);
    v += Vec3(1, 1, 1);
    EXPECT_TRUE(v == Vec3(2, 3, 4));

    v -= Vec3(1, 1, 1);
    EXPECT_TRUE(v == Vec3(1, 2, 3));

    v *= 2.0;
    EXPECT_TRUE(v == Vec3(2, 4, 6));

    v /= 2.0;
    EXPECT_TRUE(v == Vec3(1, 2, 3));
}

TEST(Vec3, Distance) {
    Vec3 a(0, 0, 0);
    Vec3 b(3, 4, 0);
    EXPECT_DOUBLE_EQ(distance(a, b), 5.0);
}

TEST(Vec3, Lerp) {
    Vec3 a(0, 0, 0);
    Vec3 b(10, 20, 30);
    Vec3 mid = lerp(a, b, 0.5);
    EXPECT_DOUBLE_EQ(mid.x, 5.0);
    EXPECT_DOUBLE_EQ(mid.y, 10.0);
    EXPECT_DOUBLE_EQ(mid.z, 15.0);

    EXPECT_TRUE(lerp(a, b, 0.0) == a);
    EXPECT_TRUE(lerp(a, b, 1.0) == b);
}