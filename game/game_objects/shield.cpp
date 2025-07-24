//
//  shield.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 3/1/24.
//

#include "shield.h"
#include "game_objects.h"
#include "music_handler.h"
#include "global_variables.h"

Texture Shield::m_texture;

Shield::Shield()
{
    m_position.x = 0;
    m_position.y = 0;
    m_velocity.x = 0;
    m_velocity.y = 0;
    m_acceleration.x = 0;
    m_acceleration.y = 0;;
    
    m_colliders.resize(1);
}

void Shield::update_colliders()
{
    m_colliders[0].x = m_position.x;
    m_colliders[0].y = m_position.y;
    
    m_colliders[0].w = 33*m_scale_factor;
    m_colliders[0].h = 70*m_scale_factor;

    update_scaled_colliders(m_scale_factor);
}

Texture& Shield::get_texture()
{
    return m_texture;
}

ObjectName Shield::get_name()
{
    return NAME;
}

bool Shield::get_state()
{
    return m_state;
}

void Shield::set_state(bool state)
{
    m_state = state;
}

void Shield::resolve_collision(Object* p_other)
{
    ObjectName other_name = p_other->get_name();
    
    switch(other_name)
    {
        case KUNAI:
            MusicHandler::play_shield_hit();
            g_game_objects.destroy(p_other);
            break;
            
        case APPLE:
            MusicHandler::play_shield_hit();
            collide(p_other);
            break;
    }
}

void Shield::update_position(SDL_FPoint center)
{
    if (m_state)
    {
        m_position.x = center.x - m_width/2;
        m_position.y = center.y - m_height/2;
    
        change_var_capped(m_scale_factor, 0.1, MAX_SCALE_FACTOR);
        
        m_width = 33*m_scale_factor;
        m_height = 70*m_scale_factor;
        
        update_colliders();
    }
    
    else m_scale_factor = 0;
}

void Shield::render()
{
    m_texture.render(m_position.x, m_position.y, nullptr, m_scale_factor, 0, nullptr, m_flip_state);
}
