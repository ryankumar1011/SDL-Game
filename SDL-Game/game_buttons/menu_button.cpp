//
//  menu_button.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 10/1/24.
//

#include "menu_button.h"
#include "music_handler.h"
#include "global_variables.h"

Texture MenuButton::m_texture;

MenuButton::MenuButton()
{
    m_position.x = 0;
    m_position.y = 0;
}

Texture& MenuButton::get_texture()
{
    return m_texture;
}

float MenuButton::get_width()
{
    return WIDTH;
}

float MenuButton::get_height()
{
    return HEIGHT;
}

void MenuButton::update()
{
    if (m_state == MOUSE_PRESS_DOWN)
    {
        MusicHandler::play_click();
        
        if (g_controls_manual_state)
        {
            g_controls_manual_state = false;
        }
        
        g_menu_state = !g_menu_state;
        
        m_state = MOUSE_OVER;
    }
    update_hover_box();
}

void MenuButton::render()
{
    render_hover_box();
    m_texture.render(m_position.x, m_position.y, nullptr, SCALE_FACTOR);
}
