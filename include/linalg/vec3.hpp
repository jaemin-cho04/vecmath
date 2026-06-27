#pragma once

namespace linalg {

struct Vec3 {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    Vec3() = default;
    Vec3(double x, double y, double z);

    double length() const;
    Vec3   normalized() const;

    Vec3& operator+=(const Vec3& v);
    Vec3& operator-=(const Vec3& v);
    Vec3& operator*=(double s);
    Vec3& operator/=(double s);
};

Vec3   operator+(const Vec3& a, const Vec3& b);
Vec3   operator-(const Vec3& a, const Vec3& b);
Vec3   operator-(const Vec3& v);                  // unary negation
Vec3   operator*(const Vec3& v, double s);
Vec3   operator/(const Vec3& v, double s);
double dot(const Vec3& a, const Vec3& b);
Vec3   cross(const Vec3& a, const Vec3& b);
bool   operator==(const Vec3& a, const Vec3& b);  // tolerance-based equality
double distance(const Vec3& a, const Vec3& b);    // length of (a - b)
Vec3   lerp(const Vec3& a, const Vec3& b, double t); // linear interpolation, t in [0, 1]

}  // namespace linalg
