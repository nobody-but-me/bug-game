
#include <iostream>
#include <string>
#include <print>

#include <backend/glfw_integration.hpp>
#include <backend/backend.hpp>
#include <common/enums.hpp>

namespace backEnd {
    
    void force_window_close( ) { glfwIntegration::force_window_close(); }
    void destroy_application() { glfwIntegration::destroy(); }
    
    bool is_window_open() { return glfwIntegration::is_window_open(); }
    
    int init(const WindowMode& window_mode) {
	if (glfwIntegration::init(window_mode) == -1) return -1;
	return 0;
    }
    
    void begin_frame() {
	glfwIntegration::begin_frame();
    }
    void end_frame() {
	glfwIntegration::end_frame();
    }
    
    void update(double delta_time);
    void render();
    void ready() {
	std::printf("[INFO] : backend.cpp::ready() : Hello, Dolphine!\n");
    }
    
}
