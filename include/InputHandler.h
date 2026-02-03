#pragma once

#include <GLFW/glfw3.h>

namespace rts {

/**
 * Input Handler - Manages keyboard and mouse input via GLFW
 * Tracks current and previous frame states to detect press/release events
 */
class InputHandler {
public:
    InputHandler(GLFWwindow* window);
    ~InputHandler();
    
    // Update input state - call once per frame before processing input
    void update();
    
    // Keyboard queries
    bool is_key_down(int key) const;
    bool is_key_pressed(int key) const;  // True only on the frame the key was pressed
    bool is_key_released(int key) const; // True only on the frame the key was released
    
    // Mouse queries
    bool is_mouse_button_down(int button) const;
    bool is_mouse_button_pressed(int button) const;
    bool is_mouse_button_released(int button) const;
    
    void get_mouse_position(double& x, double& y) const;
    void get_mouse_delta(double& dx, double& dy) const;
    float get_scroll_delta() const;
    
private:
    GLFWwindow* m_window;
    
    // Keyboard state
    bool m_keys_current[GLFW_KEY_LAST + 1];
    bool m_keys_previous[GLFW_KEY_LAST + 1];
    
    // Mouse state
    bool m_mouse_buttons_current[GLFW_MOUSE_BUTTON_LAST + 1];
    bool m_mouse_buttons_previous[GLFW_MOUSE_BUTTON_LAST + 1];
    
    double m_mouse_x, m_mouse_y;
    double m_mouse_prev_x, m_mouse_prev_y;
    
    float m_scroll_delta;
    
    // GLFW callbacks
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    
    // Callback user pointer data
    static InputHandler* s_instance;
};

} // namespace rts
