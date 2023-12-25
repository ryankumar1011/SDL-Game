//
//  Weapons.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 25/12/23.
//

#include "kunai.h"
#include "texture.h"
#include "global_variables.h"

Kunai::Kunai()
{
    m_position_x = 0;
    m_position_y = 0;
    m_velocity_x = 2;
    m_velocity_y = 0;
    
}

void Kunai::handle_event(SDL_Event& event)
{
    
}
void Kunai::set_position(int x, int y)
{
    m_position_x = x;
    m_position_y = y;
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

void Kunai::render()
{
    kunai_texture.render_texture(m_position_x, m_position_y, nullptr, 0, m_flip_state);
}

