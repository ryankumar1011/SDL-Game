//
//  button.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 10/1/24.
//

#include "button.h"
#include "global_variables.h"

void Button::set_position(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
}

void Button::handle_event(SDL_Event& event)
{
    if ((event.type == SDL_MOUSEBUTTONDOWN) || (event.type == SDL_MOUSEBUTTONUP) || (event.type == SDL_MOUSEMOTION) || (event.type == SDL_MOUSEWHEEL))
    {
        m_state = MOUSE_OUT;
        
        int x, y;
        
        SDL_GetMouseState(&x, &y);
        
        bool inside_button = true;
        
        if (x < m_position.x)
            
            inside_button = false;
        
        else if (x > (m_position.x + get_width()))
            
            inside_button = false;
        
        else if (y < m_position.y)
            
            inside_button = false;
        
        
        else if (y > (m_position.y + get_height()))
            
            inside_button = false;
        
        if (inside_button)
        {
            m_state = MOUSE_OVER;
            
            switch (event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    m_state = MOUSE_PRESS_DOWN;
                    break;
                    
                case SDL_MOUSEBUTTONUP:
                    m_state = MOUSE_PRESS_UP;
                    break;
                    
                case SDL_MOUSEMOTION:
                    m_state = MOUSE_MOVE_OVER;
                    break;
                    
                 case SDL_MOUSEWHEEL:
                    m_state = MOUSE_SCROLL_OVER;
                    break;
            }
        }
    }
    update();
}

void Button::update_hover_box()
{
    if ((m_state == MOUSE_OVER) || (m_state == MOUSE_MOVE_OVER))
    {
        m_hover = true;
    }
    else if (m_state == MOUSE_OUT)
    {
        m_hover = false;
    }
}

void Button::render_hover_box()
{
    if (m_hover)
    {
        SDL_FRect render_area = {m_position.x, m_position.y, get_width(), get_height()};
        SDL_SetRenderDrawBlendMode(gp_renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(gp_renderer, 0x0B, 0x66, 0x23, 0x88);
        SDL_RenderFillRectF(gp_renderer, &render_area);
    }
}
