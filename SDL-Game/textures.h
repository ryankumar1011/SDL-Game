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
    
    bool load_from_file(const std::string&);
    
    bool load_from_font_file(const std::string&, SDL_Color text_color);
        
    void set_color_mod(uint8_t red, uint8_t green, uint8_t blue);

    void set_alpha_mod(uint8_t alpha);

    void set_blend_mode(SDL_BlendMode blendmode = SDL_BLENDMODE_BLEND);
    
    void set_color_key(uint8_t red, uint8_t green, uint8_t blue);
    
    void render_texture(int x = 0, int y = 0, SDL_Rect* crop_image = nullptr, double angle = 0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    void free();
    
    ~Texture();
    
    int get_height();
        
    int get_width();
    
    std::string get_path();
    
private:
    
    SDL_Texture* m_texture;
    
    const SDL_PixelFormat* m_format;
    
    int m_height;
    
    int m_width;
    
    uint32_t m_color_key;
    
    std::string m_texture_path;
    
};

