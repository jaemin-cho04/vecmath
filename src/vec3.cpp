#include <linalg/vec3.hpp>
// pulls its own header, needs to know what Vec3 looks like before it can define functions

#include <cmath> // for std::sqrt, etc. when you need it

// You implement everything here. One definition is provided so the project
// compiles and links cleanly on a fresh clone — replace/extend as you go.

namespace linalg {

Vec3::Vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
// definition of second constructor 
// :: means look inside this thing

Vec3 operator+(const Vec3& a, const Vec3& b) {
    return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}
// Vec3 at the top is the return type
// const means just reading
// & enforces no copy is made when calling function

Vec3 operator-(const Vec3& a, const Vec3& b) {
    return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 operator*(const Vec3& a, double s) {
    return Vec3(a.x * s, a.y * s, a.z * s);
}

double dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
// dot (a, b) = length^2

double Vec3::length() const {
    return std::sqrt(dot(*this, *this));
}
// std is for standard library 
// *this is how member function refers to itself


// TODO: define operator+, operator-, operator* (scalar), dot, cross,
//       length, normalized, etc. — matching whatever you declare in the header.

}  // namespace linalg
