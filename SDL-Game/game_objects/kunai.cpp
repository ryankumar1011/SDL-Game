//
//  Weapons.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 25/12/23.
//

#include "kunai.h"
#include "texture.h"
#include "global_variables.h"

const int Kunai::width = 31;
const int Kunai::height = 15;

Kunai::Kunai()
{
    m_position_x = 0;
    m_position_y = 0;
    m_velocity_x = 0;
    m_velocity_y = 0;

    m_colliders.resize(8);

    m_colliders[0].w = 3;
    m_colliders[0].h = 5;
    
    m_colliders[1].w = 5;
    m_colliders[1].h = 9;
    
    m_colliders[2].w = 5;
    m_colliders[2].h = 5;
    
    m_colliders[3].w = 18;
    m_colliders[3].h = 5;
    
    m_colliders[4].w = 12;
    m_colliders[4].h = 2;
    
    m_colliders[5].w = 6;
    m_colliders[5].h = 3;
    
    m_colliders[6].w = 12;
    m_colliders[6].h = 2;
    
    m_colliders[7].w = 6;
    m_colliders[7].h = 3;
    
    update_colliders();
    
}

void Kunai::handle_event(SDL_Event& event)
{
    
}

void Kunai::update_position()
{
    m_position_x += m_velocity_x;
    m_position_y += m_velocity_y;
    if (((m_position_x + kunai_texture.get_width()) > SCREEN_WIDTH) || (m_position_x < 0))
    {
        m_position_x -= m_velocity_x;
        m_velocity_x = -m_velocity_x;
        (m_flip_state == SDL_FLIP_NONE) ? m_flip_state = SDL_FLIP_HORIZONTAL : m_flip_state = SDL_FLIP_NONE;
    }
    
}

void Kunai::update_colliders()
{
    m_colliders[0].x = m_position_x + 0;
    m_colliders[0].y = m_position_y + 5;
 
    m_colliders[1].x = m_position_x + 3;
    m_colliders[1].y = m_position_y + 3;
    
    m_colliders[2].x = m_position_x + 8;
    m_colliders[2].y = m_position_y + 5;
    
    m_colliders[3].x = m_position_x + 13;
    m_colliders[3].y = m_position_y + 5;
    
    m_colliders[4].x = m_position_x + 13;
    m_colliders[4].y = m_position_y + 10;
    
    m_colliders[5].x = m_position_x + 15;
    m_colliders[5].y = m_position_y + 12;
    
    m_colliders[6].x = m_position_x + 13;
    m_colliders[6].y = m_position_y + 3;
    
    m_colliders[7].x = m_position_x + 15;
    m_colliders[7].y = m_position_y + 0;
   
}

void Kunai::render()
{
    kunai_texture.render_texture(m_position_x, m_position_y, nullptr, 0, m_flip_state);
}

//This function is ONLY FOR TESTING. It renderes a kunai scaled 20 times larger.

void Kunai::render_scaled_kunai()
{
    SDL_Rect enlarged_rect = {25, 25, 620, 300}; // we are upscaling the kunai 20 times to see it clearly
    
    SDL_RenderCopy(gp_renderer, kunai_texture.get_texture_pointer(), nullptr, &enlarged_rect);
}

//This function is ONLY FOR TESTING. It scales the kunai colliders 20 times. It should be called outside game loop

void Kunai::scale_colliders()
{
    for (int i = 0; i < m_colliders.size(); i++)
    {
        m_colliders[i].x = 25 + m_colliders[i].x*20;
        m_colliders[i].y = 25 + m_colliders[i].y*20;
        m_colliders[i].w = m_colliders[i].w*20;
        m_colliders[i].h = m_colliders[i].h*20;
    }
}
