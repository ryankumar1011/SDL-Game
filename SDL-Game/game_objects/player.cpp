//
//  player.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 26/12/23.
//

#include "player.h"
#include "texture.h"
#include "hearts.h"
#include "kunai.h"
#include "game_objects.h"
#include "global_variables.h"

SDL_Rect Player::m_player_clips[12];

void Player::set_clips()
{
m_player_clips[0] = {20, 19, 108-19, 150-18};
m_player_clips[1] = {120, 19, 193-120, 150-19};
m_player_clips[2] = {216, 20, 283-216, 150-20};
m_player_clips[3] = {317, 22, 377-317, 151-22};
m_player_clips[4] = {405, 21, 459-405, 153-21};
m_player_clips[5] = {488, 22, 533-488, 151-22};

m_player_clips[6] = {94, 167, 147-94, 298-167};
m_player_clips[7] = {176, 166, 238-176, 296-166};
m_player_clips[8] = {263, 167, 339-263, 297-167};
m_player_clips[9] = {345, 167, 426-345, 297-167};
m_player_clips[10] = {435, 168, 531-435, 298-168};
m_player_clips[11] = {26, 303, 129-26, 434-303};
}

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
    
    std::cout << "player created\n";
}

ObjectName Player::get_name()
{
    return Player::NAME; // Do not need to specify Player:: (this is for clarity)
}

float Player::get_height()
{
    return Player::HEIGHT;
}

float Player::get_width()
{
    return Player::WIDTH;
}

bool Player::pop_heart()
{
    return mp_hearts->pop_color();
}

void Player::set_hearts(Hearts* p_hearts)
{
    mp_hearts = p_hearts;
}

void Player::create_kunai()
{
    Kunai* p_kunai = new Kunai;
    if (m_flip_state == SDL_FLIP_NONE)
    {
        if (m_position_x + 107 + Kunai::WIDTH > SCREEN_WIDTH) p_kunai->set_position(SCREEN_WIDTH - Kunai::WIDTH, m_position_y + 64.5);
        else p_kunai->set_position(m_position_x + 107, m_position_y + 64.5);
    }
    else
    {
        if (m_position_x - 107 - Kunai::WIDTH < 0) p_kunai->set_position(0, m_position_y + 64.5);
        else p_kunai->set_position(m_position_x - 107, m_position_y + 64.5);
    }
    
    g_game_objects.insert(p_kunai);
}

void Player::handle_event(SDL_Event& event)
{
    const uint8_t* key_states = SDL_GetKeyboardState(nullptr);
    
    if (event.type == SDL_KEYDOWN)
    {
        if (key_states[SDL_SCANCODE_A] || key_states[SDL_SCANCODE_LEFT])
        {
            //m_acceleration_x = -0.35;
            change_var(m_acceleration_x, -0.15, -MAX_ACCELERATION_X); //acts more like player has inertia
            if (m_flip_state == SDL_FLIP_NONE) m_flip_state = SDL_FLIP_HORIZONTAL;
        }
        
        if (key_states[SDL_SCANCODE_D] || key_states[SDL_SCANCODE_RIGHT])
        {
            //m_acceleration_x = 0.35;
            change_var(m_acceleration_x, 0.15, MAX_ACCELERATION_X); //acts more will act like player has inertia
            if (m_flip_state == SDL_FLIP_HORIZONTAL) m_flip_state = SDL_FLIP_NONE;
        }
        
        if (key_states[SDL_SCANCODE_T] && (event.key.repeat == 0))
        {
            if (m_frame == -1) m_frame = 0; //start the animation
            
            if (m_frame > 22) //cut the animation short
            {
                create_kunai();
                
                m_frame = -1;
            }
        }

        if (key_states[SDL_SCANCODE_SPACE] && (event.key.repeat == 0))
        {
            m_velocity_y = -JUMP_VELOCITY_Y;
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
    
    change_var(m_velocity_x, m_acceleration_x - FRICTION_MULTIPLIER*m_velocity_x, MAX_VELOCITY_X);
    change_var(m_velocity_y, m_acceleration_y - AIR_RESISTANCE*m_velocity_y, MAX_VELOCITY_Y);
   
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
    mp_hearts->render();
    
    if (m_frame < 0)
    {
        g_player_sprite.render_texture((int)m_position_x, (int)m_position_y, &m_player_clips[0], 0, m_flip_state);
    }
    else
    {
        g_player_sprite.render_texture((int)m_position_x, (int)m_position_y, &m_player_clips[m_frame/4], 0, m_flip_state);
        
        m_frame++;
    }
    if (m_frame > 44)
    {
        m_frame = -1; //stop animation
        
        create_kunai();
    }
}

Player::~Player()
{
    std::cout << "player destroyed\n";
}
