//
//  mouse_input.h
//  SDL-Game
//
//  Created by Ryan Kumar on 1/11/23.
//

#pragma once 

#include "texture.h"

enum MouseClipState
{
    MOUSE_CLIP_OUT,
    MOUSE_CLIP_OVER,
    MOUSE_CLIP_PRESS_UP,
    MOUSE_CLIP_PRESS_DOWN,
    MOUSE_CLIP_MOVE_OVER,
    MOUSE_CLIP_SCROLL_OVER,
    MOUSE_CLIP_TOTAL
    
};

class MouseButton
{

public:
    
    MouseButton();
    
    void handle_mouse_event (SDL_Event& event);
    
    void set_button_sprite(Texture* p_button_sprite);
    
    Texture* get_button_sprite_texture();
    
    void set_position (int x, int y);
    
    void set_width(int width);
    
    void set_height(int height);
    
    int get_current_clip();
    
    void handle_extra_states();
    
    void render_button();
    
    
private:
    
    int m_width;
    
    int m_height;
    
    SDL_Point m_position;
    
    MouseClipState m_current_clip;
    
    Texture* mp_button_sprite;
    
};





