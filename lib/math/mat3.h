#pragma once

#include <cmath>
#include <cstring>

namespace rts {
namespace math {

/**
 * 3x3 Matrix
 * User should replace this with their own mat3 implementation
 */
struct mat3 {
    float m[9];  // Column-major order
    
    mat3() {
        identity();
    }
    
    void identity() {
        memset(m, 0, sizeof(m));
        m[0] = m[4] = m[8] = 1.0f;
    }
    
    static mat3 rotation_z(float radians) {
        mat3 result;
        float c = cosf(radians);
        float s = sinf(radians);
        result.m[0] = c;  result.m[3] = -s; result.m[6] = 0.0f;
        result.m[1] = s;  result.m[4] = c;  result.m[7] = 0.0f;
        result.m[2] = 0.0f; result.m[5] = 0.0f; result.m[8] = 1.0f;
        return result;
    }
};

} // namespace math
} // namespace rts
