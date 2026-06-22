#pragma once
#include <initializer_list>
#include <cmath>
#include <stdexcept>



namespace linalg {

    template<typename T, int N>


    struct Vec {
        T data[N];
        
        // Constructors
        Vec() = default;

        Vec(std::initializer_list<T> list) {
            int i = 0;
            for (T value : list) {
                if (i < N) {
                    data[i] = value;
                    i++;
                } else {
                    break; // ignore extra values
                }
            }
        }

        T length() const {
            T sum = 0;
            for (int i = 0; i < N; i++) {
                sum += data[i] * data[i];
            }
            return std::sqrt(sum);
        }

        Vec normalized() const {
            T len = length();
            if (len < 1e-9) {
                throw std::runtime_error("Cannot normalize zero-length vector");
            }
            Vec result;
            for (int i = 0; i < N; i++) {
                result.data[i] = data[i] / len;
            }
            return result;
        }

    };

    template<typename T, int N>
    Vec<T, N> operator+(const Vec<T, N>& a, const Vec<T, N>& b) {
        Vec<T, N> result;
        for (int i = 0; i < N; i++) {
            result.data[i] = a.data[i] + b.data[i];
        }
        return result;
    }

    template<typename T, int N>
    Vec<T, N> operator-(const Vec<T, N>& a, const Vec<T, N>& b) {
        Vec<T, N> result;
        for (int i = 0; i < N; i++) {
            result.data[i] = a.data[i] - b.data[i];
        }
        return result;
    }

    template<typename T, int N>
    Vec<T, N> operator*(const Vec<T, N>& v, T scalar) {
        Vec<T, N> result;
        for (int i = 0; i < N; i++) {
            result.data[i] = v.data[i] * scalar;
        }
        return result;
    }

    template<typename T, int N>
    T dot(const Vec<T, N>& a, const Vec<T, N>& b) {
        T result = 0;
        for (int i = 0; i < N; i++) {
            result += a.data[i] * b.data[i];
        }
        return result;
    }
    
    template<typename T, int N>
    bool operator==(const Vec<T, N>& a, const Vec<T, N>& b) {
        for (int i = 0; i < N; i++) {
            if (std::abs(a.data[i] - b.data[i]) > 1e-9) {
                return false;
            }
        }
        return true;
    }

    template<typename T, int N>
    Vec<T, N> cross(const Vec<T, N>& a, const Vec<T, N>& b) {
        static_assert(N == 3, "Cross product is only defined for 3D vectors");
        Vec<T, N> result;
        result.data[0] = a.data[1] * b.data[2] - a.data[2] * b.data[1];
        result.data[1] = a.data[2] * b.data[0] - a.data[0] * b.data[2];
        result.data[2] = a.data[0] * b.data[1] - a.data[1] * b.data[0];
        return result;
    }

    

}