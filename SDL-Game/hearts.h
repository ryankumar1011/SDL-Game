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
    static constexpr int WIDTH = 17;
    static constexpr int HEIGHT = 14;
    static Texture& get_texture();
    void set_position(int x, int y);
    void set_number(int number);
    bool pop_color();
    void render();
    
private:
    int m_number;
    std::vector<SDL_Point> m_positions;
    std::vector<HeartColor> m_colors;
    SDL_Rect m_red_clip;
    SDL_Rect m_white_clip;
    static Texture m_sprite;
};
