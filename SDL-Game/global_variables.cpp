//
//  variables.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 25/12/23.
//

#include "global_variables.h"
#include "texture.h"
#include "mouse_button.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const int SCREEN_DIAGONAL = sqrt((SCREEN_WIDTH*SCREEN_WIDTH) + (SCREEN_HEIGHT*SCREEN_HEIGHT));

SDL_Window* gp_window = nullptr;
SDL_Renderer* gp_renderer = nullptr;

//Texture are efficient, driver-specific representation of pixel data. Textures are used during hardware rendering, and are stored in VRAM opposed to regular RAM, accelerating rendering operations using GPU. Meanwhile SDL_Surface is just a struct that contains pixel information.

//SDL_Renderer is a struct that handles ALL rendering and contains information about settings related to rendering

//Clips
SDL_Rect g_player_clips[12];

//Fonts
TTF_Font* gp_arial_font = nullptr;

//Chunks and music from SDL mixer
Mix_Music* gp_background_music = nullptr;
Mix_Chunk* gp_shuriken_sound = nullptr;
Mix_Chunk* gp_apple_hit_sound = nullptr;

//Instantiating objects:
//Note - suffixes _sprite and _text are used to indicate textures of sprites and textures of texts respectively

Texture frame_rate_text;
Texture player_sprite;
Texture kunai_texture;
Texture heart_sprite;

//SDL_Rect g_button_clips [4];
//MouseButton g_buttons[4];

