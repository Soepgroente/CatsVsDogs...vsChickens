#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include "Camera.h"
#include "InputHandler.h"
#include "Config.h"

// TODO: Include user's Vulkan rendering pipeline headers here

namespace rts {

class Application {
public:
    Application();
    ~Application();
    
    bool initialize();
    void run();
    void shutdown();
    
private:
    void process_input(float delta_time);
    void update(float delta_time);
    void render();
    
    GLFWwindow* m_window;
    Camera* m_camera;
    InputHandler* m_input;
    
    int m_window_width;
    int m_window_height;
    
    bool m_running;
};

Application::Application()
    : m_window(nullptr)
    , m_camera(nullptr)
    , m_input(nullptr)
    , m_window_width(config::DEFAULT_WINDOW_WIDTH)
    , m_window_height(config::DEFAULT_WINDOW_HEIGHT)
    , m_running(true)
{
}

Application::~Application() {
}

bool Application::initialize() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    
    // Configure GLFW for Vulkan (no OpenGL context)
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    
    // Create window
    m_window = glfwCreateWindow(m_window_width, m_window_height, 
                                 config::WINDOW_TITLE, nullptr, nullptr);
    if (!m_window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    
    // Initialize input handler
    m_input = new InputHandler(m_window);
    
    // Initialize camera
    m_camera = new Camera();
    m_camera->set_perspective(config::DEFAULT_FOV,
                             static_cast<float>(m_window_width) / m_window_height,
                             config::CAMERA_NEAR_PLANE,
                             config::CAMERA_FAR_PLANE);
    
    // TODO: Initialize Vulkan rendering pipeline here
    // - Create Vulkan instance
    // - Create surface from GLFW window
    // - Select physical device
    // - Create logical device
    // - Create swapchain
    // - Create render pass
    // - Create framebuffers
    // - Create command pools and buffers
    // - Load shaders and create pipeline
    
    std::cout << "Application initialized successfully" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  WASD / Arrow Keys - Pan camera" << std::endl;
    std::cout << "  Q/E - Rotate camera" << std::endl;
    std::cout << "  Mouse Wheel - Zoom" << std::endl;
    std::cout << "  ESC - Exit" << std::endl;
    
    return true;
}

void Application::process_input(float delta_time) {
    m_input->update();
    
    // Exit on ESC
    if (m_input->is_key_pressed(GLFW_KEY_ESCAPE)) {
        m_running = false;
        return;
    }
    
    // Camera panning with WASD or Arrow Keys
    float pan_amount = m_camera->get_distance() * 0.5f * delta_time;
    if (m_input->is_key_down(GLFW_KEY_W) || m_input->is_key_down(GLFW_KEY_UP)) {
        m_camera->pan(0.0f, pan_amount);
    }
    if (m_input->is_key_down(GLFW_KEY_S) || m_input->is_key_down(GLFW_KEY_DOWN)) {
        m_camera->pan(0.0f, -pan_amount);
    }
    if (m_input->is_key_down(GLFW_KEY_A) || m_input->is_key_down(GLFW_KEY_LEFT)) {
        m_camera->pan(-pan_amount, 0.0f);
    }
    if (m_input->is_key_down(GLFW_KEY_D) || m_input->is_key_down(GLFW_KEY_RIGHT)) {
        m_camera->pan(pan_amount, 0.0f);
    }
    
    // Camera rotation with Q/E
    float rotation_amount = 1.5f * delta_time;
    if (m_input->is_key_down(GLFW_KEY_Q)) {
        m_camera->rotate(rotation_amount);
    }
    if (m_input->is_key_down(GLFW_KEY_E)) {
        m_camera->rotate(-rotation_amount);
    }
    
    // Camera zoom with mouse wheel
    float scroll = m_input->get_scroll_delta();
    if (scroll != 0.0f) {
        m_camera->zoom(scroll * 2.0f);
    }
}

void Application::update(float delta_time) {
    m_camera->update(delta_time);
    
    // TODO: Update game systems here
    // - Entity Component System (ECS) update
    // - Physics simulation
    // - AI / Pathfinding
    // - Unit management
    // - Combat resolution
}

void Application::render() {
    // TODO: Implement Vulkan rendering here
    // 
    // Basic rendering flow:
    // 1. Acquire next swapchain image
    // 2. Record command buffer:
    //    - Begin render pass
    //    - Bind pipeline
    //    - Set viewport and scissor
    //    - Update uniforms (view/projection matrices from camera)
    //    - Draw grid (for ground reference)
    //    - Draw test geometry (cubes, simple units)
    //    - End render pass
    // 3. Submit command buffer
    // 4. Present swapchain image
    //
    // For now, just poll events to keep window responsive
    glfwPollEvents();
}

void Application::run() {
    auto last_time = std::chrono::high_resolution_clock::now();
    
    while (m_running && !glfwWindowShouldClose(m_window)) {
        // Calculate delta time
        auto current_time = std::chrono::high_resolution_clock::now();
        float delta_time = std::chrono::duration<float>(current_time - last_time).count();
        last_time = current_time;
        
        // Limit delta time to prevent large jumps
        if (delta_time > config::MAX_DELTA_TIME) delta_time = config::MAX_DELTA_TIME;
        
        process_input(delta_time);
        update(delta_time);
        render();
    }
}

void Application::shutdown() {
    // TODO: Cleanup Vulkan resources here
    // - Destroy pipeline
    // - Destroy framebuffers
    // - Destroy render pass
    // - Destroy swapchain
    // - Destroy device
    // - Destroy surface
    // - Destroy instance
    
    delete m_camera;
    delete m_input;
    
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
    
    glfwTerminate();
    
    std::cout << "Application shutdown complete" << std::endl;
}

} // namespace rts

int main() {
    rts::Application app;
    
    if (!app.initialize()) {
        std::cerr << "Failed to initialize application" << std::endl;
        return 1;
    }
    
    app.run();
    app.shutdown();
    
    return 0;
}
