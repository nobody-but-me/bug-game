
#include <iostream>
#include <string>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <common/enums.hpp>
#include <math/delta.hpp>

#include <backend/glfw_integration.hpp>
#include <utils/resource_manager.hpp>
#include <renderer/renderer.hpp>
#include <backend/backend.hpp>
#include <editor/editor.hpp>
#include <utils/log.hpp>

#include <utils/input.hpp>
#include <application.hpp>

namespace BackEnd
{
    
    void force_window_close( ) { GlfwIntegration::force_window_close(); }
    void destroy_application() {
	Editor::destroy();
	GlfwIntegration::destroy();
	return;
    }
    
    bool is_window_open() { return GlfwIntegration::is_window_open(); }
    
    int init(const WindowMode& window_mode) {
	if (GlfwIntegration::init(window_mode) == -1) return -1;
	
	Gfx::Renderer::init();
	InputManager::init(GlfwIntegration::get_current_window());
	Application::ready();
	
	Editor::init(GlfwIntegration::get_current_window());
	Logging::INFO("backend.cpp::init() : backend initialized successfully.");
	Logging::NOTE("Hello, Dolphine!\n");
	return 0;
    }
    
    void begin_frame() {
	GlfwIntegration::begin_frame();
    }
    void end_frame() {
	GlfwIntegration::end_frame();
    }
    
    void loop() {
	begin_frame();
	if (InputManager::is_key_pressed(BUG_ESC)) force_window_close();
	
	Math::Delta::calculate_delta();
	while (Math::Delta::is_frametiming()) {
	    Application::process(Math::Delta::get_delta_time());
	    Math::Delta::update();
	}
	render();
	
	end_frame();
    }
    void render() {
	ResourceManager::render_objects();
	ResourceManager::play_animations();
	Editor::render();
	return;
    }
    
}
