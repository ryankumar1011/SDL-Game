//
//  MouseButton.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 25/12/23.
//

#include "mouse_button.h"
#include "global_variables.h"

MouseButton::MouseButton()
{
    m_position = {0,0};
    
    m_width = 0;
    m_height = 0;
    
    m_current_clip = MOUSE_CLIP_OUT;
    
}

//Changes m_current_clip (with type of an enum MouseClipState) depending on the type of mouse event returned during SDL_PollEvent()
void MouseButton::handle_event (SDL_Event& event)
{
    if ((event.type == SDL_MOUSEBUTTONDOWN) || (event.type == SDL_MOUSEBUTTONUP) || (event.type == SDL_MOUSEMOTION) || (event.type == SDL_MOUSEWHEEL))
    {
        m_current_clip = MOUSE_CLIP_OUT;
        
        int x, y;
        
        SDL_GetMouseState(&x, &y);
        
        bool inside_button = true;
        
        
        if (x < m_position.x)
            
            inside_button = false;
        
        else if (x > (m_position.x + m_width))
            
            inside_button = false;
        
        else if (y < m_position.y)
            
            inside_button = false;
        
        
        else if (y > (m_position.y + m_height))
            
            inside_button = false;
        
        if (inside_button)
        {
            m_current_clip = MOUSE_CLIP_OVER;
            
            switch (event.type)
            {
                    
                case SDL_MOUSEBUTTONDOWN:
                    m_current_clip = MOUSE_CLIP_PRESS_DOWN;
                    break;
                    
                case SDL_MOUSEBUTTONUP:
                    m_current_clip = MOUSE_CLIP_PRESS_UP;
                    break;
                    
                case SDL_MOUSEMOTION:
                    m_current_clip = MOUSE_CLIP_MOVE_OVER;
                    break;
                    
                 case SDL_MOUSEWHEEL:
                    m_current_clip = MOUSE_CLIP_SCROLL_OVER;
                    break;
            }
        }
    }
}

//Some mouse states may not change the clip to display. They may instead change the color of the button or have other effects.
void MouseButton::handle_extra_states()

{
    mp_sprite->set_color_mod(0xFF, 0xFF, 0xFF);
    
    if (m_current_clip == MOUSE_CLIP_MOVE_OVER)
    {
        mp_sprite->set_color_mod(0x00, 0x60, 0x00);
        m_current_clip = MOUSE_CLIP_OVER;
    }
    if (m_current_clip == MOUSE_CLIP_SCROLL_OVER)
    {
        mp_sprite->set_color_mod(0x00, 0x60, 0x00);
        m_current_clip = MOUSE_CLIP_OVER;
    }

}

void MouseButton::set_position (int x, int y)
{
    
    m_position.x = x;
    m_position.y = y;
    
}

void MouseButton::set_width(int width)
{
    m_width = width;
}

void MouseButton::set_height(int height)
{
    m_height = height;
}

void MouseButton::set_sprite(Texture* p_sprite)
{
    mp_sprite = p_sprite;
}

int MouseButton::get_current_clip()
{
    return m_current_clip;
}

void MouseButton::render_button()
{
    handle_extra_states();
    mp_sprite->render_texture(m_position.x, m_position.y, &m_clips[m_current_clip]);
    
}

