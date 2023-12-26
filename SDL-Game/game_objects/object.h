//
//  Object.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 26/12/23.
//

#pragma once
#include <vector>
#include "sdl_libraries.h"

//apply forces(), player 1, player 2, object, colliders,

class Object
{
public:
    void set_position(int x, int y);
    bool check_collision(std::vector<SDL_Rect>& a_colliders, std::vector<SDL_Rect>& b_colliders);
    void render_colliders(); //for testing

    virtual void handle_event(SDL_Event& event) = 0;
    virtual void update_position() = 0;
    virtual void update_colliders() = 0;
    virtual void render() = 0;
    
protected:
    int m_position_x;
    int m_position_y;
    int m_velocity_x;
    int m_velocity_y;
    std::vector<SDL_Rect> m_colliders;
    SDL_RendererFlip m_flip_state;
};
