#include "Camera.hpp"
#include <cmath>

Camera::Camera()
	: position(0.0f, -10.0f, 8.0f)
	, target(0.0f, 0.0f, 0.0f)
	, up(0.0f, 0.0f, 1.0f)
	, distance(12.0f)
	, rotation(0.0f)
	, pitch(0.785398f)  // ~45 degrees for isometric-ish view
	, fov(1.0472f)      // 60 degrees in radians
	, aspectRatio(16.0f / 9.0f)
	, nearPlane(0.1f)
	, farPlane(1000.0f)
	, panSpeed(10.0f)
	, rotationSpeed(1.5f)
	, zoomSpeed(5.0f)
	, minDistance(5.0f)
	, maxDistance(50.0f)
{
	updateViewMatrix();
	// projection_matrix = mat4::perspective(fov, aspectRatio, nearPlane, farPlane);
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
	float cosRot = cosf(rotation);
	float sinRot = sinf(rotation);
	
	// Transform movement based on camera rotation
	float worldDx = dx * cosRot - dy * sinRot;
	float worldDy = dx * sinRot + dy * cosRot;
	
	target.x += worldDx;
	target.y += worldDy;
	
	updateViewMatrix();
}

void	Camera::rotate(float angleDelta)
{
	rotation += angleDelta;

	while (rotation < 0.0f)
	{
		rotation += two_pi();
	}
	if (rotation >= two_pi())
	{
		rotation = std::fmod(rotation, two_pi());
	}
	
	updateViewMatrix();
}

void	Camera::zoom(float delta)
{
	distance = std::clamp(distance - delta, minDistance, maxDistance);	
	updateViewMatrix();
}

void	Camera::setPerspective(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	this->fov = fov;
	this->aspectRatio = aspectRatio;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
	
	// projection_matrix = mat4::perspective(fov, aspectRatio, nearPlane, farPlane);
}

void	Camera::setViewYXZ(const vec3& position, const vec3& rotation)
{
	this->position = position;
	(void)rotation;
	updateViewMatrix();
}

void	Camera::setPosition(const vec3& position)
{
	this->position = position;
	updateViewMatrix();
}

void	Camera::setTarget(const vec3& target)
{
	this->target = target;
	updateViewMatrix();
}

void	Camera::updateViewMatrix()
{
	// Calculate camera position based on target, distance, rotation, and pitch
	float	cosPitch = cosf(pitch);
	float	sinPitch = sinf(pitch);
	float	cosRot = cosf(rotation);
	float	sinRot = sinf(rotation);
	
	// Position camera at distance from target
	position.x = target.x - distance * cosPitch * sinRot;
	position.y = target.y - distance * cosPitch * cosRot;
	position.z = target.z + distance * sinPitch;
	
	// Create view matrix looking at target
	// view_matrix = mat4::look_at(position, target, up);
}
