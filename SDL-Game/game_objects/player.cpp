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
    m_width = 89;
    m_height = 132;
    
    m_position_x = 0;
    m_position_y = 0;
    m_velocity_x = 0;
    m_velocity_y = 0;
    
    m_colliders.resize(2);

    m_colliders[0].w = 62;
    m_colliders[0].h = 59;
    
    m_colliders[1].w = 71;
    m_colliders[1].h = 75;
    
    update_colliders();
    
    m_frame = -1;
    mp_current_clip = &g_player_clips[0];
    
}

void Player::handle_event(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN)
    {
        const uint8_t* key_states = SDL_GetKeyboardState(nullptr);
        
        //use template,change acceleration instead?
        
        if (key_states[SDL_SCANCODE_A] | key_states[SDL_SCANCODE_LEFT])
        {
            change_velocity_x(-1, -6);
        }
        if (key_states[SDL_SCANCODE_D] | key_states[SDL_SCANCODE_RIGHT])
        {
            change_velocity_x(1, 6);
        }
        if (key_states[SDL_SCANCODE_W] | key_states[SDL_SCANCODE_UP])
        {
            change_velocity_y(-1, -6);
        }
        if (key_states[SDL_SCANCODE_S] | key_states[SDL_SCANCODE_DOWN])
        {
            change_velocity_y(1, 6);
        }
        
        if ((key_states[SDL_SCANCODE_F] && event.key.repeat == 0))
        {
            m_frame = 0;
        }
    }
}

void Player::update_position()
{
    m_position_x += m_velocity_x;
    m_position_y += m_velocity_y;
    
    update_colliders();
    
    if (((m_position_x + m_width) > SCREEN_WIDTH) || (m_position_x < 0))
    {
        m_position_x -= m_velocity_x;
        m_velocity_x = 0;
        (m_flip_state == SDL_FLIP_NONE) ? m_flip_state = SDL_FLIP_HORIZONTAL : m_flip_state = SDL_FLIP_NONE;
        
    }
    
    if (((m_position_y + m_height) > SCREEN_HEIGHT) || (m_position_y < 0))
    {
        m_position_y -= m_velocity_y;
        m_velocity_y = 0;
    }
    
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
        player_sprite.render_texture(m_position_x, m_position_y, &g_player_clips[0], 0, m_flip_state);
    }
    else
    {
        mp_current_clip = &g_player_clips[m_frame/5];
        
        player_sprite.render_texture(m_position_x, m_position_y, mp_current_clip, 0, m_flip_state);
        
        m_frame++;
        
        if (m_frame > 55)
        {
            m_frame = -1;
        }
    }
}

