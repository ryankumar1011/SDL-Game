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
    
    for (int i = 0; i < m_colliders.size(); i++)
    {
        m_left = m_colliders[i].x;
        m_top = m_colliders[i].y;
        m_right = m_colliders[i].x + m_colliders[i].w;
        m_bottom = m_colliders[i].y + m_colliders[i].h;
        
        for (int j = 0; j < other_colliders.size(); j++)
        {
            other_left = other_colliders[j].x;
            other_top = other_colliders[j].y;
            other_right = other_colliders[j].x + other_colliders[j].w;
            other_bottom = other_colliders[j].y + other_colliders[j].h;
            
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

void Object::flip_colliders()
{
    for (int i = 0; i < m_colliders.size(); i++)
    {
        //the x position of the left side will be changed, so m_collider[i].x is changed accordingly
        m_colliders[i].x = m_position_x + (get_width() - (m_colliders[i].x - m_position_x));
        
        //since the collider's left x position becomes the right x position when horizontally flipped, we need to change m_collider[i].x to the new left position
        m_colliders[i].x = m_colliders[i].x - m_colliders[i].w;
    }
}

//This function is ONLY FOR TESTING. It is used to render the positions of the colliders.
//To check the position of colliders more easily, first scale_colliders() and render_scaled_kunai() can be called to render enlarged kunai and change its colliders
//Note::scale_colliders() should be called outside game loop - colliders should only be scalled once

void Object::render_colliders()
{
    SDL_SetRenderDrawColor(gp_renderer, 0x00, 0x00, 0x00, 0xFF);
    
    for (int i = 0; i < m_colliders.size(); i++)
    {
        SDL_RenderDrawRectF(gp_renderer, &m_colliders[i]);
    }
    
}

