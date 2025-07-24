//
//  controls_button.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 14/3/24.
//

#include "controls_button.h"
#include "music_handler.h"
#include "global_variables.h"

Texture ControlsButton::m_texture;

ControlsButton::ControlsButton()
{
    m_position.x = 0;
    m_position.y = 0;
}

Texture& ControlsButton::get_texture()
{
    return m_texture;
}

float ControlsButton::get_width()
{
    return WIDTH;
}

float ControlsButton::get_height()
{
    return HEIGHT;
}

void ControlsButton::update()
{
    if (m_state == MOUSE_PRESS_DOWN)
    {
        MusicHandler::play_click();
        
        if (g_menu_state)
        {
            g_menu_state = false;
        }
        
        g_controls_manual_state = !g_controls_manual_state;
        
        m_state = MOUSE_OVER;
    }
    
    update_hover_box();
}

void ControlsButton::render()
{
    render_hover_box();
    m_texture.render(m_position.x, m_position.y, nullptr, SCALE_FACTOR);
}

