
#include <iostream>

#include <backend/backend.hpp>

int main(int argc, char *argv[]) {
    if ((backEnd::init(WindowMode::WINDOWED_MODE)) == -1) return -1;
    backEnd::ready();
    while (backEnd::is_window_open()) {
	backEnd::begin_frame();
	
	// main loop
	
	backEnd::end_frame();
    }
    backEnd::destroy_application();
    return 0;
}
