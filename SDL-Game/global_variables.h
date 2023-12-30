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
struct ChronoTimer;
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

extern Mix_Music* gp_background_music;
extern Mix_Chunk* gp_shuriken_sound;
extern Mix_Chunk* gp_apple_hit_sound;

extern Texture g_frame_rate_text;
extern Texture g_player_sprite;
extern Texture g_kunai_texture;
extern Texture g_heart_sprite;
