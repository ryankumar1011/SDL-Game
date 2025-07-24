//
//  button.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 10/1/24.
//

#pragma once
#include "button_state.h"
#include <SDL2/SDL.h>

class Button
{
public:

    void set_position(float x, float y);
    virtual float get_width() = 0;
    virtual float get_height() = 0;
    void handle_event(SDL_Event& event);
    inline virtual void update() {}
    inline virtual void render() {};
    
    void update_hover_box();  //updates state of green box when mouse hovers over button
    void render_hover_box(); //renders this green box
    
protected:
    ButtonState m_state;
    SDL_FPoint m_position;
    bool m_hover;
};

