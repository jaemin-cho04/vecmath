#include <linalg/mat4.hpp>
#include <cmath> // for std::sqrt, etc. when you need it
#include <stdexcept> // for std::runtime_error if you choose to throw exceptions

namespace linalg {

    // implement constructor for Mat4
    Mat4::Mat4(double d[4][4]) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                data[i][j] = d[i][j];
            }
        }
    }
}