//
//  menu_button.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 10/1/24.
//

#pragma once
#include "button_state.h"
#include "button.h"
#include "texture.h"
#include <SDL2/SDL.h>

class MenuButton : public Button
{
public:
    static constexpr float SCALE_FACTOR = 0.7;
    static constexpr float HEIGHT = 30*SCALE_FACTOR;
    static constexpr float WIDTH = 30*SCALE_FACTOR;

public:
    MenuButton();
    static Texture& get_texture();
    float get_width() override;
    float get_height() override;
    void update() override;
    void render() override;

private:
    static Texture m_texture;
};
