//
//  Apple.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 2/1/24.
//

#include "apple.h"
#include "kunai.h"
#include "player.h"
#include "game_objects.h"
#include "music_handler.h"
#include "global_variables.h"

Texture Apple::m_texture;
SDL_Rect Apple::m_clip = {25, 20, 15, 17};

Apple::Apple()
{
    m_position.x = 0;
    m_position.y = 0;
    m_velocity.x = 0;
    m_velocity.y = 3;
    m_acceleration.x = 0;
    m_acceleration.y = 0;
    m_angle = 0.0;
    
    m_colliders.resize(1);
    
    m_colliders[0].w = 15;
    m_colliders[0].h = 14;
    
    scale_colliders(SCALE_FACTOR);
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

float Apple::get_mass()
{
    return MASS;
}

void Apple::update_position()
{
    m_position.x += m_velocity.x;
    m_position.y += m_velocity.y;
        
    update_colliders();
}

void Apple::update_colliders()
{
    m_colliders[0].x = m_position.x;
    m_colliders[0].y = m_position.y + 3;
    
    update_scaled_colliders(SCALE_FACTOR);
}

void Apple::resolve_collision(Object* p_other)
{
    ObjectName other_name = p_other->get_name();
    
    switch(other_name)
    {
        case PLAYER:
            collide(p_other);           
            break;
            
        case SHIELD:
            collide(p_other);
            break;
            
        case KUNAI:
            g_game_objects.destroy(this);
            static_cast<Kunai*>(p_other)->get_player().get_kunai_counter().increase_count(3);
            MusicHandler::play_apple_hit();
            break;
            
        case APPLE:
            g_game_objects.destroy(this);
            g_game_objects.destroy(p_other);
            break;
    }
}
void Apple::render()
{
    m_texture.render(m_position.x, m_position.y, &m_clip, SCALE_FACTOR, m_angle, nullptr, m_flip_state);
    
    m_angle += m_angular_velocity;
    
    if (m_angle > 360) m_angle = 0;
}

/*
void collide()
{
     
    
     float penetration_length = std::sqrt(m_penetration.x * m_penetration.x + m_penetration.y * m_penetration.y);
                 if (penetration_length > 0)
                 {
                     m_penetration.x /= penetration_length;
                     m_penetration.y /= penetration_length;
                 }

                 // Adjust positions to resolve the collision
                 m_position_x += m_penetration.x * 0.1f;
                 m_position_y += m_penetration.y * 0.1f;

                 // Calculate dot product for reflection
                 float dotProduct = abs(m_velocity_x * m_penetration.x) + abs(m_velocity_y * m_penetration.y);

                 // Reflect the velocity vector across the penetration vector
                 m_velocity_x -= 2 * dotProduct * m_penetration.x;
                 m_velocity_y += 2 * dotProduct * m_penetration.y;
    m_velocity_x -= 2 * dotProduct * m_penetration.x;
    m_velocity_x -= 2 * dotProduct * m_penetration.x;
      float dotProduct = m_velocity_x * m_penetration.x + m_velocity_y * m_penetration.y;

      // Reflect the velocity vector across the normal vector
      m_velocity_x -= 2 * dotProduct * m_penetration.x;
      m_velocity_y -= 2 * dotProduct * m_penetration.y;
    
    update_position();

    if (-m_penetration.x > 0)
    {
        if (m_angle_velocity >= -5) m_angle_velocity--;
    }
    
    else if (m_angle_velocity <= 5) m_angle_velocity++;
    
}
*/
/*
 float penetration_length = std::sqrt(m_penetration.x * m_penetration.x + m_penetration.y * m_penetration.y);
             if (penetration_length > 0)
             {
                 m_penetration.x /= penetration_length;
                 m_penetration.y /= penetration_length;
             }

             // Adjust positions to resolve the collision
             m_position_x += m_penetration.x * 0.1f;
             m_position_y += m_penetration.y * 0.1f;

             // Calculate dot product for reflection
             float dotProduct = m_velocity_x * m_penetration.x + m_velocity_y * m_penetration.y;

             // Reflect the velocity vector across the penetration vector
             m_velocity_x -= 2 * dotProduct * m_penetration.x;
             m_velocity_y -= 2 * dotProduct * m_penetration.y;
 m_velocity_x -= 2 * (m_velocity_x * m_normal_vector.x + m_velocity_y * m_normal_vector.y) * m_normal_vector.x;
    m_velocity_y -= 2 * (m_velocity_x * m_normal_vector.x + m_velocity_y * m_normal_vector.y) * m_normal_vector.y;

    // Move the object slightly away from the collision point to avoid getting stuck
    m_position_x += m_normal_vector.x;
    m_position_y += m_normal_vector.y;
 
 */

