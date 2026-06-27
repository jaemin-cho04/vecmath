#include <linalg/vec3.hpp>

#include <cmath>

namespace linalg {

Vec3::Vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

Vec3 operator+(const Vec3& a, const Vec3& b) {
    return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 operator-(const Vec3& a, const Vec3& b) {
    return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 operator-(const Vec3& v) {
    return Vec3(-v.x, -v.y, -v.z);
}

Vec3 operator*(const Vec3& a, double s) {
    return Vec3(a.x * s, a.y * s, a.z * s);
}

Vec3 operator/(const Vec3& v, double s) {
    return Vec3(v.x / s, v.y / s, v.z / s);
}

double dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double Vec3::length() const {
    return std::sqrt(dot(*this, *this));
}

Vec3 Vec3::normalized() const {
    double len = length();
    if (len < 1e-9) {
        return Vec3(0, 0, 0);
    }
    return Vec3(x / len, y / len, z / len);
}

Vec3& Vec3::operator+=(const Vec3& v) {
    x += v.x; y += v.y; z += v.z;
    return *this;
}

Vec3& Vec3::operator-=(const Vec3& v) {
    x -= v.x; y -= v.y; z -= v.z;
    return *this;
}

Vec3& Vec3::operator*=(double s) {
    x *= s; y *= s; z *= s;
    return *this;
}

Vec3& Vec3::operator/=(double s) {
    x /= s; y /= s; z /= s;
    return *this;
}

Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

bool operator==(const Vec3& a, const Vec3& b) {
    const double EPSILON = 1e-9;
    return std::abs(a.x - b.x) < EPSILON &&
           std::abs(a.y - b.y) < EPSILON &&
           std::abs(a.z - b.z) < EPSILON;
}

double distance(const Vec3& a, const Vec3& b) {
    return (a - b).length();
}

Vec3 lerp(const Vec3& a, const Vec3& b, double t) {
    return a + (b - a) * t;
}

}  // namespace linalg
