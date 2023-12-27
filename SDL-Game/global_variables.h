//
//  function_declarations.h
//  SDL-Game
//
//  Created by Ryan Kumar on 4/11/23.
//

#pragma once

#include "sdl_libraries.h"

class Texture;
class MouseButton;
class Weapons;
class SDLTimer;
struct ChronoTimer;
class Object;
class Player;
class Kunai;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SCREEN_DIAGONAL;

extern SDL_Window* gp_window;
extern SDL_Renderer* gp_renderer;

extern SDL_Rect g_button_clips [4];
extern SDL_Rect g_player_clips [12];

extern TTF_Font* gp_arial_font;

extern Mix_Music* gp_background_music;
extern Mix_Chunk* gp_shuriken_sound;
extern Mix_Chunk* gp_apple_hit_sound;

extern Texture* p_current_texture;
extern Texture button_sprite;
extern Texture button_text;
extern Texture frame_rate_text;
extern Texture player_sprite;
extern Texture kunai_texture;
extern Texture heart_sprite;

