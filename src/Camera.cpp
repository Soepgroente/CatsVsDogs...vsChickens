#include "Camera.hpp"
#include <cmath>

namespace rts {

Camera::Camera()
	: position(0.0f, -10.0f, 8.0f)
	, target(0.0f, 0.0f, 0.0f)
	, up(0.0f, 0.0f, 1.0f)
	, distance(12.0f)
	, rotation(0.0f)
	, pitch(0.785398f)  // ~45 degrees for isometric-ish view
	, fov(1.0472f)      // 60 degrees in radians
	, aspect_ratio(16.0f / 9.0f)
	, near_plane(0.1f)
	, far_plane(1000.0f)
	, pan_speed(10.0f)
	, rotation_speed(1.5f)
	, zoospeed(5.0f)
	, min_distance(5.0f)
	, max_distance(50.0f)
{
	update_view_matrix();
	// projection_matrix = mat4::perspective(fov, aspect_ratio, near_plane, far_plane);
}

void	Camera::update(float delta_time)
{
	(void)delta_time; // Unused for now - reserved for future smooth interpolation
	// Camera movement is handled via pan/rotate/zoom methods called from input
	// This method can be used for smooth interpolation or camera shake in the future
}

void	Camera::pan(float dx, float dy)
{
	// Pan in world space, accounting for current rotation
	float cos_rot = cosf(rotation);
	float sin_rot = sinf(rotation);
	
	// Transform movement based on camera rotation
	float world_dx = dx * cos_rot - dy * sin_rot;
	float world_dy = dx * sin_rot + dy * cos_rot;
	
	target.x += world_dx;
	target.y += world_dy;
	
	update_view_matrix();
}

void	Camera::rotate(float angle_delta)
{
	rotation += angle_delta;

	while (rotation < 0.0f)
	{
		rotation += two_pi();
	}
	if (rotation >= two_pi())
	{
		rotation = std::fmod(rotation, two_pi());
	}
	
	update_view_matrix();
}

void	Camera::zoom(float delta)
{
	distance = std::clamp(distance - delta, min_distance, max_distance);	
	update_view_matrix();
}

void	Camera::setPerspective(float fov, float aspect_ratio, float near_plane, float far_plane)
{
	this->fov = fov;
	this->aspect_ratio = aspect_ratio;
	this->near_plane = near_plane;
	this->far_plane = far_plane;
	
	// projection_matrix = mat4::perspective(fov, aspect_ratio, near_plane, far_plane);
}

void	Camera::set_position(const vec3& position)
{
	this->position = position;
	update_view_matrix();
}

void	Camera::set_target(const vec3& target)
{
	this->target = target;
	update_view_matrix();
}

void	Camera::update_view_matrix()
{
	// Calculate camera position based on target, distance, rotation, and pitch
	float	cos_pitch = cosf(pitch);
	float	sin_pitch = sinf(pitch);
	float	cos_rot = cosf(rotation);
	float	sin_rot = sinf(rotation);
	
	// Position camera at distance from target
	position.x = target.x - distance * cos_pitch * sin_rot;
	position.y = target.y - distance * cos_pitch * cos_rot;
	position.z = target.z + distance * sin_pitch;
	
	// Create view matrix looking at target
	// view_matrix = mat4::look_at(position, target, up);
}

} // namespace rts
