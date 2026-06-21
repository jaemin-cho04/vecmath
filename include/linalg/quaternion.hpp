#pragma once
#include <linalg/vec3.hpp>

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
        Quaternion normalized() const; // returns a unit quaternion in the same direction
        
        static Quaternion fromAxisAngle(const Vec3& axis, double angle); // creates a quaternion representing a rotation around the given axis by the given angle (in radians)  
    };

    Quaternion operator*(const Quaternion& q1, const Quaternion& q2); // quaternion multiplication

}