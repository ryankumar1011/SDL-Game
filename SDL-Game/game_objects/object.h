//
//  Object.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 26/12/23.
//

#pragma once
#include <vector>
#include "sdl_libraries.h"

//test collision detection
//apply forces(), player 1, player 2, object, colliders,
//apply friction, gravity, bounciness

class Object
{
    
public:
    void set_position(float x, float y);
    void change_var(float& var, float amount, float cap);
    bool check_collision(Object* other);
    void flip_colliders();
    std::vector<SDL_FRect>& get_colliders();
    void render_colliders(); //for testing

    virtual void handle_event(SDL_Event& event) = 0;
    virtual void update_position() = 0;
    virtual void update_colliders() = 0;
    virtual void render() = 0;
    
protected:
    int m_width;
    int m_height;
    float m_position_x;
    float m_position_y;
    float m_velocity_x;
    float m_velocity_y;
    float m_acceleration_x;
    float m_acceleration_y;

    std::vector<SDL_FRect> m_colliders;
    SDL_RendererFlip m_flip_state;
    
};
