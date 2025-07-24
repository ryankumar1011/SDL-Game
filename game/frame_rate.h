//
//  frame_rate.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 1/1/24.
//

#pragma once
#include "texture.h"
#include <sstream>
#include <SDL2/SDL.h>

class FrameRate
{
public:
    FrameRate();
    void set_position(float x, float y);
    void update(int frame_rate);
    void render();
    ~FrameRate();
    
private:
    Texture m_text;
    SDL_FPoint m_position;
    std::stringstream m_text_stream;
    SDL_Color m_color = {0x00, 0x00, 0x00};
    bool load_texture();
};
