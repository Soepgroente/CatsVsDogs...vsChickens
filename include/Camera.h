#pragma once

#include "../lib/math/vec3.h"
#include "../lib/math/mat4.h"

namespace rts {

/**
 * Camera System for 2.5D RTS
 * 
 * Controls:
 * - WASD or Arrow Keys: Pan camera across the world
 * - Q/E: Rotate around Z-axis
 * - Mouse Wheel: Zoom in/out
 * 
 * The camera provides view and projection matrices for rendering
 */
class Camera {
public:
    Camera();
    ~Camera();
    
    // Update camera based on input
    void update(float delta_time);
    
    // Movement controls
    void pan(float dx, float dy);
    void rotate(float angle_delta);
    void zoom(float delta);
    
    // Getters for rendering
    const math::mat4& get_view_matrix() const { return m_view_matrix; }
    const math::mat4& get_projection_matrix() const { return m_projection_matrix; }
    
    // Camera configuration
    void set_perspective(float fov, float aspect_ratio, float near_plane, float far_plane);
    void set_position(const math::vec3& position);
    void set_target(const math::vec3& target);
    
    // Camera properties
    const math::vec3& get_position() const { return m_position; }
    const math::vec3& get_target() const { return m_target; }
    float get_distance() const { return m_distance; }
    float get_rotation() const { return m_rotation; }
    
    // Movement parameters
    void set_pan_speed(float speed) { m_pan_speed = speed; }
    void set_rotation_speed(float speed) { m_rotation_speed = speed; }
    void set_zoom_speed(float speed) { m_zoom_speed = speed; }
    
private:
    void update_view_matrix();
    
    // Camera position and orientation
    math::vec3 m_position;      // Camera position
    math::vec3 m_target;        // Point camera is looking at
    math::vec3 m_up;            // Up vector
    
    float m_distance;           // Distance from target
    float m_rotation;           // Rotation around Z-axis (radians)
    float m_pitch;              // Pitch angle for 2.5D view (radians)
    
    // Projection parameters
    float m_fov;
    float m_aspect_ratio;
    float m_near_plane;
    float m_far_plane;
    
    // Movement parameters
    float m_pan_speed;
    float m_rotation_speed;
    float m_zoom_speed;
    
    float m_min_distance;
    float m_max_distance;
    
    // Matrices
    math::mat4 m_view_matrix;
    math::mat4 m_projection_matrix;
};

} // namespace rts
