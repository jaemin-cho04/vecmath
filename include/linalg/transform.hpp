#pragma once
#include <linalg/vec3.hpp>
#include <linalg/mat4.hpp>
#include <linalg/quaternion.hpp>

namespace linalg {

    // A rigid-body transform: rotation (as a unit quaternion) + translation.
    // This is the SE(3) representation used throughout robotics (it maps
    // directly onto ROS 2's geometry_msgs/Transform: a quaternion + a
    // translation vector), as an alternative to the equivalent Mat4
    // homogeneous-transform representation.
    struct Transform3D {
        Quaternion rotation;
        Vec3 translation;

        Transform3D() = default;
        Transform3D(const Quaternion& rotation, const Vec3& translation);

        Vec3 apply(const Vec3& point) const; // rotate then translate the point
        Mat4 toMat4() const; // equivalent homogeneous 4x4 transform
        Transform3D inverse() const; // the transform that undoes this one
    };

    Transform3D operator*(const Transform3D& a, const Transform3D& b); // compose: apply b, then a

}
