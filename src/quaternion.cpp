#include <linalg/quaternion.hpp>
#include <cmath>
#include <stdexcept>
#include <algorithm>

namespace linalg {

    Quaternion::Quaternion(double w_, double x_, double y_, double z_) : w(w_), x(x_), y(y_), z(z_) {}

    double Quaternion::length() const {
        return std::sqrt(w * w + x * x + y * y + z * z);
    }

    Quaternion Quaternion::normalized() const {
        double len = length();
        if (len < 1e-9) {
            return Quaternion(1, 0, 0, 0);
        }
        return Quaternion(w / len, x / len, y / len, z / len);
    }

    Quaternion Quaternion::conjugate() const {
        return Quaternion(w, -x, -y, -z);
    }

    Quaternion Quaternion::inverse() const {
        double lenSq = w * w + x * x + y * y + z * z;
        Quaternion c = conjugate();
        return Quaternion(c.w / lenSq, c.x / lenSq, c.y / lenSq, c.z / lenSq);
    }

    Vec3 Quaternion::rotate(const Vec3& v) const {
        return toRotationMatrix() * v;
    }

    Mat3 Quaternion::toRotationMatrix() const {
        Quaternion q = normalized();
        double d[3][3] = {
            {1 - 2 * (q.y * q.y + q.z * q.z),     2 * (q.x * q.y - q.w * q.z),     2 * (q.x * q.z + q.w * q.y)},
            {    2 * (q.x * q.y + q.w * q.z), 1 - 2 * (q.x * q.x + q.z * q.z),     2 * (q.y * q.z - q.w * q.x)},
            {    2 * (q.x * q.z - q.w * q.y),     2 * (q.y * q.z + q.w * q.x), 1 - 2 * (q.x * q.x + q.y * q.y)}
        };
        return Mat3(d);
    }

    Vec3 Quaternion::toEulerAngles() const {
        Quaternion q = normalized();

        double sinrCosp = 2 * (q.w * q.x + q.y * q.z);
        double cosrCosp = 1 - 2 * (q.x * q.x + q.y * q.y);
        double roll = std::atan2(sinrCosp, cosrCosp);

        double sinp = std::clamp(2 * (q.w * q.y - q.z * q.x), -1.0, 1.0);
        double pitch = std::asin(sinp);

        double sinyCosp = 2 * (q.w * q.z + q.x * q.y);
        double cosyCosp = 1 - 2 * (q.y * q.y + q.z * q.z);
        double yaw = std::atan2(sinyCosp, cosyCosp);

        return Vec3(roll, pitch, yaw);
    }

    Quaternion Quaternion::fromAxisAngle(const Vec3& axis, double angle) {
        Vec3 normAxis = axis.normalized();
        double halfAngle = angle / 2.0;
        double s = std::sin(halfAngle);
        return Quaternion(std::cos(halfAngle), normAxis.x * s, normAxis.y * s, normAxis.z * s);
    }

    Quaternion Quaternion::fromEulerAngles(double roll, double pitch, double yaw) {
        double cr = std::cos(roll * 0.5);
        double sr = std::sin(roll * 0.5);
        double cp = std::cos(pitch * 0.5);
        double sp = std::sin(pitch * 0.5);
        double cy = std::cos(yaw * 0.5);
        double sy = std::sin(yaw * 0.5);

        return Quaternion(
            cr * cp * cy + sr * sp * sy,
            sr * cp * cy - cr * sp * sy,
            cr * sp * cy + sr * cp * sy,
            cr * cp * sy - sr * sp * cy
        );
    }

    Quaternion operator*(const Quaternion& q1, const Quaternion& q2) {
        return Quaternion(
            q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
            q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
            q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
            q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w
        );
    }

    bool operator==(const Quaternion& a, const Quaternion& b) {
        const double EPSILON = 1e-9;
        return std::abs(a.w - b.w) < EPSILON &&
               std::abs(a.x - b.x) < EPSILON &&
               std::abs(a.y - b.y) < EPSILON &&
               std::abs(a.z - b.z) < EPSILON;
    }

    double dot(const Quaternion& a, const Quaternion& b) {
        return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
    }

    Quaternion slerp(const Quaternion& a, const Quaternion& b, double t) {
        double d = dot(a, b);

        // Take the shorter path around the hypersphere.
        Quaternion bb = b;
        if (d < 0.0) {
            bb = Quaternion(-b.w, -b.x, -b.y, -b.z);
            d = -d;
        }

        // Nearly parallel: fall back to linear interpolation to avoid
        // dividing by a near-zero sin(theta0).
        if (d > 0.9995) {
            Quaternion result(
                a.w + t * (bb.w - a.w),
                a.x + t * (bb.x - a.x),
                a.y + t * (bb.y - a.y),
                a.z + t * (bb.z - a.z)
            );
            return result.normalized();
        }

        double theta0 = std::acos(d);
        double theta = theta0 * t;
        double sinTheta0 = std::sin(theta0);
        double sinTheta = std::sin(theta);

        double s0 = std::cos(theta) - d * sinTheta / sinTheta0;
        double s1 = sinTheta / sinTheta0;

        return Quaternion(
            s0 * a.w + s1 * bb.w,
            s0 * a.x + s1 * bb.x,
            s0 * a.y + s1 * bb.y,
            s0 * a.z + s1 * bb.z
        );
    }

    // Shepherd's method: numerically robust matrix-to-quaternion conversion
    // that avoids dividing by a near-zero term by picking whichever of
    // w/x/y/z is largest as the one to solve for directly.
    Quaternion toQuaternion(const Mat3& m) {
        double trace = m.data[0][0] + m.data[1][1] + m.data[2][2];

        if (trace > 0.0) {
            double s = std::sqrt(trace + 1.0) * 2.0;
            return Quaternion(
                0.25 * s,
                (m.data[2][1] - m.data[1][2]) / s,
                (m.data[0][2] - m.data[2][0]) / s,
                (m.data[1][0] - m.data[0][1]) / s
            );
        } else if (m.data[0][0] > m.data[1][1] && m.data[0][0] > m.data[2][2]) {
            double s = std::sqrt(1.0 + m.data[0][0] - m.data[1][1] - m.data[2][2]) * 2.0;
            return Quaternion(
                (m.data[2][1] - m.data[1][2]) / s,
                0.25 * s,
                (m.data[0][1] + m.data[1][0]) / s,
                (m.data[0][2] + m.data[2][0]) / s
            );
        } else if (m.data[1][1] > m.data[2][2]) {
            double s = std::sqrt(1.0 + m.data[1][1] - m.data[0][0] - m.data[2][2]) * 2.0;
            return Quaternion(
                (m.data[0][2] - m.data[2][0]) / s,
                (m.data[0][1] + m.data[1][0]) / s,
                0.25 * s,
                (m.data[1][2] + m.data[2][1]) / s
            );
        } else {
            double s = std::sqrt(1.0 + m.data[2][2] - m.data[0][0] - m.data[1][1]) * 2.0;
            return Quaternion(
                (m.data[1][0] - m.data[0][1]) / s,
                (m.data[0][2] + m.data[2][0]) / s,
                (m.data[1][2] + m.data[2][1]) / s,
                0.25 * s
            );
        }
    }

}