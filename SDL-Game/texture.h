//
//  Texture_class.h
//  SDL-Game
//
//  Created by Ryan Kumar on 26/10/23.
//

#pragma once

#include "sdl_libraries.h"
#include <iostream>

class Texture
{
    
public:

    Texture();
    
    
    bool load_from_file(const std::string& texture_path);
    
    bool load_from_font(TTF_Font* ptr_loaded_font, const std::string& text, const SDL_Color& font_color);
    
        
    void set_color_mod(const uint8_t &red, const uint8_t &green, const uint8_t &blue);

    void set_alpha_mod(const uint8_t &alpha);

    void set_blend_mode(SDL_BlendMode blendmode = SDL_BLENDMODE_BLEND);
    
    void set_color_key(const uint8_t &red, const uint8_t &green, const uint8_t &blue);
    
    void set_font_color(const uint8_t &red, const uint8_t &green, const uint8_t &blue);
    
    void set_width(int width);
    
    void set_height(int height);
    
    void set_flip_state(SDL_RendererFlip flip_state);
    
    
    int get_height();
        
    int get_width();
   
    std::string get_path();
    
    
    void render_texture(int x = 0, int y = 0, SDL_Rect* p_clip = nullptr, int max_dim = 0, SDL_RendererFlip flip_state = SDL_FLIP_NONE);
    void render_texture(int x, int y, SDL_Rect* p_clip, double angle, SDL_Point* center, SDL_RendererFlip flip_state);
    
    void free();
    
    
    ~Texture();
    
    
private:
    
    SDL_Texture* mp_texture;
    
    const SDL_PixelFormat* mp_format;
    
    SDL_Color m_font_color;
    
    int m_height;
    
    int m_width;
    
    uint32_t m_color_key;
    
    std::string m_texture_path;
    
};

