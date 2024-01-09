//
//  kunai_counter.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 3/1/24.
//

#pragma once

#include <SDL2/SDL.h>
#include "texture.h"
#include <sstream>

class KunaiCounter
{
public:
    KunaiCounter();
    static constexpr float SCALE_FACTOR = 0.85;
    static constexpr float WIDTH = 31*SCALE_FACTOR;
    static constexpr float HEIGHT = 15*SCALE_FACTOR;
    
    void set_position(float x, float y);
    void set_count(int count);
    void increase_count(int amount = 1);
    bool reduce_count(int amount = 1);
    void update_count();
    void render();
    ~KunaiCounter();
private:
    float m_position_x;
    float m_position_y;
    int m_count;
    SDL_Color m_color = {0x00, 0x00, 0x00};
    std::stringstream m_text_stream;
    static Texture m_trans_kunai;
    Texture m_text;
    void load_texture();
};
