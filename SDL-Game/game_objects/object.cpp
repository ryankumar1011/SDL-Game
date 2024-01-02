//
//  Object.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 26/12/23.
//

#include "object.h"
#include "global_variables.h"

void Object::set_position(float x, float y)
{
    m_position_x = x;
    m_position_y = y;
}

void Object::set_velocity(float x, float y)
{
    m_velocity_x = x;
    m_velocity_y = y;
}

void Object::change_var(float& var, float amount, float cap)
{
    float new_var{};
    
    if (amount > 0) cap = abs(cap);
    
    else cap = - abs(cap);
    
    new_var = var + amount;
    
    if ((cap >= 0 && new_var <= cap) || (cap < 0 && new_var >= cap))
    {
        var = new_var;
    }
    else
    {
        var = cap;
    }
}

//This function uses seperate axis theorem to check for a collision. This can be easily done by SDL function SDL_HasIntersection(), but this is just for practice.

bool Object::check_collision(Object* other)
{
    std::vector<SDL_FRect>& other_colliders = other->get_colliders();
    
    float m_left;
    float m_right;
    float m_top;
    float m_bottom;
    
    float other_left;
    float other_right;
    float other_top;
    float other_bottom;
    
    for (auto& i : m_colliders)
    {
        m_left = i.x;
        m_top = i.y;
        m_right = i.x + i.w;
        m_bottom = i.y + i.h;
        
        for (auto& j : other_colliders)
        {
            other_left = j.x;
            other_top = j.y;
            other_right = j.x + j.w;
            other_bottom = j.y + j.h;
            if (((m_bottom <= other_top) || (m_top >= other_bottom) || (m_right <= other_left) || (m_left >= other_right)) == false)
            {
                return true;
            }
        }
    }
    return false;
}

std::vector<SDL_FRect>& Object::get_colliders()
{
    return m_colliders;
}

float Object::get_scale_factor()
{
    return 1;
}

void Object::scale_colliders()
{
    for (auto& i : m_colliders)
    {
        i.w *= get_scale_factor();
        i.h *= get_scale_factor();
    }
}

void Object::update_colliders_scaled()
{
    for (auto& i : m_colliders)
    {
        i.x = m_position_x + (i.x - m_position_x)*get_scale_factor();
        i.y = m_position_y + (i.y - m_position_y)*get_scale_factor();
    }
}


void Object::flip_colliders()
{
    for (auto& i : m_colliders)
    {
        //the x position of the left side will be changed, so m_collider[i].x is changed accordingly
        i.x = m_position_x + (get_width() - (i.x - m_position_x));
        
        //since the collider's left x position becomes the right x position when horizontally flipped, we need to change m_collider[i].x to the new left position
        i.x = i.x - i.w;
    }
}

//This function is for testing. It is used to render the positions of the colliders.

void Object::render_colliders()
{
    SDL_SetRenderDrawColor(gp_renderer, 0x00, 0x00, 0x00, 0xFF);
    
    for (auto& i : m_colliders)
    {
        SDL_RenderDrawRectF(gp_renderer, &i);
    }
}

