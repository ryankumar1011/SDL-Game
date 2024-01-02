//
//  Texture_class.h
//  SDL-Game
//
//  Created by Ryan Kumar on 26/10/23.
//

#pragma once

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <iostream>

class Texture
{
public:

    Texture();
    
    bool load_from_file(const std::string& texture_path);
    
    bool load_from_font(TTF_Font* ptr_loaded_font, const std::string& text, const SDL_Color& font_color);
    
    void set_color_mod(const uint8_t &red, const uint8_t &green, const uint8_t &blue);

    void set_alpha_mod(const uint8_t &alpha);

    void set_blend_mode(SDL_BlendMode blendmode = SDL_BLENDMODE_BLEND); //alpha blending
    
    void set_color_key(const uint8_t &red, const uint8_t &green, const uint8_t &blue);
    
    void set_width(int width);
    
    void set_height(int height);
    
    int get_height();
        
    int get_width();
    
    SDL_Texture* get_texture();
    
    void render(float x = 0, float y = 0, SDL_Rect* p_clip = nullptr, float scale_factor = 1, SDL_RendererFlip flip_state = SDL_FLIP_NONE, float center_width = 0);

    void render(float x, float y, SDL_Rect* p_clip, float scale_factor, double angle, SDL_FPoint* center, SDL_RendererFlip flip_state);
    
    void free();
    
    ~Texture();
    
private:
    
    SDL_Texture* mp_texture;
    
    const SDL_PixelFormat* mp_format;
    
    float m_height;
    
    float m_width;
    
    uint32_t m_color_key;
};

