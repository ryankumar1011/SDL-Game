//
//  Weapons.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 25/12/23.
//

#include "kunai.h"
#include "player.h"
#include "texture.h"
#include "game_objects.h"
#include "global_variables.h"

Texture Kunai::m_texture;

Texture& Kunai::get_texture()
{
    return m_texture;
}

Kunai::Kunai()
{
    m_position_x = 0;
    m_position_y = 0;
    m_velocity_x = 0;
    m_velocity_y = 0;
    m_acceleration_x = 0;
    m_acceleration_y = 0;

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
    
    scale_colliders();
    update_colliders();
    
    std::cout << "Kunai created\n";

    
}

ObjectName Kunai::get_name()
{
    return NAME;
}

int Kunai::get_width()
{
    return WIDTH;
}

float Kunai::get_scale_factor()
{
    return SCALE_FACTOR;
}

void Kunai::update_position()
{
    m_position_x += m_velocity_x;
    m_position_y += m_velocity_y;

    if (((m_position_x + WIDTH) > SCREEN_WIDTH) || (m_position_x < 0))
    {
        m_position_x -= m_velocity_x;
        m_velocity_x = -m_velocity_x;
    }
    
    if (m_velocity_x > 0)
    {
        m_flip_state = SDL_FLIP_NONE;
    }
    
    else if (m_velocity_x < 0)
    {
        m_flip_state = SDL_FLIP_HORIZONTAL;
    }
    
    update_colliders();
    
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
    
    update_colliders_scaled();

    if (m_flip_state == SDL_FLIP_HORIZONTAL)
    {
        flip_colliders();
    }
}
void Kunai::resolve_collision(Object* p_other)
{
    ObjectName other_name = p_other->get_name();
    
    switch(other_name)
    {
        case PLAYER:
            g_game_objects.remove(this);
            std::cout << "Kunai hit player\n";
            if (!(static_cast<Player*>(p_other))->get_hearts().pop_color())
            {
              std::cout << "you loose\n";
            }
            break;
            
        case KUNAI:
            g_game_objects.remove(this);
            g_game_objects.remove(p_other);
            std::cout << "Kunai hit kunai\n";
            break;
            
        case APPLE:
            g_game_objects.remove(p_other);
            std::cout << "Kunai hit apple\n";
            break;
    }
}
void Kunai::render()
{
    m_texture.render(m_position_x, m_position_y, nullptr, SCALE_FACTOR, m_flip_state);
}

Kunai::~Kunai()
{
    std::cout << "Kunai destroyed\n";
}
