//
//  weapons.h
//  SDL-Game
//
//  Created by Ryan Kumar on 5/11/23.
//

#pragma once

#include "sdl_libraries.h"

class Kunai
{
    
public:
    Kunai();
    void set_position(int x, int y);
    void handle_event(SDL_Event& event);
    void update_position();
    void render();
    
    
private:
    int m_position_x;
    int m_position_y;
    int m_velocity_x;
    int m_velocity_y;
    SDL_RendererFlip m_flip_state;
    
};





