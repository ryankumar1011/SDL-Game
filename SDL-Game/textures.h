//
//  Texture_class.h
//  SDL-Game
//
//  Created by Ryan Kumar on 26/10/23.
//

#pragma once

#include <string>
#include <chrono>

class Texture
{
public:

    Texture();
    
    bool load_from_file(const std::string& texture_path);
    
    bool load_texture_from_font(TTF_Font* ptr_loaded_font, const std::string& text, const SDL_Color& font_color);
        
    void set_color_mod(const uint8_t &red, const uint8_t &green, const uint8_t &blue);

    void set_alpha_mod(const uint8_t &alpha);

    void set_blend_mode(SDL_BlendMode blendmode = SDL_BLENDMODE_BLEND);
    
    void set_color_key(const uint8_t &red, const uint8_t &green, const uint8_t &blue);
    
    void set_font_color(const uint8_t &red, const uint8_t &green, const uint8_t &blue);
    
    int get_height();
        
    int get_width();
    
    std::string get_path();
    
    void render_texture(int x = 0, int y = 0, SDL_Rect* crop_image = nullptr, double angle = 0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    void free();
    
    ~Texture();
    
    
private:
    
    SDL_Texture* m_ptr_texture;
    
    const SDL_PixelFormat* m_ptr_format;
    
    SDL_Color m_font_color;
    
    int m_height;
    
    int m_width;
    
    uint32_t m_color_key;
    
    std::string m_texture_path;
    
};

