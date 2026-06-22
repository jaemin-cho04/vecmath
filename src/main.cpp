#include <iostream>
#include <iomanip>
#include <linalg/mat4.hpp>
#include <linalg/mat3.hpp>
#include <linalg/vec3.hpp>
#include <cmath>

constexpr double PI = 3.14159265358979323846;

using linalg::Mat4;
using linalg::Mat3;
using linalg::Vec3;

void printMatrix(const Mat4& m) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            double value = (std::abs(m.data[i][j]) < 1e-9) ? 0.0 : m.data[i][j];
            std::cout << std::setw(8) << std::fixed << std::setprecision(3) << value;
        }
        std::cout << std::endl;
    }
}

double roundToZero(double value) {
    return (std::abs(value) < 1e-9) ? 0.0 : value;
}

int main() {
    double theta1, theta2, theta3, L1, L2, L3;

    std::cout << "Enter theta1 (in degrees): ";
    std::cin >> theta1;

    std::cout << "Enter theta2 (in degrees): ";
    std::cin >> theta2;

    std::cout << "Enter theta3 (in degrees): ";
    std::cin >> theta3;

    std::cout << "Enter L1: ";
    std::cin >> L1;
    
    std::cout << "Enter L2: ";
    std::cin >> L2;

    std::cout << "Enter L3: ";
    std::cin >> L3;

    std::cout << "Link 1: position = (" << L1 << ", 0.0, 0.0), rotation = " << theta1 << " degrees" << std::endl;
    std::cout << "Link 2: position = (" << L2 << ", 0.0, 0.0), rotation = " << theta2 << " degrees" << std::endl;
    std::cout << "Link 3: position = (" << L3 << ", 0.0, 0.0), rotation = " << theta3 << " degrees" << std::endl;

    Vec3 link1Position = Mat3::rotationZ(theta1 * PI / 180.0) * Vec3(L1, 0.0, 0.0);
    Vec3 link2Position = Mat3::rotationZ(theta2 * PI / 180.0) * Vec3(L2, 0.0, 0.0);
    Vec3 link3Position = Mat3::rotationZ(theta3 * PI / 180.0) * Vec3(L3, 0.0, 0.0);

    link1Position = Vec3(roundToZero(link1Position.x), roundToZero(link1Position.y), roundToZero(link1Position.z));
    link2Position = Vec3(roundToZero(link2Position.x), roundToZero(link2Position.y), roundToZero(link2Position.z));
    link3Position = Vec3(roundToZero(link3Position.x), roundToZero(link3Position.y), roundToZero(link3Position.z));

    std::cout << "Link 1 position: (" << link1Position.x << ", " << link1Position.y << ", " << link1Position.z << ")" << std::endl;
    std::cout << "Link 2 position: (" << link2Position.x << ", " << link2Position.y << ", " << link2Position.z << ")" << std::endl;
    std::cout << "Link 3 position: (" << link3Position.x << ", " << link3Position.y << ", " << link3Position.z << ")" << std::endl;

    Mat4 T1 = fromRotationTranslation(Mat3::rotationZ(theta1 * PI / 180.0), link1Position);
    Mat4 T2 = fromRotationTranslation(Mat3::rotationZ(theta2 * PI / 180.0), link2Position);
    Mat4 T3 = fromRotationTranslation(Mat3::rotationZ(theta3 * PI / 180.0), link3Position);

    std::cout << "Transformation matrix T1:" << std::endl;
    printMatrix(T1);
    std::cout << "Transformation matrix T2:" << std::endl;
    printMatrix(T2);
    std::cout << "Transformation matrix T3:" << std::endl;
    printMatrix(T3);

    Mat4 T = T1 * T2 * T3; // combined transformation


    std::cout << "Combined transformation T:" << std::endl;
    printMatrix(T);

    Vec3 endEffector = T * Vec3(0.0, 0.0, 0.0); // transform the origin to get end effector position

    std::cout << "End effector position: (" << endEffector.x << ", " << endEffector.y << ", " << endEffector.z << ")" << std::endl;

    return 0;
}