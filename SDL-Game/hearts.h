//
//  hearts.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 28/12/23.
//

#pragma once

#include "sdl_libraries.h"

 enum HeartColor
{
    RED,
    WHITE
 };

class Hearts
{
    
public:
    Hearts();
    void set_position(int x, int y);
    bool pop_color();
    void render();
    
private:
    SDL_Rect m_red_clip;
    SDL_Rect m_white_clip;
    SDL_Rect m_render_areas[3];
    HeartColor m_colors[3];
};
