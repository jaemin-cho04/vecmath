#pragma once
// tells compiler "only include this file once per compliation unit"

// ============================================================================
//  Vec3 — a 3D vector. THIS IS YOUR FIRST PIECE TO BUILD.
//
//  Right now this is just declarations: the "what", not the "how". Your job
//  is to fill in the implementations in src/vec3.cpp, then prove they work
//  with tests in tests/test_vec3.cpp.
//
//  Suggested order to implement (each one is a small, self-contained win):
//    1. The members + constructors
//    2. operator+ , operator-           (component-wise)
//    3. operator* (scalar)              (scale the vector)
//    4. dot(a, b)                       (returns a scalar)
//    5. length() / norm()               (uses dot, or std::sqrt)
//    6. normalized()                    (length 1, same direction)
//    7. cross(a, b)                     (returns a Vec3 — the 3D-specific one)
//    8. operator== with a tolerance     (floats never compare exactly!)
//
//  Don't ask an AI to write these. Write a rough version yourself first —
//  even a broken one — then debug it. That's the whole point.
// ============================================================================

namespace linalg {
// namespace is folder for names

struct Vec3 {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    // Constructors
    Vec3() = default;
    // tells compiler "generate the default one for me"
    Vec3(double x, double y, double z);
    // with semicolon, its a declaraiton

    // --- Member operations (you decide which are members vs free functions) ---
    double length() const;            // TODO
    // Vec3   normalized() const;        // TODO
};

// --- Free functions (often cleaner than members for binary ops) -------------
Vec3   operator+(const Vec3& a, const Vec3& b);   
Vec3   operator-(const Vec3& a, const Vec3& b);   
Vec3   operator*(const Vec3& v, double s);
double dot(const Vec3& a, const Vec3& b);
Vec3   cross(const Vec3& a, const Vec3& b);

}  // namespace linalg
