
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
    Object sprite, sprite2;
    int index = 0;
    int delay = 0;
    int init(const WindowMode& window_mode) {
	if (GlfwIntegration::init(window_mode) == -1) return -1;
	
	Gfx::Renderer::init();
	
	InputManager::init(GlfwIntegration::get_current_window());
	
	// -- NOTE: this whole logic will be re-placed in the future. It's here for now just for test purposes.
	ResourceManager::load_texture(&texture, "mir", "../../game/res/sprites/sprite_sheet.png", true);
	ResourceManager::init_rectangle(&sprite2, "Sprite2", &texture);
	ResourceManager::init_rectangle(&sprite, "Sprite", &texture);
	
	sprite.colour = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);
	sprite.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	sprite.position = glm::vec2(-2.5f, 0.0f);
	sprite.scale = glm::vec2(5.0f, 5.0f);
	sprite.z_index = 0;
	
	sprite2.colour = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);
	sprite2.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	sprite2.position = glm::vec2(10.0f, 0.0f);
	sprite2.scale = glm::vec2(-5.0f, 5.0f);
	sprite2.z_index = -5;
	
	sprite2.animated = true; sprite.animated = true;
	sprite2.rows = 8; sprite2.cols = 8;
	sprite.rows = 8; sprite.cols = 8;
	
	ResourceManager::init_animation(&sprite.animation , "animation" , AnimationType::ONCE, 3, 0, true);
	ResourceManager::init_animation(&sprite2.animation, "animation2", AnimationType::PING_PONG, 5, 0, true);
	
	// NOTE: Are the bellow numbers magic-numbers? Sort of. These are the frame numbers relative to the sprite sheet loaded by this object. This will be useful when the game engine have a visual animation timeline where you will be able to set up the frames visually, just like in game engines like unity and godot, for example.
	sprite2.animation.set_frames({9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21});
	sprite.animation.set_frames({ 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 1 });
	
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
	return;
    }
    void render() {
	ResourceManager::render_objects();
	ResourceManager::play_animations();
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
