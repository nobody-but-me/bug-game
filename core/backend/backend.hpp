
#pragma once
#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <common/enums.hpp>

namespace backEnd
{
    
    void force_window_close( );
    void destroy_application();
    
    bool is_window_open();
    
    int init(const WindowMode& window_mode);
    
    void begin_frame();
    void end_frame();
    
    void loop();
    
    void update(float delta);
    void render();
    void ready();
    
}


#endif//BACKEND_HPP
