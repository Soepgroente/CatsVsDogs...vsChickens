#pragma once

#include <cmath>

namespace rts {
namespace math {

/**
 * 3D Vector
 * User should replace this with their own vec3 implementation
 */
struct vec3 {
    float x, y, z;
    
    vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    
    vec3 operator+(const vec3& other) const {
        return vec3(x + other.x, y + other.y, z + other.z);
    }
    
    vec3 operator-(const vec3& other) const {
        return vec3(x - other.x, y - other.y, z - other.z);
    }
    
    vec3 operator*(float scalar) const {
        return vec3(x * scalar, y * scalar, z * scalar);
    }
    
    vec3 operator/(float scalar) const {
        return vec3(x / scalar, y / scalar, z / scalar);
    }
    
    float dot(const vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    
    vec3 cross(const vec3& other) const {
        return vec3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
    
    float length() const {
        return sqrtf(x * x + y * y + z * z);
    }
    
    vec3 normalized() const {
        float len = length();
        if (len > 0.0f) {
            return vec3(x / len, y / len, z / len);
        }
        return vec3(0.0f, 0.0f, 0.0f);
    }
};

} // namespace math
} // namespace rts
