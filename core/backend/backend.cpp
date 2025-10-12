
#include <iostream>
#include <string>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <common/object.hpp>
#include <common/enums.hpp>
#include <math/delta.hpp>

#include <backend/glfw_integration.hpp>
#include <utils/resource_manager.hpp>
#include <renderer/renderer.hpp>
#include <backend/backend.hpp>
#include <editor/editor.hpp>
#include <utils/input.hpp>
#include <utils/log.hpp>

namespace BackEnd
{
    
    void force_window_close( ) { GlfwIntegration::force_window_close(); }
    void destroy_application() {
	Editor::destroy();
	GlfwIntegration::destroy();
	return;
    }
    
    bool is_window_open() { return GlfwIntegration::is_window_open(); }
    
    Texture texture;
    Object sprite;
    int index = 0;
    int delay = 0;
    int init(const WindowMode& window_mode) {
	if (GlfwIntegration::init(window_mode) == -1) return -1;
	
	Gfx::Renderer::init();
	
	InputManager::init(GlfwIntegration::get_current_window());
	
	// -- NOTE: this whole logic will be re-placed in the future. It's here for now just for test purposes.
	ResourceManager::load_texture(&texture, "mir", "../../game/res/sprites/sprite_sheet.png", true);
	ResourceManager::init_rectangle(&sprite, "Sprite", &texture);
	
	sprite.colour = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);
	sprite.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	sprite.position = glm::vec2(0.0f, 0.0f);
	sprite.scale = glm::vec2(5.0f, 5.0f);
	sprite.z_index = 0;
	
	sprite.rows = 8; sprite.cols = 8;
	sprite.animated = true;
	
	// -- 
	
	Editor::init(GlfwIntegration::get_current_window());
	Logging::NOTE("backend.cpp::init() : backend initialized successfully.");
	return 0;
    }
    
    void begin_frame() {
	GlfwIntegration::begin_frame();
    }
    void end_frame() {
	GlfwIntegration::end_frame();
    }
    
    void update(float delta) {
	// NOTE : for test purposes.
	if (delay < 9) {
	    delay++;
	} else {
	    delay = 0;
	    index++;
	}
	molson(set_int)("index", index, true, Gfx::Renderer::get_main_shader());
	return;
    }
    void render() {
	ResourceManager::render_objects();
	Editor::render();
	return;
    }
    void ready() { Logging::INFO("Hello, Dolphine!\n"); }
    void loop() {
	begin_frame();
	if (InputManager::is_key_pressed(BUG_ESC)) force_window_close();
	
	Math::Delta::calculate_delta();
	while (Math::Delta::is_frametiming()) {
	    update(Math::Delta::get_delta_time());
	    Math::Delta::update();
	}
	render();
	
	end_frame();
    }
    
}
