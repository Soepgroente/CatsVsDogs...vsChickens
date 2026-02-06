#pragma once

#include <GLFW/glfw3.h>

namespace rts {

/**
 * Input Handler - Manages keyboard and mouse input via GLFW
 * Tracks current and previous frame states to detect press/release events
 */
class InputHandler
{
	public:

	InputHandler() = delete;
	InputHandler(GLFWwindow* window);
	~InputHandler();
	InputHandler(const InputHandler&) = delete;
	InputHandler& operator=(const InputHandler&) = delete;

	void    update();

	bool	is_key_down(int key) const;
	bool	is_key_pressed(int key) const;  // True only on the frame the key was pressed
	bool	is_key_released(int key) const; // True only on the frame the key was released
	
	// Mouse queries
	bool	is_mouse_button_down(int button) const;
	bool	is_mouse_button_pressed(int button) const;
	bool	is_mouse_button_released(int button) const;
	
	void	get_mouse_position(double& x, double& y) const;
	void	get_mouse_delta(double& dx, double& dy) const;
	float	get_scroll_delta() const;
	
	private:

	GLFWwindow* window;
	
	bool keys_current[GLFW_KEY_LAST + 1];
	bool keys_previous[GLFW_KEY_LAST + 1];
	
	// Mouse state
	bool mouse_buttons_current[GLFW_MOUSE_BUTTON_LAST + 1];
	bool mouse_buttons_previous[GLFW_MOUSE_BUTTON_LAST + 1];
	
	double mouse_x, mouse_y;
	double mouse_prev_x, mouse_prev_y;
	
	float scroll_delta;
	
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	
	static InputHandler* s_instance;
};

} // namespace rts
