//
//  game_buttons.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 13/3/24.
//

#pragma once

#include "button.h"
#include <vector>
#include <SDL2/SDL.h>

class GameButtons
{
public:
    void insert(Button* p_button);
    void remove(Button* p_button);
    void handle_event(SDL_Event);
    void update();
    void render();

    
private:
    std::vector<Button*> mp_buttons;
};
