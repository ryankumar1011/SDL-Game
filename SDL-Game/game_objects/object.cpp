//
//  Object.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 26/12/23.
//

#include "object.h"
#include "global_variables.h"

void Object::set_position(int x, int y)
{
    m_position_x = x;
    m_position_y = y;
}

//This function uses seperate axis theorem to check for a collision. This can be easily done by SDL function SDL_HasIntersection(), but this is just for practice.

bool Object::check_collision(std::vector<SDL_Rect>& a_colliders, std::vector<SDL_Rect>& b_colliders)
{
    int a_left;
    int a_right;
    int a_top;
    int a_bottom;
    
    int b_left;
    int b_right;
    int b_top;
    int b_bottom;
    
    for (int i = 0; i < a_colliders.size(); i++)
    {
        a_left = a_colliders[i].x;
        a_top = a_colliders[i].y;
        a_right = a_colliders[i].x + a_colliders[i].w;
        a_bottom = a_colliders[i].y + a_colliders[i].h;
        
        for (int i = 0; i < b_colliders.size(); i++)
        {
            b_left = b_colliders[i].x;
            b_top = b_colliders[i].y;
            b_right = b_colliders[i].x + b_colliders[i].w;
            b_bottom = b_colliders[i].y + b_colliders[i].h;
            
            if ((a_bottom <= b_top) || (b_bottom <= a_top) || (a_right <= b_left) || (b_right <= a_left) == false)
            {
                return true;
            }
        }
    }
            
    return false;
}

//This function is ONLY FOR TESTING. It is used to render the positions of the colliders.
//To check the position of colliders more easily, first scale_colliders() and render_scaled_kunai() can be called to render enlarged kunai and change its colliders
//Note::scale_colliders() should be called outside game loop - colliders should only be scalled once

void Object::render_colliders()
{
    SDL_SetRenderDrawColor(gp_renderer, 0x00, 0x00, 0x00, 0xFF);
    
    for (int i = 0; i < m_colliders.size(); i++)
    {
        SDL_RenderDrawRect(gp_renderer, &m_colliders[i]);
    }
    
}
