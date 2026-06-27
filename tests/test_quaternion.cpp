#include <gtest/gtest.h>
#include <linalg/quaternion.hpp>
#include <linalg/vec3.hpp>
#include <cmath>

constexpr double PI = 3.14159265358979323846;

using linalg::Quaternion;
using linalg::Vec3;

TEST(Quaternion, ConstructsFromComponents) {
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

TEST(Quaternion, Length) {
    Quaternion q(1.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(q.length(), 1.0);

    Quaternion q2(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(q2.length(), std::sqrt(1.0 + 4.0 + 9.0 + 16.0));
}

TEST(Quaternion, Conjugate) {
    Quaternion q(1.0, 2.0, 3.0, 4.0);
    Quaternion c = q.conjugate();
    EXPECT_DOUBLE_EQ(c.w, 1.0);
    EXPECT_DOUBLE_EQ(c.x, -2.0);
    EXPECT_DOUBLE_EQ(c.y, -3.0);
    EXPECT_DOUBLE_EQ(c.z, -4.0);
}

TEST(Quaternion, ConjugateIsInverseForUnitQuaternion) {
    Quaternion q = Quaternion::fromAxisAngle(Vec3(0, 0, 1), PI / 3);
    Quaternion product = q * q.conjugate();
    EXPECT_NEAR(product.w, 1.0, 1e-9);
    EXPECT_NEAR(product.x, 0.0, 1e-9);
    EXPECT_NEAR(product.y, 0.0, 1e-9);
    EXPECT_NEAR(product.z, 0.0, 1e-9);
}

TEST(Quaternion, ToRotationMatrixRotatesVector) {
    // 90 degree rotation around Z: (1, 0, 0) should land on (0, 1, 0),
    // matching the Mat3::rotationZ behavior verified elsewhere.
    Quaternion q = Quaternion::fromAxisAngle(Vec3(0, 0, 1), PI / 2);
    linalg::Mat3 r = q.toRotationMatrix();
    Vec3 rotated = r * Vec3(1, 0, 0);
    EXPECT_NEAR(rotated.x, 0.0, 1e-9);
    EXPECT_NEAR(rotated.y, 1.0, 1e-9);
    EXPECT_NEAR(rotated.z, 0.0, 1e-9);
}

TEST(Quaternion, RotateMatchesToRotationMatrix) {
    Quaternion q = Quaternion::fromAxisAngle(Vec3(0, 0, 1), PI / 2);
    Vec3 rotated = q.rotate(Vec3(1, 0, 0));
    EXPECT_NEAR(rotated.x, 0.0, 1e-9);
    EXPECT_NEAR(rotated.y, 1.0, 1e-9);
    EXPECT_NEAR(rotated.z, 0.0, 1e-9);
}

TEST(Quaternion, InverseUndoesRotation) {
    Quaternion q = Quaternion::fromAxisAngle(Vec3(1, 0, 0), PI / 3);
    Quaternion product = q * q.inverse();
    EXPECT_NEAR(product.w, 1.0, 1e-9);
    EXPECT_NEAR(product.x, 0.0, 1e-9);
    EXPECT_NEAR(product.y, 0.0, 1e-9);
    EXPECT_NEAR(product.z, 0.0, 1e-9);
}

TEST(Quaternion, ToQuaternionRoundTrip) {
    Quaternion original = Quaternion::fromAxisAngle(Vec3(1, 1, 0).normalized(), PI / 3);
    linalg::Mat3 m = original.toRotationMatrix();
    Quaternion roundTrip = toQuaternion(m);

    // Either roundTrip or its negation represents the same rotation
    // (q and -q are the same rotation), so compare via the resulting matrix.
    Vec3 p(1, 2, 3);
    Vec3 viaOriginal = original.rotate(p);
    Vec3 viaRoundTrip = roundTrip.rotate(p);
    EXPECT_NEAR(viaOriginal.x, viaRoundTrip.x, 1e-9);
    EXPECT_NEAR(viaOriginal.y, viaRoundTrip.y, 1e-9);
    EXPECT_NEAR(viaOriginal.z, viaRoundTrip.z, 1e-9);
}

TEST(Quaternion, ToleranceBasedEquality) {
    Quaternion a(1.0, 2.0, 3.0, 4.0);
    Quaternion b(1.0, 2.0, 3.0, 4.0);
    Quaternion c(1.0 + 1e-10, 2.0 - 1e-10, 3.0 + 1e-10, 4.0);
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a == c);
}

TEST(Quaternion, FromEulerAnglesMatchesAxisAngleForSingleAxis) {
    // A pure yaw rotation should match fromAxisAngle around Z for the same angle.
    double yaw = PI / 4;
    Quaternion fromEuler = Quaternion::fromEulerAngles(0.0, 0.0, yaw);
    Quaternion fromAxis = Quaternion::fromAxisAngle(Vec3(0, 0, 1), yaw);
    EXPECT_NEAR(fromEuler.w, fromAxis.w, 1e-9);
    EXPECT_NEAR(fromEuler.x, fromAxis.x, 1e-9);
    EXPECT_NEAR(fromEuler.y, fromAxis.y, 1e-9);
    EXPECT_NEAR(fromEuler.z, fromAxis.z, 1e-9);
}

TEST(Quaternion, EulerRoundTrip) {
    double roll = 0.3, pitch = -0.2, yaw = 0.6;
    Quaternion q = Quaternion::fromEulerAngles(roll, pitch, yaw);
    Vec3 angles = q.toEulerAngles();
    EXPECT_NEAR(angles.x, roll, 1e-9);
    EXPECT_NEAR(angles.y, pitch, 1e-9);
    EXPECT_NEAR(angles.z, yaw, 1e-9);
}

TEST(Quaternion, DotProduct) {
    Quaternion a(1.0, 0.0, 0.0, 0.0);
    Quaternion b(0.0, 1.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(dot(a, b), 0.0);
    EXPECT_DOUBLE_EQ(dot(a, a), 1.0);
}

TEST(Quaternion, SlerpEndpoints) {
    Quaternion a = Quaternion::fromAxisAngle(Vec3(0, 0, 1), 0.0);
    Quaternion b = Quaternion::fromAxisAngle(Vec3(0, 0, 1), PI / 2);

    Quaternion atStart = slerp(a, b, 0.0);
    EXPECT_NEAR(atStart.w, a.w, 1e-9);
    EXPECT_NEAR(atStart.z, a.z, 1e-9);

    Quaternion atEnd = slerp(a, b, 1.0);
    EXPECT_NEAR(atEnd.w, b.w, 1e-9);
    EXPECT_NEAR(atEnd.z, b.z, 1e-9);
}

TEST(Quaternion, SlerpHalfwayIsHalfTheAngle) {
    Quaternion a = Quaternion::fromAxisAngle(Vec3(0, 0, 1), 0.0);
    Quaternion b = Quaternion::fromAxisAngle(Vec3(0, 0, 1), PI / 2);
    Quaternion mid = slerp(a, b, 0.5);
    Quaternion expected = Quaternion::fromAxisAngle(Vec3(0, 0, 1), PI / 4);
    EXPECT_NEAR(mid.w, expected.w, 1e-9);
    EXPECT_NEAR(mid.z, expected.z, 1e-9);
}
