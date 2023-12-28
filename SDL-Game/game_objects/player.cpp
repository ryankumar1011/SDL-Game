//
//  player.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 26/12/23.
//

#include "player.h"
#include "texture.h"
#include "global_variables.h"

Player::Player()
{
    
    m_position_x = 0;
    m_position_y = 0;
    
    m_velocity_x = 0;
    m_velocity_y = 0;
    
    m_acceleration_x = 0;
    m_acceleration_y = GRAVITY_ACCELERATION;
        
    m_colliders.resize(2);

    m_colliders[0].w = 62;
    m_colliders[0].h = 59;
    
    m_colliders[1].w = 71;
    m_colliders[1].h = 75;
    
    update_colliders();
    
    m_frame = -1;
    
}

float Player::get_height()
{
    return Player::HEIGHT;
}

float Player::get_width()
{
    return Player::WIDTH;
}

void Player::handle_event(SDL_Event& event)
{
    const uint8_t* key_states = SDL_GetKeyboardState(nullptr);
    
    if (event.type == SDL_KEYDOWN)
    {
        
        if (key_states[SDL_SCANCODE_A] || key_states[SDL_SCANCODE_LEFT])
        {
            change_var(m_acceleration_x, -0.1, -1);
            if (m_flip_state == SDL_FLIP_NONE) m_flip_state = SDL_FLIP_HORIZONTAL;
        }
        if (key_states[SDL_SCANCODE_D] || key_states[SDL_SCANCODE_RIGHT])
        {
            change_var(m_acceleration_x, 0.1, 1);
            if (m_flip_state == SDL_FLIP_HORIZONTAL) m_flip_state = SDL_FLIP_NONE;
            
        }
        
        if ((key_states[SDL_SCANCODE_F] && event.key.repeat == 0))
        {
            m_frame = 0;
        }
        if ((key_states[SDL_SCANCODE_SPACE] && event.key.repeat == 0))
        {
            m_velocity_y = -11.5;
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        if ((key_states[SDL_SCANCODE_A] == 0) && (key_states[SDL_SCANCODE_LEFT] == 0) && (m_acceleration_x < 0))
            m_acceleration_x = 0;
        if ((key_states[SDL_SCANCODE_D] == 0) && (key_states[SDL_SCANCODE_RIGHT] == 0) && (m_acceleration_x > 0))
            m_acceleration_x = 0;
    }
}

void Player::update_position()
{
    m_position_x += m_velocity_x;
    m_position_y += m_velocity_y;
    
    if (((m_position_x + Player::WIDTH) > SCREEN_WIDTH) || (m_position_x < 0))
    {
        m_position_x -= m_velocity_x;
        m_velocity_x = 0;
        m_acceleration_x = 0;
    }
    
    if (((m_position_y + Player::HEIGHT) > SCREEN_HEIGHT) || (m_position_y < 0))
    {
        m_position_y -= m_velocity_y;
        m_velocity_y = 0;
        m_acceleration_y = 0;
        
        
    }
    else
    {
        m_acceleration_y = GRAVITY_ACCELERATION;
    }
    
    change_var(m_velocity_x, m_acceleration_x - FRICTION_MULTIPLIER*m_velocity_x, 10);
    change_var(m_velocity_y, m_acceleration_y - AIR_RESISTANCE*m_velocity_y, 15);
   
    update_colliders();
        
}

void Player::update_colliders()
{
    m_colliders[0].x = m_position_x + 3;
    m_colliders[0].y = m_position_y + 3;
    
    m_colliders[1].x = m_position_x + 13;
    m_colliders[1].y = m_position_y + 57;
    
    if (m_flip_state == SDL_FLIP_HORIZONTAL)
    {
        flip_colliders();
    }
}

void Player::render()
{
    if (m_frame < 0)
    {
        player_sprite.render_texture((int)m_position_x, (int)m_position_y, &g_player_clips[0], 0, m_flip_state);
    }
    else
    {
        player_sprite.render_texture((int)m_position_x, (int)m_position_y, &g_player_clips[m_frame/5], 0, m_flip_state);
        
        m_frame++;
        
        if (m_frame > 55)
        {
            m_frame = -1;
        }
    }
}
