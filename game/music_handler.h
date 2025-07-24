//
//  music_handler.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 13/3/24.
//

#pragma once

#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2/SDL.h>

namespace MusicHandler
{
void play_kunai_throw();

void play_kunai_hit();

void play_apple_hit();

void play_click();

void toggle_music();

void play_shield_hit();

void handle_event(SDL_Event event); //to change music with key input
};

