#include <linalg/quaternion.hpp>
#include <cmath> // for std::sqrt, std::sin, std::cos, etc. when you need it
#include <stdexcept> // for std::runtime_error if you choose to throw exceptions

namespace linalg {

    Quaternion::Quaternion(double w_, double x_, double y_, double z_) : w(w_), x(x_), y(y_), z(z_) {}

    Quaternion Quaternion::normalized() const {
        double len = std::sqrt(w * w + x * x + y * y + z * z);
        if (len < 1e-9) {
            return Quaternion(1, 0, 0, 0); // or handle zero-length case as you see fit
        }
        return Quaternion(w / len, x / len, y / len, z / len);
    }

    Quaternion Quaternion::fromAxisAngle(const Vec3& axis, double angle) {
        Vec3 normAxis = axis.normalized();
        double halfAngle = angle / 2.0;
        double s = std::sin(halfAngle);
        return Quaternion(std::cos(halfAngle), normAxis.x * s, normAxis.y * s, normAxis.z * s);
    }

    Quaternion operator*(const Quaternion& q1, const Quaternion& q2) {
        return Quaternion(
            q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
            q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
            q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
            q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w
        );
    }


}