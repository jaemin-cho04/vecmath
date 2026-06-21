#include <gtest/gtest.h>
#include <linalg/quaternion.hpp>
#include <linalg/vec3.hpp>
#include <cmath>

constexpr double PI = 3.14159265358979323846;

using linalg::Quaternion;
using linalg::Vec3;

// --- Sanity check ------------------------------------------------------------

TEST(QuaternionSetup, ToolchainWorks) {
    Quaternion q(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(q.w, 1.0);
    EXPECT_DOUBLE_EQ(q.x, 2.0);
    EXPECT_DOUBLE_EQ(q.y, 3.0);
    EXPECT_DOUBLE_EQ(q.z, 4.0);
}

TEST(Quaternion, Normalized) {
    Quaternion q(1.0, 2.0, 3.0, 4.0);
    Quaternion nq = q.normalized();
    double len = std::sqrt(nq.w * nq.w + nq.x * nq.x + nq.y * nq.y + nq.z * nq.z);
    EXPECT_NEAR(len, 1.0, 1e-9);
}

TEST(Quaternion, FromAxisAngle) {
    Vec3 axis(0, 1, 0);
    double angle = PI / 2; // 90 degrees
    Quaternion q = Quaternion::fromAxisAngle(axis, angle);
    EXPECT_NEAR(q.w, std::cos(angle / 2), 1e-9);
    EXPECT_NEAR(q.x, 0.0, 1e-9);
    EXPECT_NEAR(q.y, std::sin(angle / 2), 1e-9);
    EXPECT_NEAR(q.z, 0.0, 1e-9);
}

TEST(Quaternion, Multiply) {
    Quaternion q1(1.0, 0.0, 0.0, 0.0); // identity
    Quaternion q2(0.0, 1.0, 0.0, 0.0); // 180 degree rotation around x-axis
    Quaternion product = q1 * q2;
    EXPECT_DOUBLE_EQ(product.w, 0.0);
    EXPECT_DOUBLE_EQ(product.x, 1.0);
    EXPECT_DOUBLE_EQ(product.y, 0.0);
    EXPECT_DOUBLE_EQ(product.z, 0.0);
}
