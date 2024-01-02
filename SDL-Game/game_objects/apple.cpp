//
//  Apple.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 2/1/24.
//

#include "apple.h"
#include "player.h"
#include "game_objects.h"
#include "global_variables.h"

Texture Apple::m_texture;
SDL_Rect Apple::m_clip = {25, 20, 15, 17};

Apple::Apple()
{
    m_position_x = 0;
    m_position_y = 0;
    m_velocity_x = 0;
    m_velocity_y = 0;
    m_acceleration_x = 0;
    m_acceleration_y = 0;
    m_center.x = 0;
    m_center.y = 0;
    m_angle = 0.0;
    m_acceleration_y = GRAVITY_ACCELERATION;
    
    m_colliders.resize(1);
    
    m_colliders[0].w = 15;
    m_colliders[0].h = 14;
    
    scale_colliders();
    update_colliders();
}

Texture& Apple::get_texture()
{
    return m_texture;
}

ObjectName Apple::get_name()
{
    return NAME;
}

float Apple::get_scale_factor()
{
    return SCALE_FACTOR;
}

int Apple::get_width()
{
    return WIDTH;
}

void Apple::update_position()
{
    m_position_x += m_velocity_x;
    m_position_y += m_velocity_y;
    
    change_var(m_velocity_y, m_acceleration_y, MAX_VELOCITY_Y);
    m_center = {(m_position_x + 15/2), (m_position_y + 10)};
    
    update_colliders();
}

void Apple::update_colliders()
{
    m_colliders[0].x = m_position_x;
    m_colliders[0].y = m_position_y + 3;
    
    update_colliders_scaled();
}

void Apple::resolve_collision(Object* p_other)
{
    ObjectName other_name = p_other->get_name();
    
    switch(other_name)
    {
        case PLAYER:
            g_game_objects.remove(this);
            std::cout << "Kunai hit player\n";
            if (!static_cast<Player*>(p_other)->get_hearts().pop_color())
            {
                std::cout << "you loose\n";
            }
            break;
            
        case KUNAI:
            g_game_objects.remove(this);
            std::cout << "Kunai hit apple\n";
            break;
            
        case APPLE:
            g_game_objects.remove(this);
            g_game_objects.remove(p_other);
            std::cout << "Apple hit apple\n";
            break;
    }
}

void Apple::render()
{
    m_texture.render(m_position_x, m_position_y, &m_clip, SCALE_FACTOR, m_flip_state);
    
    m_angle += 3;
    
    if (m_angle > 360) m_angle = 0;
}
