#include <gtest/gtest.h>
#include <linalg/vec.hpp>
#include <cmath>
#include <stdexcept>

using linalg::Vec;

TEST(VecTemplate, ConstructsFromInitializerList) {
    Vec<double, 3> v{1.0, 2.0, 3.0};
    EXPECT_DOUBLE_EQ(v.data[0], 1.0);
    EXPECT_DOUBLE_EQ(v.data[1], 2.0);
    EXPECT_DOUBLE_EQ(v.data[2], 3.0);
}

TEST(VecTemplate, AddsComponentwise) {
    Vec<double, 3> a{1, 2, 3};
    Vec<double, 3> b{4, 5, 6};
    Vec<double, 3> c = a + b;
    EXPECT_DOUBLE_EQ(c.data[0], 5.0);
    EXPECT_DOUBLE_EQ(c.data[1], 7.0);
    EXPECT_DOUBLE_EQ(c.data[2], 9.0);
}

TEST(VecTemplate, SubtractsComponentwise) {
    Vec<double, 3> a{1, 2, 3};
    Vec<double, 3> b{4, 5, 6};
    Vec<double, 3> c = a - b;
    EXPECT_DOUBLE_EQ(c.data[0], -3.0);
    EXPECT_DOUBLE_EQ(c.data[1], -3.0);
    EXPECT_DOUBLE_EQ(c.data[2], -3.0);
}

TEST(VecTemplate, UnaryNegation) {
    Vec<double, 3> v{1, -2, 3};
    Vec<double, 3> n = -v;
    EXPECT_DOUBLE_EQ(n.data[0], -1.0);
    EXPECT_DOUBLE_EQ(n.data[1], 2.0);
    EXPECT_DOUBLE_EQ(n.data[2], -3.0);
}

TEST(VecTemplate, DividesByScalar) {
    Vec<double, 3> v{2, 4, 6};
    Vec<double, 3> c = v / 2.0;
    EXPECT_DOUBLE_EQ(c.data[0], 1.0);
    EXPECT_DOUBLE_EQ(c.data[1], 2.0);
    EXPECT_DOUBLE_EQ(c.data[2], 3.0);
}

TEST(VecTemplate, MultipliesByScalar) {
    Vec<double, 3> a{1, 2, 3};
    Vec<double, 3> c = a * 3.0;
    EXPECT_DOUBLE_EQ(c.data[0], 3.0);
    EXPECT_DOUBLE_EQ(c.data[1], 6.0);
    EXPECT_DOUBLE_EQ(c.data[2], 9.0);
}

TEST(VecTemplate, DotProduct) {
    Vec<double, 3> a{1, 0, 0};
    Vec<double, 3> b{0, 1, 0};
    EXPECT_DOUBLE_EQ(dot(a, b), 0.0);

    Vec<double, 3> c{1, 2, 3};
    EXPECT_DOUBLE_EQ(dot(c, c), 14.0);
}

TEST(VecTemplate, Length) {
    Vec<double, 3> v{1, 2, 3};
    EXPECT_DOUBLE_EQ(v.length(), std::sqrt(14.0));
}

TEST(VecTemplate, Normalized) {
    Vec<double, 3> v{1, 2, 3};
    Vec<double, 3> n = v.normalized();
    EXPECT_NEAR(n.length(), 1.0, 1e-9);
    EXPECT_DOUBLE_EQ(n.data[0], 1.0 / std::sqrt(14.0));
    EXPECT_DOUBLE_EQ(n.data[1], 2.0 / std::sqrt(14.0));
    EXPECT_DOUBLE_EQ(n.data[2], 3.0 / std::sqrt(14.0));
}

TEST(VecTemplate, NormalizedThrowsOnZeroLength) {
    Vec<double, 3> v{0, 0, 0};
    EXPECT_THROW(v.normalized(), std::runtime_error);
}

TEST(VecTemplate, CrossProduct) {
    Vec<double, 3> a{1, 0, 0};
    Vec<double, 3> b{0, 1, 0};
    Vec<double, 3> c = cross(a, b);
    EXPECT_DOUBLE_EQ(c.data[0], 0.0);
    EXPECT_DOUBLE_EQ(c.data[1], 0.0);
    EXPECT_DOUBLE_EQ(c.data[2], 1.0);
}

TEST(VecTemplate, ToleranceBasedEquality) {
    Vec<double, 3> a{1.0, 2.0, 3.0};
    Vec<double, 3> b{1.0, 2.0, 3.0};
    Vec<double, 3> c{1.0 + 1e-10, 2.0 - 1e-10, 3.0 + 1e-10};
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a == c);
}

// The generality is the point: same code works for a different size and a
// different underlying numeric type, with no duplicated implementation.
TEST(VecTemplate, WorksForDifferentSizeAndType) {
    Vec<float, 4> a{1.0f, 2.0f, 3.0f, 4.0f};
    Vec<float, 4> b{1.0f, 1.0f, 1.0f, 1.0f};
    Vec<float, 4> c = a + b;
    EXPECT_FLOAT_EQ(c.data[0], 2.0f);
    EXPECT_FLOAT_EQ(c.data[1], 3.0f);
    EXPECT_FLOAT_EQ(c.data[2], 4.0f);
    EXPECT_FLOAT_EQ(c.data[3], 5.0f);
}
