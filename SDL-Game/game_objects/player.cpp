//
//  player.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 26/12/23.
//

#include "kunai.h"
#include "apple.h"
#include "player.h"
#include "music_handler.h"
#include "game_objects.h"
#include "global_variables.h"

SDL_Rect Player::m_clips[12];
Texture Player::m_sprite;

Texture& Player::get_texture()
{
    return m_sprite;
}

void Player::set_clips()
{
m_clips[0] = {20, 19, 108-19, 150-18};
m_clips[1] = {120, 19, 193-120, 150-19};
m_clips[2] = {216, 20, 283-216, 150-20};
m_clips[3] = {317, 22, 377-317, 151-22};
m_clips[4] = {405, 21, 459-405, 153-21};
m_clips[5] = {488, 22, 533-488, 151-22};

m_clips[6] = {94, 167, 147-94, 298-167};
m_clips[7] = {176, 166, 238-176, 296-166};
m_clips[8] = {263, 167, 339-263, 297-167};
m_clips[9] = {345, 167, 426-345, 297-167};
m_clips[10] = {435, 168, 531-435, 298-168};
m_clips[11] = {26, 303, 129-26, 434-303};
}

Player::Player()
{
    m_position.x = 0;
    m_position.y = 0;
    m_velocity.x = 0;
    m_velocity.y = 0;
    m_acceleration.x = 0;
    m_acceleration.y = GRAVITY_ACCELERATION;
        
    m_colliders.resize(2);

    m_colliders[0].w = 62;
    m_colliders[0].h = 57;
    
    m_colliders[1].w = 71;
    m_colliders[1].h = 75;
    
    scale_colliders(SCALE_FACTOR);
    update_colliders();
    
    m_flip_state = SDL_FLIP_NONE;
    
    m_frame = -1;
    m_shield.set_state(false);
    
    std::cout << "player created\n";
}


ObjectName Player::get_name()
{
    return NAME;
}

float Player::get_mass()
{
    return MASS;
}

Hearts& Player::get_hearts()
{
    return m_hearts;
}

KunaiCounter& Player::get_kunai_counter()
{
    return m_kunai_counter;
}

void Player::create_kunai()
{
    if (m_kunai_counter.decrease_count())
    {
        Kunai* p_kunai = new Kunai(*this);
        
        SDL_FPoint& kunai_position = p_kunai->get_position();
        SDL_FPoint& kunai_velocity = p_kunai->get_velocity();
        
        kunai_velocity.y = 0;
        
        if (m_flip_state == SDL_FLIP_NONE)
        {
            if (m_position.x + SCALE_FACTOR*104 + Kunai::WIDTH > SCREEN_WIDTH)
            {
                kunai_position.x = SCREEN_WIDTH - Kunai::WIDTH;
                kunai_position.y = m_position.y + SCALE_FACTOR*72 - Kunai::HEIGHT/2;
            }
            else
            {
                kunai_position.x = m_position.x + SCALE_FACTOR*104;
                kunai_position.y = m_position.y + SCALE_FACTOR*72 - Kunai::HEIGHT/2;
            }
            
            kunai_velocity.x = 6;
        }
        
        else
        {
            if (m_position.x - 1 - Kunai::WIDTH < 0)
            {
                kunai_position.x = 0;
                kunai_position.y = m_position.y + SCALE_FACTOR*72 - Kunai::HEIGHT/2;
            }
            else
            {
                kunai_position.x = m_position.x - 1 - Kunai::WIDTH;
                kunai_position.y = m_position.y + SCALE_FACTOR*72 - Kunai::HEIGHT/2;
            }
            
            kunai_velocity.x = -6;
        }
        
        g_game_objects.insert(p_kunai);
        MusicHandler::play_kunai();
    }
}

void Player::handle_event(SDL_Event& event)
{
    const uint8_t* key_states = SDL_GetKeyboardState(nullptr);
    
    if (event.type == SDL_KEYDOWN)
    {
        if (key_states[SDL_SCANCODE_A] || key_states[SDL_SCANCODE_LEFT])
        {
            m_acceleration.x = -MAX_ACCELERATION_X;
            m_flip_state = SDL_FLIP_HORIZONTAL;
        }
        
        if (key_states[SDL_SCANCODE_D] || key_states[SDL_SCANCODE_RIGHT])
        {
            m_acceleration.x = MAX_ACCELERATION_X;
            m_flip_state = SDL_FLIP_NONE;
        }
        
        if (key_states[SDL_SCANCODE_T] && (event.key.repeat == 0))
        {
            if (m_shield.get_state())
            {
                m_shield.set_state(false);
                g_game_objects.remove(&m_shield);
            }
            
            if (m_frame == -1) m_frame = 0; //start the animation
            
            if (m_frame > 24) //cut the animation short
            {
                create_kunai();
                
                m_frame = 0; //and start again
            }
        }
        
        if (key_states[SDL_SCANCODE_F] && ((m_frame == -1) || (m_frame > 24)) && (!m_shield.get_state()))
        {
            if (m_frame > 24) m_frame = -1;
            m_shield.set_state(true);
            g_game_objects.insert(&m_shield);
        }

        if (key_states[SDL_SCANCODE_SPACE] && (event.key.repeat == 0))
        {
            m_velocity.y = -JUMP_VELOCITY_Y;
        }
    }
        
    else if (event.type == SDL_KEYUP)
    {
        //these handle the cases when switching from pressing left to pressing right and vice versa
        
        if ((key_states[SDL_SCANCODE_A] == 0) && (key_states[SDL_SCANCODE_LEFT] == 0) && (m_acceleration.x < 0))
        {
            m_acceleration.x = 0;
            if (key_states[SDL_SCANCODE_D] || key_states[SDL_SCANCODE_RIGHT])
            {
                m_flip_state = SDL_FLIP_NONE;
                m_acceleration.x = MAX_ACCELERATION_X;
            }
        }
        
        if ((key_states[SDL_SCANCODE_D] == 0) && (key_states[SDL_SCANCODE_RIGHT] == 0) && (m_acceleration.x > 0))
        {
            m_acceleration.x = 0;
            if (key_states[SDL_SCANCODE_A] || key_states[SDL_SCANCODE_LEFT])
            {
                m_flip_state = SDL_FLIP_HORIZONTAL;
                m_acceleration.x = -MAX_ACCELERATION_X;
            }
        }
        if (key_states[SDL_SCANCODE_T])
        {
            if (m_frame == -1) m_frame = 0; //start the animation
        }
        //throw key is pressed but shield key is not
        if (key_states[SDL_SCANCODE_F] == 0)
        {
            m_shield.set_state(false);
            g_game_objects.remove(&m_shield);
        }
    }
}

void Player::update_position()
{
    m_position.x += m_velocity.x;
    m_position.y += m_velocity.y;
    
    if (((m_position.x + WIDTH) > SCREEN_WIDTH) || (m_position.x < 0))
    {
        m_position.x -= m_velocity.x;
        m_velocity.x = 0;
        m_acceleration.x = 0;
    }
    
    if (((m_position.y + HEIGHT) > SCREEN_HEIGHT) || (m_position.y < 0))
    {
        m_position.y -= m_velocity.y;
        m_velocity.y = 0;
        m_acceleration.y = 0;
        
    }
    else
    {
        m_acceleration.y = GRAVITY_ACCELERATION;
    }
    
    change_var_capped(m_velocity.x, m_acceleration.x - FRICTION_MULTIPLIER*m_velocity.x, MAX_VELOCITY_X);
    change_var_capped(m_velocity.y, m_acceleration.y - AIR_RESISTANCE*m_velocity.y, MAX_VELOCITY_Y);
    
    update_colliders();
    
    if (m_flip_state == SDL_FLIP_NONE)
    {
        m_shield.update_position({m_position.x + SCALE_FACTOR*82, m_position.y + SCALE_FACTOR*55});
    }
    if (m_flip_state == SDL_FLIP_HORIZONTAL)
    {
        m_shield.update_position({m_position.x + SCALE_FACTOR*5, m_position.y + SCALE_FACTOR*55});
    }
    
    m_shield.get_velocity() = {m_velocity.x, m_velocity.y};
        
}

void Player::update_colliders()
{
    m_colliders[0].x = m_position.x + 3;
    m_colliders[0].y = m_position.y + 1;
    
    m_colliders[1].x = m_position.x + 13;
    m_colliders[1].y = m_position.y + 57;
    
    update_scaled_colliders(SCALE_FACTOR);
    
    if (m_flip_state == SDL_FLIP_HORIZONTAL)
    {
        flip_colliders(WIDTH);
    }
}

void Player::resolve_collision(Object* p_other)
{
    ObjectName other_name = p_other->get_name();
    
    switch(other_name)
    {
        case KUNAI:
            g_game_objects.destroy(p_other);
            if (!get_hearts().pop())
            {
                std::cout << "you loose\n";
            }
            break;
            
        case APPLE:
            collide(p_other);
            break;
    }
}

void Player::render()
{
    m_hearts.render();
    m_kunai_counter.render();
    
    if (m_frame < 0)
    {
        m_sprite.render(m_position.x, m_position.y, &m_clips[0], SCALE_FACTOR, m_flip_state);
    }
    else
    {
        m_sprite.render(m_position.x, m_position.y, &m_clips[m_frame/4], SCALE_FACTOR, m_flip_state, WIDTH);
        
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
