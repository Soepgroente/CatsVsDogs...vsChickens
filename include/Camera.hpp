#pragma once

#include "Vectors.hpp"

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

	void	update(float deltaTime);
	void	pan(float dx, float dy);
	void	rotate(float angleDelta);
	void	zoom(float delta);
	
	const mat4&	getViewMatrix() const { return viewMatrix; }
	const mat4&	getProjectionMatrix() const { return projectionMatrix; }
	const vec3&	getPosition() const { return position; }
	const vec3&	getTarget() const { return target; }

	void	setPerspective(float fov, float aspectRatio, float nearPlane, float farPlane);
	void	setPosition(const vec3& position);
	void	setViewYXZ(const vec3& position, const vec3& rotation);
	void	setTarget(const vec3& target);

	float	getDistance() const { return distance; }
	float	getRotation() const { return rotation; }
	void	setPanSpeed(float speed) { panSpeed = speed; }
	void	setRotationSpeed(float speed) { rotationSpeed = speed; }
	void	setZoomSpeed(float speed) { zoomSpeed = speed; }
	
	private:

	void	updateViewMatrix();
	
	vec3	position;
	vec3	target;
	vec3	up;
	
	float	distance;
	float	rotation;
	float	pitch;		// Pitch angle for 2.5D view (radians)
	
	// Projection parameters
	float	fov;
	float	aspectRatio;
	float	nearPlane;
	float	farPlane;
	
	// Movement parameters
	float	panSpeed;
	float	rotationSpeed;
	float	zoomSpeed;

	float	minDistance;
	float	maxDistance;

	mat4	viewMatrix;
	mat4	projectionMatrix;
};
