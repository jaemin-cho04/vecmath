#include <linalg/transform.hpp>

namespace linalg {

    Transform3D::Transform3D(const Quaternion& rotation_, const Vec3& translation_)
        : rotation(rotation_), translation(translation_) {}

    Vec3 Transform3D::apply(const Vec3& point) const {
        return rotation.toRotationMatrix() * point + translation;
    }

    Mat4 Transform3D::toMat4() const {
        return fromRotationTranslation(rotation.toRotationMatrix(), translation);
    }

    Transform3D Transform3D::inverse() const {
        Quaternion invRotation = rotation.conjugate();
        Vec3 invTranslation = invRotation.toRotationMatrix() * (-translation);
        return Transform3D(invRotation, invTranslation);
    }

    Transform3D operator*(const Transform3D& a, const Transform3D& b) {
        Quaternion combinedRotation = a.rotation * b.rotation;
        Vec3 combinedTranslation = a.rotation.toRotationMatrix() * b.translation + a.translation;
        return Transform3D(combinedRotation, combinedTranslation);
    }

}
