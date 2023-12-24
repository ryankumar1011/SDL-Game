//
//  function_declarations.h
//  SDL-Game
//
//  Created by Ryan Kumar on 4/11/23.
//

#pragma once

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
