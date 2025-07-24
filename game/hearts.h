//
//  hearts.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 28/12/23.
//

#pragma once

#include "texture.h"
#include <vector>
#include <SDL2/SDL.h>

 enum HeartColor
{
    RED,
    WHITE
 };

class Hearts
{
    
public:
    Hearts();
    static constexpr float SCALE_FACTOR = 1;
    static constexpr float WIDTH = 17*SCALE_FACTOR;
    static constexpr float HEIGHT = 14*SCALE_FACTOR;
    
    static Texture& get_texture();
    void set_position(float x, float y);
    void set_number(int number);
    bool pop();
    void render();
    
private:
    static Texture m_sprite;
    std::vector<SDL_FPoint> m_positions;
    std::vector<HeartColor> m_colors;
    static SDL_Rect m_red_clip;
    static SDL_Rect m_white_clip;
    int m_number;
};

