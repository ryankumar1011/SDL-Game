//
//  volume_button.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 13/3/24.
//

#include "music_button.h"
#include "music_handler.h"
#include "global_variables.h"

Texture MusicButton::m_texture_on;
Texture MusicButton::m_texture_off;

MusicButton::MusicButton()
{
    m_position.x = 0;
    m_position.y = 0;
}

Texture& MusicButton::get_texture_on()
{
    return m_texture_on;
}

Texture& MusicButton::get_texture_off()
{
    return m_texture_off;
}

float MusicButton::get_width()
{
    return WIDTH;
}

float MusicButton::get_height()
{
    return HEIGHT;
}

void MusicButton::update()
{
    if (Mix_PlayingMusic() == 0)
    {
        m_sound = false;
    }
    else if  (Mix_PausedMusic() == 1)
    {
        m_sound = false;
    }
    else
    {
        m_sound = true;
    }
    
    if (m_state == MOUSE_PRESS_UP)
    {
        MusicHandler::toggle_music();
        m_sound = !(m_sound);
        m_state = MOUSE_OVER;
    }
    
    update_hover_box();
}

void MusicButton::render()
{
    render_hover_box();
    
    if (m_sound)
    {
        m_texture_on.render(m_position.x, m_position.y, nullptr, SCALE_FACTOR);
    }
    else
    {
        m_texture_off.render(m_position.x, m_position.y, nullptr, SCALE_FACTOR);
    }
}

