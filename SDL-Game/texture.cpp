//
//  Texture.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 25/12/23.
//

#include "texture.h"
#include "global_variables.h"
#include <SDL2_image/SDL_image.h>

Texture::Texture()
    {
        m_height = 0;
        m_width = 0;
        m_color_key = 0;
        mp_texture = nullptr;
    }

bool Texture::load_from_file(const std::string& file_path)
{
    free();
    //If the Texture class already stores a loaded texture, this texture should be freed first
    
    SDL_Texture* p_loaded_texture = nullptr;
    SDL_Surface* p_loaded_surface = nullptr;
    
    //We first load surface, and then create texture from surface pixels
    //If we use surfaces, we would then convert them to display format using: optimized_surface = SDL_ConvertSurface(loaded_surface, my_surface->format, 0);
    //However, this is not necessary here
    //We still need the file path using this method since we nead to load the surface into memory first
    
    p_loaded_surface = IMG_Load(file_path.c_str());
    
    if (p_loaded_surface == nullptr)
        {
            printf("Error loading surface with path %s. ERROR: %s\n.", file_path.c_str(), IMG_GetError());
        }
    
    else
       {
           mp_format = (p_loaded_surface->format);
           
           // color keying makes a specified color transparent or removes it
           
           if (m_color_key == 0) // will be zero if no color key is set
           {
               m_color_key = SDL_MapRGB(mp_format, 0xFF, 0xFF, 0xFF); // this stores a pixel value
               
               //MapRGB generates pixel value with colour in the format of the used surface

           }
           
           SDL_SetColorKey(p_loaded_surface, SDL_TRUE, m_color_key); // set to true, meaning color key is enabled
                      
           p_loaded_texture = SDL_CreateTextureFromSurface(gp_renderer, p_loaded_surface);
           
           if (p_loaded_texture == NULL)
               
           {
               printf("Error loading texture with path %s, ERROR: %s\n", file_path.c_str(), SDL_GetError());
               
           }
           else
            {
               
               m_width = p_loaded_surface->w;
               m_height = p_loaded_surface->h;
               
            }
    
           SDL_FreeSurface(p_loaded_surface);
           
        }

    mp_texture = p_loaded_texture;

    return (p_loaded_texture != nullptr);
                
}

bool Texture::load_from_font(TTF_Font* p_loaded_font, const std::string& text, const SDL_Color& font_color)
{
    free();
    
    SDL_Surface* p_loaded_surface = nullptr;
    SDL_Texture* p_font_texture = nullptr;

    p_loaded_surface = TTF_RenderText_Blended(p_loaded_font, text.c_str(), font_color);
    
    if (p_loaded_surface == nullptr)
    {
        printf("Error loading surface with text %s. ERROR: %s\n", text.c_str(), TTF_GetError());
    }
    
    else
    {
    p_font_texture = SDL_CreateTextureFromSurface(gp_renderer, p_loaded_surface);
    
    if (p_font_texture == nullptr)
        
    {
        printf("Error loading texture with text %s, ERROR: %s\n", text.c_str(), SDL_GetError());
        
    }
    else
     {
        
        m_width = p_loaded_surface->w;
        m_height = p_loaded_surface->h;
        
     }

     SDL_FreeSurface(p_loaded_surface);
    
 }

 mp_texture = p_font_texture;
    
 return (p_font_texture != nullptr);
    
}

int Texture::get_height()
{
    return m_height;
}

int Texture::get_width()
{
  return m_width;
}

SDL_Texture* Texture::get_texture()
{
    return mp_texture;
}

void Texture::set_height(int height)
{
   m_height = height;
}

void Texture::set_width(int width)
{
   m_width = width;
}

void Texture::set_color_key(const uint8_t &red, const uint8_t &green, const uint8_t &blue)
{
    m_color_key = SDL_MapRGB(mp_format, red, green, blue);
}

void Texture::set_color_mod(const uint8_t& red, const uint8_t& green, const uint8_t& blue)
{
    SDL_SetTextureColorMod(mp_texture, red, green, blue);
}

void Texture::set_alpha_mod(const uint8_t& alpha)
{
    SDL_SetTextureAlphaMod(mp_texture, alpha);
}

void Texture::set_blend_mode(SDL_BlendMode blendmode)
{
    SDL_SetTextureBlendMode(mp_texture, blendmode);
}

//Below is the mainly used render function. It can render a texture, a clip of a sprite/texture and the flipped texture/clip. Using max_width, it can also render clips of a sprite so that they are all centered within a certain width (may be used for animations)

void Texture::render(float x, float y, SDL_Rect* p_clip, float scale_factor, SDL_RendererFlip flip_state, float center_width)

{
    SDL_FRect render_area{};

    if (p_clip == nullptr)
    {
        render_area = {x, y, scale_factor*m_width, scale_factor*m_height};
        SDL_RenderCopyExF(gp_renderer, mp_texture, nullptr, &render_area, 0, nullptr, flip_state);
    }
    else
    {
        float clip_width = scale_factor*(float)(p_clip->w);
        float clip_height = scale_factor*(float)(p_clip->h);
        center_width = center_width*scale_factor;
        
        if (clip_width > center_width && (center_width != 0) && flip_state == SDL_FLIP_HORIZONTAL)
        {
            //the animation expands leftwards with right side fixed
            render_area = {x - (clip_width - center_width), y, clip_width, clip_height};
            SDL_RenderCopyExF(gp_renderer, mp_texture, p_clip, &render_area, 0, nullptr, flip_state);
        }
        
        else if (center_width == 0 || clip_width > center_width)
        {
            //the animation expands rightwards with left side fixed
            render_area = {x, y, clip_width, clip_height};
            SDL_RenderCopyExF(gp_renderer, mp_texture, p_clip, &render_area, 0, nullptr, flip_state);
        }
        
        else
        {
            render_area = {x + (center_width - clip_width)/2, y, clip_width, clip_height};
            SDL_RenderCopyExF(gp_renderer, mp_texture, p_clip, &render_area, 0, nullptr, flip_state);
        }
    }
    
}

//The below render function is used when the rotated texture/clip needs to be rendered. Centering is not implemented for this yet

void Texture::render(float x, float y, SDL_Rect* p_clip, float scale_factor, double angle, SDL_FPoint* center, SDL_RendererFlip flip_state)
{
    SDL_FRect render_area{};

    if (p_clip == nullptr)
    {
        render_area = {x, y, m_width*scale_factor, m_height*scale_factor};
        SDL_RenderCopyExF(gp_renderer, mp_texture, p_clip, &render_area, angle, center, flip_state);    }
    else
    {
        render_area = {x, y, scale_factor*(float)p_clip->w, scale_factor*(float)p_clip->h};
        SDL_RenderCopyExF(gp_renderer, mp_texture, p_clip, &render_area, angle, center, flip_state);
    }
}

void Texture::free()
{
    SDL_DestroyTexture(mp_texture);
    mp_texture = nullptr;
    m_width = 0;
    m_height = 0;
    
}

Texture::~Texture()
{
    free();
}

