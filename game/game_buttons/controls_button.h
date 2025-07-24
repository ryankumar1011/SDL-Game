//
//  controls_button.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 14/3/24.
//

#pragma once

#include "button_state.h"
#include "button.h"
#include "texture.h"
#include <SDL2/SDL.h>

class ControlsButton : public Button
{
public:
    static constexpr float SCALE_FACTOR = 0.0206;
    static constexpr float HEIGHT = 980*SCALE_FACTOR;
    static constexpr float WIDTH = 980*SCALE_FACTOR;
    
public:
    ControlsButton();
    static Texture& get_texture();
    float get_width() override;
    float get_height() override;
    void update() override;
    void render() override;
    
private:
    static Texture m_texture;
};
