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
#include "music_handler.h"
#include "global_variables.h"

Texture Kunai::m_texture;

Texture& Kunai::get_texture()
{
    return m_texture;
}

Kunai::Kunai(Player& player)
    : m_player(player)
{
    m_position.x = 0;
    m_position.y = 0;
    m_velocity.x = 0;
    m_velocity.y = 0;
    m_acceleration.x = 0;
    m_acceleration.y = 0;
    
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
    
    scale_colliders(SCALE_FACTOR);
    update_colliders();
    
    std::cout << "Kunai created\n";

    
}

ObjectName Kunai::get_name()
{
    return NAME;
}

Player& Kunai::get_player()
{
    return m_player;
}

void Kunai::update_position()
{
    m_position.x += m_velocity.x;
    m_position.y += m_velocity.y;

    if (((m_position.x + WIDTH) > SCREEN_WIDTH) || (m_position.x < 0))
    {
        m_position.x -= m_velocity.x;
        m_velocity.x = -m_velocity.x;
    }
    
    if (m_velocity.x > 0)
    {
        m_flip_state = SDL_FLIP_NONE;
    }
    
    else if (m_velocity.x < 0)
    {
        m_flip_state = SDL_FLIP_HORIZONTAL;
    }
    
    update_colliders();
    
}

void Kunai::update_colliders()
{
    m_colliders[0].x = m_position.x + 0;
    m_colliders[0].y = m_position.y + 5;
 
    m_colliders[1].x = m_position.x + 3;
    m_colliders[1].y = m_position.y + 3;
    
    m_colliders[2].x = m_position.x + 8;
    m_colliders[2].y = m_position.y + 5;
    
    m_colliders[3].x = m_position.x + 13;
    m_colliders[3].y = m_position.y + 5;
    
    m_colliders[4].x = m_position.x + 13;
    m_colliders[4].y = m_position.y + 10;
    
    m_colliders[5].x = m_position.x + 15;
    m_colliders[5].y = m_position.y + 12;
    
    m_colliders[6].x = m_position.x + 13;
    m_colliders[6].y = m_position.y + 3;
    
    m_colliders[7].x = m_position.x + 15;
    m_colliders[7].y = m_position.y + 0;
    
    update_scaled_colliders(SCALE_FACTOR);

    if (m_flip_state == SDL_FLIP_HORIZONTAL)
    {
        flip_colliders(WIDTH);
    }
}
void Kunai::resolve_collision(Object* p_other)
{
    ObjectName other_name = p_other->get_name();
    
    switch(other_name)
    {
        case PLAYER:
            g_game_objects.destroy(this);
            if (!(static_cast<Player*>(p_other))->get_hearts().pop())
            {
              std::cout << "you loose\n";
            }
            break;
            
        case SHIELD:
            g_game_objects.destroy(this);
            break;
            
        case KUNAI:
            g_game_objects.destroy(this);
            g_game_objects.destroy(p_other);
            break;
            
        case APPLE:
            g_game_objects.destroy(p_other);
            get_player().get_kunai_counter().increase_count(3);
            MusicHandler::play_apple_hit();
            break;
    }
}
void Kunai::render()
{
    m_texture.render(m_position.x, m_position.y, nullptr, SCALE_FACTOR, m_flip_state);
}

Kunai::~Kunai()
{
    std::cout << "Kunai destroyed\n";
}
