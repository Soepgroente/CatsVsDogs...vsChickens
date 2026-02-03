#include "Camera.h"
#include <cmath>

namespace rts {

Camera::Camera()
    : m_position(0.0f, -10.0f, 8.0f)
    , m_target(0.0f, 0.0f, 0.0f)
    , m_up(0.0f, 0.0f, 1.0f)
    , m_distance(12.0f)
    , m_rotation(0.0f)
    , m_pitch(0.785398f)  // ~45 degrees for isometric-ish view
    , m_fov(1.0472f)      // 60 degrees in radians
    , m_aspect_ratio(16.0f / 9.0f)
    , m_near_plane(0.1f)
    , m_far_plane(1000.0f)
    , m_pan_speed(10.0f)
    , m_rotation_speed(1.5f)
    , m_zoom_speed(5.0f)
    , m_min_distance(5.0f)
    , m_max_distance(50.0f)
{
    update_view_matrix();
    m_projection_matrix = math::mat4::perspective(m_fov, m_aspect_ratio, m_near_plane, m_far_plane);
}

Camera::~Camera() {
}

void Camera::update(float delta_time) {
    // Camera movement is handled via pan/rotate/zoom methods called from input
    // This method can be used for smooth interpolation or camera shake in the future
}

void Camera::pan(float dx, float dy) {
    // Pan in world space, accounting for current rotation
    float cos_rot = cosf(m_rotation);
    float sin_rot = sinf(m_rotation);
    
    // Transform movement based on camera rotation
    float world_dx = dx * cos_rot - dy * sin_rot;
    float world_dy = dx * sin_rot + dy * cos_rot;
    
    m_target.x += world_dx;
    m_target.y += world_dy;
    
    update_view_matrix();
}

void Camera::rotate(float angle_delta) {
    m_rotation += angle_delta;
    
    // Normalize rotation to [0, 2*PI)
    while (m_rotation < 0.0f) m_rotation += 6.28318531f;  // 2*PI
    while (m_rotation >= 6.28318531f) m_rotation -= 6.28318531f;
    
    update_view_matrix();
}

void Camera::zoom(float delta) {
    m_distance -= delta;
    
    // Clamp distance
    if (m_distance < m_min_distance) m_distance = m_min_distance;
    if (m_distance > m_max_distance) m_distance = m_max_distance;
    
    update_view_matrix();
}

void Camera::set_perspective(float fov, float aspect_ratio, float near_plane, float far_plane) {
    m_fov = fov;
    m_aspect_ratio = aspect_ratio;
    m_near_plane = near_plane;
    m_far_plane = far_plane;
    
    m_projection_matrix = math::mat4::perspective(m_fov, m_aspect_ratio, m_near_plane, m_far_plane);
}

void Camera::set_position(const math::vec3& position) {
    m_position = position;
    update_view_matrix();
}

void Camera::set_target(const math::vec3& target) {
    m_target = target;
    update_view_matrix();
}

void Camera::update_view_matrix() {
    // Calculate camera position based on target, distance, rotation, and pitch
    float cos_pitch = cosf(m_pitch);
    float sin_pitch = sinf(m_pitch);
    float cos_rot = cosf(m_rotation);
    float sin_rot = sinf(m_rotation);
    
    // Position camera at distance from target
    m_position.x = m_target.x - m_distance * cos_pitch * sin_rot;
    m_position.y = m_target.y - m_distance * cos_pitch * cos_rot;
    m_position.z = m_target.z + m_distance * sin_pitch;
    
    // Create view matrix looking at target
    m_view_matrix = math::mat4::look_at(m_position, m_target, m_up);
}

} // namespace rts
