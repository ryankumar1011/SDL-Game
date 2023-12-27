//
//  hearts.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 28/12/23.
//

#include "hearts.h"
#include "texture.h"
#include "global_variables.h"


Hearts::Hearts()
{
    m_red_clip = {1, 0, 17, 14};
    m_white_clip = {19, 0, 17, 14};
    
    for (int i = 0; i < 3; i++)
    {
        m_render_areas[i].w = 17;
        m_render_areas[i].h = 14;
        m_colors[i] = RED;
    }
}

void Hearts::set_position(int x, int y)
{
    m_render_areas[0].x = x;
    m_render_areas[0].y = y;
   
    m_render_areas[1].x = m_render_areas[0].x + m_render_areas[0].w + 1;
    m_render_areas[1].y = m_render_areas[0].y;
    
    m_render_areas[2].x = m_render_areas[1].x + m_render_areas[1].w + 1;
    m_render_areas[2].y = m_render_areas[0].y;
    
}
bool Hearts::pop_color()
{
    for (int i = 2; i >= 0; i--)
    {
        if (m_colors[i] == RED)
        {
            m_colors[i] = WHITE;
            return true;
        }
    }
    
    return false;
}

void Hearts::render()
{
    for (int i = 0; i < 3; i++)
    {
        if (m_colors[i] == RED) SDL_RenderCopy(gp_renderer, heart_sprite.get_texture_pointer(), &m_red_clip, &m_render_areas[i]);
        
        else if (m_colors[i] == WHITE) SDL_RenderCopy(gp_renderer, heart_sprite.get_texture_pointer(), &m_white_clip, &m_render_areas[i]);
    }
}

