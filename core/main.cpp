
#include <iostream>
#include <backend/backend.hpp>

#include <utils/log.hpp>

int main(int argc, char *argv[]) {
    
    Logging::WARNING("that's a warning %d", 42);
    Logging::ERROR("that's an error %d", 42);
    Logging::FATAL("that's a fatal note %d", 42);
    Logging::NOTE("that's a note %d", 42);
    Logging::TODO("that's a todo note %d", 42);
    Logging::INFO("that's an info note %d", 42);
    Logging::LOG("that's a regular log %d", 42);
    
    if ((BackEnd::init(WindowMode::WINDOWED_MODE)) == -1) return -1;
    
    BackEnd::ready();
    while (BackEnd::is_window_open()) BackEnd::loop();
    
    BackEnd::destroy_application();
    return 0;
}
