//
//  volume_button.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 13/3/24.
//

#pragma once 

#include "button_state.h"
#include "button.h"
#include "texture.h"
#include <SDL2/SDL.h>

class MusicButton : public Button
{
public:
    static constexpr float SCALE_FACTOR = 0.7;
    static constexpr float HEIGHT = 30*SCALE_FACTOR;
    static constexpr float WIDTH = 30*SCALE_FACTOR;
    
public:
    MusicButton();
    static Texture& get_texture_on();
    static Texture& get_texture_off();
    
    float get_width() override;
    float get_height() override;
    void update() override;
    void render() override;
    
private:
    bool m_sound = false;
    static Texture m_texture_on;
    static Texture m_texture_off;
};
