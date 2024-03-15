//
//  function_declarations.h
//  SDL-Game
//
//  Created by Ryan Kumar on 4/11/23.
//

#pragma once

#include <vector>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2/SDL.h>

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
class Shield;
class MenuButton;
class MusicButton;
class GameObjects;
class GameButtons;
 

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SCREEN_DIAGONAL;

extern SDL_Window* gp_window;
extern SDL_Renderer* gp_renderer;

extern GameObjects g_game_objects;
extern GameButtons g_game_buttons;

extern Texture g_menu;
extern Texture g_controls_manual;
extern bool g_menu_state;
extern bool g_controls_manual_state;

extern TTF_Font* gp_arial_font;
extern TTF_Font* gp_crayon_font;

extern Mix_Music* gp_background_music;
extern Mix_Chunk* gp_kunai_throw_sound;
extern Mix_Chunk* gp_kunai_hit_sound;
extern Mix_Chunk* gp_click_sound;
extern Mix_Chunk* gp_shield_hit_sound;
