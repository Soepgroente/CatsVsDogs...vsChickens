#pragma once

#include "Vectors.hpp"

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
class Camera
{
	public:
	
	Camera();
	~Camera() = default;
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	void	update(float delta_time);
	void	pan(float dx, float dy);
	void	rotate(float angle_delta);
	void	zoom(float delta);
	
	const mat4&	get_view_matrix() const { return view_matrix; }
	const mat4&	get_projection_matrix() const { return projection_matrix; }
	const vec3&	get_position() const { return position; }
	const vec3&	get_target() const { return target; }

	void	setPerspective(float fov, float aspect_ratio, float near_plane, float far_plane);
	void	set_position(const vec3& position);
	void	set_target(const vec3& target);

	float	get_distance() const { return distance; }
	float	get_rotation() const { return rotation; }
	void	set_pan_speed(float speed) { pan_speed = speed; }
	void	set_rotation_speed(float speed) { rotation_speed = speed; }
	void	set_zoospeed(float speed) { zoospeed = speed; }
	
	private:

	void	update_view_matrix();
	
	vec3	position;
	vec3	target;
	vec3	up;
	
	float	distance;
	float	rotation;
	float	pitch;		// Pitch angle for 2.5D view (radians)
	
	// Projection parameters
	float	fov;
	float	aspect_ratio;
	float	near_plane;
	float	far_plane;
	
	// Movement parameters
	float	pan_speed;
	float	rotation_speed;
	float	zoospeed;

	float	min_distance;
	float	max_distance;

	mat4	view_matrix;
	mat4	projection_matrix;
};

} // namespace rts
