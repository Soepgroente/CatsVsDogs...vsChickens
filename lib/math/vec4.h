#pragma once

#include <cmath>
#include "vec3.h"

namespace rts {
namespace math {

/**
 * 4D Vector
 * User should replace this with their own vec4 implementation
 */
struct vec4 {
    float x, y, z, w;
    
    vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    vec4(const vec3& v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}
    
    vec4 operator+(const vec4& other) const {
        return vec4(x + other.x, y + other.y, z + other.z, w + other.w);
    }
    
    vec4 operator-(const vec4& other) const {
        return vec4(x - other.x, y - other.y, z - other.z, w - other.w);
    }
    
    vec4 operator*(float scalar) const {
        return vec4(x * scalar, y * scalar, z * scalar, w * scalar);
    }
    
    float dot(const vec4& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }
};

} // namespace math
} // namespace rts
