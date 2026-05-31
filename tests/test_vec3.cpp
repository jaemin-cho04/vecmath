#include <gtest/gtest.h>
#include <linalg/vec3.hpp>

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

// --- YOUR TESTS GO HERE ------------------------------------------------------
// Write the test BEFORE or RIGHT AFTER each operation. The pattern:

   TEST(Vec3, AddsComponentwise) {
       Vec3 a(1, 2, 3);
       Vec3 b(4, 5, 6);
       Vec3 c = a + b;
       EXPECT_DOUBLE_EQ(c.x, 5.0);
       EXPECT_DOUBLE_EQ(c.y, 7.0);
       EXPECT_DOUBLE_EQ(c.z, 9.0);
   }

//   TEST(Vec3, DotProduct) {
//       EXPECT_DOUBLE_EQ(dot(Vec3(1, 0, 0), Vec3(0, 1, 0)), 0.0);  // perpendicular
//       EXPECT_DOUBLE_EQ(dot(Vec3(1, 2, 3), Vec3(1, 2, 3)), 14.0); // = length^2
//   }
//
// For length/normalized, floats won't be exact — use EXPECT_NEAR(value, expected, 1e-9).
