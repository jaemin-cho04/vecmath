#pragma once
#include <linalg/vec3.hpp>
#include <linalg/mat3.hpp>

namespace linalg {

    struct Quaternion {
        double w = 1.0; // scalar part
        double x = 0.0; // i component
        double y = 0.0; // j component
        double z = 0.0; // k component

        // Constructors
        Quaternion() = default;
        Quaternion(double w, double x, double y, double z);

        // --- Member operations ---
        double length() const; // norm of the quaternion
        Quaternion normalized() const; // returns a unit quaternion in the same direction
        Quaternion conjugate() const; // (w, -x, -y, -z); equals the inverse for unit quaternions
        Quaternion inverse() const; // conjugate / lengthSquared; correct for non-unit quaternions too
        Mat3 toRotationMatrix() const; // converts to the equivalent 3x3 rotation matrix
        Vec3 toEulerAngles() const; // returns (roll, pitch, yaw) in radians, ZYX convention
        Vec3 rotate(const Vec3& v) const; // rotates v by this quaternion (via toRotationMatrix)

        static Quaternion fromAxisAngle(const Vec3& axis, double angle); // creates a quaternion representing a rotation around the given axis by the given angle (in radians)
        static Quaternion fromEulerAngles(double roll, double pitch, double yaw); // ZYX convention (yaw applied first, then pitch, then roll)
    };

    Quaternion operator*(const Quaternion& q1, const Quaternion& q2); // quaternion multiplication
    bool operator==(const Quaternion& a, const Quaternion& b); // tolerance-based equality
    double dot(const Quaternion& a, const Quaternion& b);
    Quaternion slerp(const Quaternion& a, const Quaternion& b, double t); // spherical linear interpolation, t in [0, 1]
    Quaternion toQuaternion(const Mat3& m); // converts a rotation matrix to the equivalent quaternion

}