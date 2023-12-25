//
//  weapons.h
//  SDL-Game
//
//  Created by Ryan Kumar on 5/11/23.
//

#pragma once

#include "sdl_libraries.h"
#include <vector>

class Kunai
{
public:
    static const int width;
    static const int height;
    
public:
    Kunai();
    void set_position(int x, int y);
    void handle_event(SDL_Event& event);
    void update_position();
    bool check_collision();
    void render();
    
    //for testing
    void render_colliders();
    void render_scaled_kunai();
    void scale_colliders();
    
private:
    int m_position_x;
    int m_position_y;
    int m_velocity_x;
    int m_velocity_y;
    
    std::vector<SDL_Rect> m_collider;
    SDL_RendererFlip m_flip_state;
    
};





