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

Vec3 Vec3::normalized() const {
    double len = length();
    if (len == 0.0) {
        return Vec3(0, 0, 0); // or handle zero-length case as you see fit
    }
    return Vec3(x / len, y / len, z / len);
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

}  // namespace linalg
