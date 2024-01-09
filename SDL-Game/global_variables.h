//
//  function_declarations.h
//  SDL-Game
//
//  Created by Ryan Kumar on 4/11/23.
//

#pragma once

#include "sdl_libraries.h"
#include <vector>

class Texture;
class MouseButton;
class Weapons;
class SDLTimer;
class ChronoTimer;
class FrameRate;
class Object;
class Player;
class Kunai;
class Hearts;
class GameObjects;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SCREEN_DIAGONAL;

extern SDL_Window* gp_window;
extern SDL_Renderer* gp_renderer;

extern GameObjects g_game_objects;

extern TTF_Font* gp_arial_font;
extern TTF_Font* gp_crayon_font;

extern Mix_Music* gp_background_music;
extern Mix_Chunk* gp_shuriken_sound;
extern Mix_Chunk* gp_apple_hit_sound;
