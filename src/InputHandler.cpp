#include "InputHandler.h"
#include <cstring>

namespace rts {

InputHandler* InputHandler::s_instance = nullptr;

InputHandler::InputHandler(GLFWwindow* window)
    : m_window(window)
    , m_mouse_x(0.0)
    , m_mouse_y(0.0)
    , m_mouse_prev_x(0.0)
    , m_mouse_prev_y(0.0)
    , m_scroll_delta(0.0f)
{
    // Initialize key states
    memset(m_keys_current, 0, sizeof(m_keys_current));
    memset(m_keys_previous, 0, sizeof(m_keys_previous));
    
    // Initialize mouse button states
    memset(m_mouse_buttons_current, 0, sizeof(m_mouse_buttons_current));
    memset(m_mouse_buttons_previous, 0, sizeof(m_mouse_buttons_previous));
    
    // Set up GLFW callbacks
    s_instance = this;
    glfwSetScrollCallback(m_window, scroll_callback);
    
    // Get initial mouse position
    glfwGetCursorPos(m_window, &m_mouse_x, &m_mouse_y);
    m_mouse_prev_x = m_mouse_x;
    m_mouse_prev_y = m_mouse_y;
}

InputHandler::~InputHandler() {
    s_instance = nullptr;
}

void InputHandler::update() {
    // Copy current states to previous
    memcpy(m_keys_previous, m_keys_current, sizeof(m_keys_current));
    memcpy(m_mouse_buttons_previous, m_mouse_buttons_current, sizeof(m_mouse_buttons_current));
    
    // Update keyboard states
    for (int key = 0; key <= GLFW_KEY_LAST; ++key) {
        m_keys_current[key] = glfwGetKey(m_window, key) == GLFW_PRESS;
    }
    
    // Update mouse button states
    for (int button = 0; button <= GLFW_MOUSE_BUTTON_LAST; ++button) {
        m_mouse_buttons_current[button] = glfwGetMouseButton(m_window, button) == GLFW_PRESS;
    }
    
    // Update mouse position
    m_mouse_prev_x = m_mouse_x;
    m_mouse_prev_y = m_mouse_y;
    glfwGetCursorPos(m_window, &m_mouse_x, &m_mouse_y);
    
    // Reset scroll delta (updated via callback)
    m_scroll_delta = 0.0f;
}

bool InputHandler::is_key_down(int key) const {
    if (key < 0 || key > GLFW_KEY_LAST) return false;
    return m_keys_current[key];
}

bool InputHandler::is_key_pressed(int key) const {
    if (key < 0 || key > GLFW_KEY_LAST) return false;
    return m_keys_current[key] && !m_keys_previous[key];
}

bool InputHandler::is_key_released(int key) const {
    if (key < 0 || key > GLFW_KEY_LAST) return false;
    return !m_keys_current[key] && m_keys_previous[key];
}

bool InputHandler::is_mouse_button_down(int button) const {
    if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST) return false;
    return m_mouse_buttons_current[button];
}

bool InputHandler::is_mouse_button_pressed(int button) const {
    if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST) return false;
    return m_mouse_buttons_current[button] && !m_mouse_buttons_previous[button];
}

bool InputHandler::is_mouse_button_released(int button) const {
    if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST) return false;
    return !m_mouse_buttons_current[button] && m_mouse_buttons_previous[button];
}

void InputHandler::get_mouse_position(double& x, double& y) const {
    x = m_mouse_x;
    y = m_mouse_y;
}

void InputHandler::get_mouse_delta(double& dx, double& dy) const {
    dx = m_mouse_x - m_mouse_prev_x;
    dy = m_mouse_y - m_mouse_prev_y;
}

float InputHandler::get_scroll_delta() const {
    return m_scroll_delta;
}

void InputHandler::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    (void)window;  // Unused
    (void)xoffset; // Only using vertical scroll for now
    if (s_instance) {
        s_instance->m_scroll_delta = static_cast<float>(yoffset);
    }
}

} // namespace rts
