#pragma once

#include <cmath>
#include <cstring>
#include "vec3.h"
#include "vec4.h"

namespace rts {
namespace math {

/**
 * 4x4 Matrix
 * User should replace this with their own mat4 implementation
 * Column-major order (OpenGL/Vulkan style)
 */
struct mat4 {
    float m[16];
    
    mat4() {
        identity();
    }
    
    void identity() {
        memset(m, 0, sizeof(m));
        m[0] = m[5] = m[10] = m[15] = 1.0f;
    }
    
    mat4 operator*(const mat4& other) const {
        mat4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i * 4 + j] = 0.0f;
                for (int k = 0; k < 4; k++) {
                    result.m[i * 4 + j] += m[k * 4 + j] * other.m[i * 4 + k];
                }
            }
        }
        return result;
    }
    
    static mat4 translation(const vec3& v) {
        mat4 result;
        result.m[12] = v.x;
        result.m[13] = v.y;
        result.m[14] = v.z;
        return result;
    }
    
    static mat4 rotation_z(float radians) {
        mat4 result;
        float c = cosf(radians);
        float s = sinf(radians);
        result.m[0] = c;  result.m[4] = -s;
        result.m[1] = s;  result.m[5] = c;
        return result;
    }
    
    static mat4 scale(const vec3& v) {
        mat4 result;
        result.m[0] = v.x;
        result.m[5] = v.y;
        result.m[10] = v.z;
        return result;
    }
    
    static mat4 perspective(float fov, float aspect, float near, float far) {
        mat4 result;
        memset(result.m, 0, sizeof(result.m));
        
        float tanHalfFov = tanf(fov / 2.0f);
        result.m[0] = 1.0f / (aspect * tanHalfFov);
        result.m[5] = 1.0f / tanHalfFov;
        result.m[10] = far / (far - near);
        result.m[11] = 1.0f;
        result.m[14] = -(far * near) / (far - near);
        result.m[15] = 0.0f;
        
        return result;
    }
    
    static mat4 look_at(const vec3& eye, const vec3& center, const vec3& up) {
        vec3 f = (center - eye).normalized();
        vec3 s = f.cross(up).normalized();
        vec3 u = s.cross(f);
        
        mat4 result;
        result.m[0] = s.x;
        result.m[4] = s.y;
        result.m[8] = s.z;
        result.m[1] = u.x;
        result.m[5] = u.y;
        result.m[9] = u.z;
        result.m[2] = -f.x;
        result.m[6] = -f.y;
        result.m[10] = -f.z;
        result.m[12] = -s.dot(eye);
        result.m[13] = -u.dot(eye);
        result.m[14] = f.dot(eye);
        result.m[15] = 1.0f;
        
        return result;
    }
};

} // namespace math
} // namespace rts
