//
//  hearts.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 28/12/23.
//

#include "hearts.h"
#include "texture.h"

Texture Hearts::m_sprite;
SDL_Rect Hearts::m_red_clip = {0, 0, 17, 14};;
SDL_Rect Hearts::m_white_clip = {18, 0, 17, 14};

Texture& Hearts::get_texture()
{
    return m_sprite;
}

Hearts::Hearts()
{
    m_number = 3;

    m_positions.resize(m_number);
    
    m_colors.resize(m_number);
    
    for (auto &i : m_colors)
    {
        i = RED;
    }
    
    std::cout << "hearts created\n";
}

void Hearts::set_position(float x, float y)
{
    m_positions[0].x = x;
    m_positions[0].y = y;
    
    for (int i = 1; i < m_number; i++)
    {
        m_positions[i].x = x + i*(WIDTH + 1);
        m_positions[i].y = y;
    }
}

void Hearts::set_number(int number)
{
    if (number > 0)
    {
        m_number = number;
        m_positions.resize(m_number);
        m_colors.resize(m_number);
        
        for (auto &i : m_colors)
        {
            i = RED;
        }
        
        set_position(m_positions[0].x, m_positions[0].y);
    }
}

bool Hearts::pop()
{
    for (int i = m_number-1; i >= 0; i--)
    {
        if (m_colors[i] == RED)
        {
            m_colors[i] = WHITE;
            if (i != 0)  return true;
        }
    }
    return false;
}

void Hearts::render()
{
    for (int i = 0; i < m_number; i++)
    {
        if (m_colors[i] == RED) 
        {
            m_sprite.render(m_positions[i].x, m_positions[i].y, &m_red_clip, SCALE_FACTOR);
        }
        
        else if (m_colors[i] == WHITE) m_sprite.render(m_positions[i].x, m_positions[i].y, &m_white_clip, SCALE_FACTOR);
    }
}

