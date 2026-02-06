#include "InputHandler.hpp"
#include <cstring>

namespace rts {

InputHandler* InputHandler::s_instance = nullptr;

InputHandler::InputHandler(GLFWwindow* window)
	: window(window)
	, mouse_x(0.0)
	, mouse_y(0.0)
	, mouse_prev_x(0.0)
	, mouse_prev_y(0.0)
	, scroll_delta(0.0f)
{
	// Initialize key states
	memset(keys_current, 0, sizeof(keys_current));
	memset(keys_previous, 0, sizeof(keys_previous));
	
	// Initialize mouse button states
	memset(mouse_buttons_current, 0, sizeof(mouse_buttons_current));
	memset(mouse_buttons_previous, 0, sizeof(mouse_buttons_previous));
	
	// Set up GLFW callbacks
	s_instance = this;
	glfwSetScrollCallback(window, scroll_callback);
	
	// Get initial mouse position
	glfwGetCursorPos(window, &mouse_x, &mouse_y);
	mouse_prev_x = mouse_x;
	mouse_prev_y = mouse_y;
}

InputHandler::~InputHandler() {
	s_instance = nullptr;
}

void InputHandler::update() {
	// Copy current states to previous
	memcpy(keys_previous, keys_current, sizeof(keys_current));
	memcpy(mouse_buttons_previous, mouse_buttons_current, sizeof(mouse_buttons_current));
	
	// Update keyboard states
	for (int key = 0; key <= GLFW_KEY_LAST; ++key) {
		keys_current[key] = glfwGetKey(window, key) == GLFW_PRESS;
	}
	
	// Update mouse button states
	for (int button = 0; button <= GLFW_MOUSE_BUTTON_LAST; ++button) {
		mouse_buttons_current[button] = glfwGetMouseButton(window, button) == GLFW_PRESS;
	}
	
	// Update mouse position
	mouse_prev_x = mouse_x;
	mouse_prev_y = mouse_y;
	glfwGetCursorPos(window, &mouse_x, &mouse_y);
	
	// Reset scroll delta (updated via callback)
	scroll_delta = 0.0f;
}

bool InputHandler::is_key_down(int key) const {
	if (key < 0 || key > GLFW_KEY_LAST) return false;
	return keys_current[key];
}

bool InputHandler::is_key_pressed(int key) const {
	if (key < 0 || key > GLFW_KEY_LAST) return false;
	return keys_current[key] && !keys_previous[key];
}

bool InputHandler::is_key_released(int key) const {
	if (key < 0 || key > GLFW_KEY_LAST) return false;
	return !keys_current[key] && keys_previous[key];
}

bool InputHandler::is_mouse_button_down(int button) const {
	if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST) return false;
	return mouse_buttons_current[button];
}

bool InputHandler::is_mouse_button_pressed(int button) const {
	if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST) return false;
	return mouse_buttons_current[button] && !mouse_buttons_previous[button];
}

bool InputHandler::is_mouse_button_released(int button) const {
	if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST) return false;
	return !mouse_buttons_current[button] && mouse_buttons_previous[button];
}

void InputHandler::get_mouse_position(double& x, double& y) const {
	x = mouse_x;
	y = mouse_y;
}

void InputHandler::get_mouse_delta(double& dx, double& dy) const {
	dx = mouse_x - mouse_prev_x;
	dy = mouse_y - mouse_prev_y;
}

float InputHandler::get_scroll_delta() const {
	return scroll_delta;
}

void InputHandler::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	(void)window;  // Unused
	(void)xoffset; // Only using vertical scroll for now
	if (s_instance) {
		s_instance->scroll_delta = static_cast<float>(yoffset);
	}
}

} // namespace rts
