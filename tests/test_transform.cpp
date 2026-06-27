#include <gtest/gtest.h>
#include <linalg/transform.hpp>
#include <cmath>

constexpr double PI = 3.14159265358979323846;

using linalg::Transform3D;
using linalg::Quaternion;
using linalg::Vec3;

TEST(Transform3D, IdentityLeavesPointUnchanged) {
    Transform3D t(Quaternion(), Vec3(0, 0, 0));
    Vec3 p(1, 2, 3);
    Vec3 result = t.apply(p);
    EXPECT_DOUBLE_EQ(result.x, 1.0);
    EXPECT_DOUBLE_EQ(result.y, 2.0);
    EXPECT_DOUBLE_EQ(result.z, 3.0);
}

TEST(Transform3D, AppliesRotationThenTranslation) {
    // 90 degree rotation around Z takes (1,0,0) to (0,1,0), then translate by (1,2,3).
    Quaternion rotation = Quaternion::fromAxisAngle(Vec3(0, 0, 1), PI / 2);
    Vec3 translation(1, 2, 3);
    Transform3D t(rotation, translation);

    Vec3 result = t.apply(Vec3(1, 0, 0));
    EXPECT_NEAR(result.x, 1.0, 1e-9);
    EXPECT_NEAR(result.y, 3.0, 1e-9);
    EXPECT_NEAR(result.z, 3.0, 1e-9);
}

TEST(Transform3D, MatchesToMat4) {
    Quaternion rotation = Quaternion::fromAxisAngle(Vec3(0, 0, 1), PI / 3);
    Vec3 translation(1, -2, 0.5);
    Transform3D t(rotation, translation);

    Vec3 p(2, 1, 0);
    Vec3 viaTransform = t.apply(p);
    Vec3 viaMat4 = t.toMat4() * p;

    EXPECT_NEAR(viaTransform.x, viaMat4.x, 1e-9);
    EXPECT_NEAR(viaTransform.y, viaMat4.y, 1e-9);
    EXPECT_NEAR(viaTransform.z, viaMat4.z, 1e-9);
}

TEST(Transform3D, InverseUndoesTransform) {
    Quaternion rotation = Quaternion::fromAxisAngle(Vec3(0, 1, 0), PI / 5);
    Vec3 translation(3, -1, 2);
    Transform3D t(rotation, translation);
    Transform3D inv = t.inverse();

    Vec3 p(1, 2, 3);
    Vec3 roundTrip = inv.apply(t.apply(p));

    EXPECT_NEAR(roundTrip.x, p.x, 1e-9);
    EXPECT_NEAR(roundTrip.y, p.y, 1e-9);
    EXPECT_NEAR(roundTrip.z, p.z, 1e-9);
}

TEST(Transform3D, ComposesTwoTransforms) {
    // Two 45-degree rotations around Z, composed, should equal one 90-degree rotation.
    Transform3D a(Quaternion::fromAxisAngle(Vec3(0, 0, 1), PI / 4), Vec3(0, 0, 0));
    Transform3D b(Quaternion::fromAxisAngle(Vec3(0, 0, 1), PI / 4), Vec3(0, 0, 0));
    Transform3D combined = a * b;

    Vec3 result = combined.apply(Vec3(1, 0, 0));
    EXPECT_NEAR(result.x, 0.0, 1e-9);
    EXPECT_NEAR(result.y, 1.0, 1e-9);
    EXPECT_NEAR(result.z, 0.0, 1e-9);
}
