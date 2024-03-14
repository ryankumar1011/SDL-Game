//
//  music_handler.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 13/3/24.
//

#pragma once

#include "global_variables.h"
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>

namespace MusicHandler
{
    void play_kunai();

    void play_apple_hit();

    void toggle_music();

    void handle_event(SDL_Event event);
}



