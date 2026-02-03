#pragma once

#include <cmath>

namespace rts {
namespace math {

/**
 * 2D Vector
 * User should replace this with their own vec2 implementation
 */
struct vec2 {
    float x, y;
    
    vec2() : x(0.0f), y(0.0f) {}
    vec2(float x, float y) : x(x), y(y) {}
    
    vec2 operator+(const vec2& other) const {
        return vec2(x + other.x, y + other.y);
    }
    
    vec2 operator-(const vec2& other) const {
        return vec2(x - other.x, y - other.y);
    }
    
    vec2 operator*(float scalar) const {
        return vec2(x * scalar, y * scalar);
    }
    
    float dot(const vec2& other) const {
        return x * other.x + y * other.y;
    }
    
    float length() const {
        return sqrtf(x * x + y * y);
    }
    
    vec2 normalized() const {
        float len = length();
        if (len > 0.0f) {
            return vec2(x / len, y / len);
        }
        return vec2(0.0f, 0.0f);
    }
};

} // namespace math
} // namespace rts
