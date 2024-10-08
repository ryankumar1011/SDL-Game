//
//  variables.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 25/12/23.
//

#include "texture.h"
#include "game_objects.h"
#include "game_buttons.h"
#include "global_variables.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const int SCREEN_DIAGONAL = sqrt((SCREEN_WIDTH*SCREEN_WIDTH) + (SCREEN_HEIGHT*SCREEN_HEIGHT));

SDL_Window* gp_window = nullptr;
SDL_Renderer* gp_renderer = nullptr;

GameObjects g_game_objects;
GameButtons g_game_buttons;

Texture g_menu;
Texture g_controls_manual;
bool g_menu_state{};
bool g_controls_manual_state{};

//Fonts
TTF_Font* gp_arial_font = nullptr;
TTF_Font* gp_crayon_font = nullptr;

//Chunks and music from SDL mixer
Mix_Music* gp_background_music = nullptr;
Mix_Chunk* gp_kunai_throw_sound = nullptr;
Mix_Chunk* gp_kunai_hit_sound = nullptr;
Mix_Chunk* gp_click_sound = nullptr;
Mix_Chunk* gp_shield_hit_sound = nullptr;
Mix_Chunk* gp_apple_hit_sound = nullptr;




//Notes:

//Texture are efficient, driver-specific representation of pixel data. Textures are used during hardware rendering, and are stored in VRAM opposed to regular RAM, accelerating rendering operations using GPU. Meanwhile SDL_Surface is just a struct that contains pixel information.

//SDL_Renderer is a struct that handles ALL rendering and contains information about settings related to rendering
