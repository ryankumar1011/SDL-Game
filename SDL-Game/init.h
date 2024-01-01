//
//  Intialize.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 25/12/23.
//

#pragma once

#include <SDL2_ttf/SDL_ttf.h>
#include <iostream>

bool init();
bool load_media();
bool load_images();
bool load_fonts();
TTF_Font* load_font_from_file(const std::string& font_path, int font_size);
bool load_texts();
bool load_audio();
void initialize_media();
void set_up_buttons();
void set_texture_clips();
void set_texture_size();
void close();

