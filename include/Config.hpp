#pragma once

/**
 * Configuration file for the RTS game
 * Compile-time constants and settings
 */

namespace rts {

namespace config
{

// Window settings
constexpr int DEFAULT_WINDOW_WIDTH = 1280;
constexpr int DEFAULT_WINDOW_HEIGHT = 720;
constexpr const char* WINDOW_TITLE = "Cats vs Dogs... vs Chickens";

// Camera settings
constexpr float DEFAULT_FOV = 1.0472f;          // 60 degrees in radians
constexpr float CAMERA_NEAR_PLANE = 0.1f;
constexpr float CAMERA_FAR_PLANE = 1000.0f;
constexpr float CAMERA_DEFAULT_DISTANCE = 12.0f;
constexpr float CAMERA_MIN_DISTANCE = 5.0f;
constexpr float CAMERA_MAX_DISTANCE = 50.0f;
constexpr float CAMERA_DEFAULT_PITCH = 0.785398f; // ~45 degrees for isometric view

// Movement speeds
constexpr float CAMERA_PAN_SPEED = 10.0f;
constexpr float CAMERA_ROTATION_SPEED = 1.5f;
constexpr float CAMERA_ZOOSPEED = 5.0f;

// Game settings
constexpr float MAX_DELTA_TIME = 0.1f;          // Cap delta time to prevent large jumps

// TODO: Add settings for:
// - Unit selection
// - Pathfinding grid resolution
// - Maximum units per faction
// - Network settings (for multiplayer)

} // namespace config
} // namespace rts
