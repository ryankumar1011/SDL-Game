//
//  main.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 22/10/23.
//

//SDL libraries:
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

//C libraries:
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>

//header files:
#include "function_declarations.h"
#include "textures.h"
#include "mouse_button.h"
#include "timer.h"

static const int SCREEN_WIDTH = 600;
static const int SCREEN_HEIGHT = 600;
static const int SCREEN_DIAGONAL = sqrt((SCREEN_WIDTH*SCREEN_WIDTH) + (SCREEN_HEIGHT*SCREEN_HEIGHT));

SDL_Window* g_ptr_window = nullptr;
SDL_Texture* g_ptr_current_texture_display = nullptr;
SDL_Renderer* g_ptr_renderer = nullptr;
//Texture are efficient, driver-specific representation of pixel data. Textures are used during hardware rendering, and are stored in VRAM opposed to regular RAM, accelerating rendering operations using GPU. Meanwhile SDL_Surface is just a struct that contains pixel information.
// SDL_Renderer is a struct that handles ALL rendering and contains information about settings related to rendering

//clips
SDL_Rect g_button_clips [4];

//fonts
TTF_Font* g_ptr_arial_font = nullptr;

//chunks and music from SDL mixer
Mix_Music* g_ptr_background_music = nullptr;
Mix_Chunk* g_ptr_shuriken_sound = nullptr;
Mix_Chunk* g_ptr_apple_hit_sound = nullptr;

//Instantiating objects:
Texture* ptr_current_texture;
Texture button_sprite_texture;
Texture text_texture;
Texture text_time_texture;

MouseButton g_buttons[4];

Texture::Texture()
    {
        m_height = 0;
        m_width = 0;
        m_ptr_texture = nullptr;
        m_color_key = 0;

    }

bool Texture::load_from_file(const std::string& texture_path)
{
    free();
    
    SDL_Texture* ptr_loaded_texture = nullptr;
    SDL_Surface* ptr_loaded_surface = nullptr;
    m_texture_path = texture_path;

        
        // We first load surface, and then create texture from surface pixels (instead of converting it into display format, which we do with optimized_surface and SDL_ConvertSurface)
        // We still need the file path using this method since we nead to load the surface into memory first
    ptr_loaded_surface = IMG_Load(m_texture_path.c_str());
    
    if (ptr_loaded_surface == nullptr)
        {
            printf("Error loading surface with path %s. ERROR: %s\n. ERROR: %s\n", texture_path.c_str(), SDL_GetError(), IMG_GetError());
        }
    
    else
       {
           m_ptr_format = (ptr_loaded_surface->format);
           
           if (m_color_key == 0) m_color_key = SDL_MapRGB(m_ptr_format, 0xFF, 0xFF, 0xFF);
           
           SDL_SetColorKey(ptr_loaded_surface, SDL_TRUE, m_color_key);
           
           //MapRGB generates pixel colour to be made transperent, which is in the format of the used surface
           
           ptr_loaded_texture = SDL_CreateTextureFromSurface(g_ptr_renderer, ptr_loaded_surface);
           
           if (ptr_loaded_texture == NULL)
               
           {
               printf("Error loading texture with path %s, ERROR: %s\n",m_texture_path.c_str(), SDL_GetError());
               
           }
           else
            {
               
               m_width = ptr_loaded_surface->w;
               m_height = ptr_loaded_surface->h;
               
            }
    
           SDL_FreeSurface(ptr_loaded_surface);
           
        }

    m_ptr_texture = ptr_loaded_texture;

    return (ptr_loaded_texture != nullptr);
                
}

bool Texture::load_texture_from_font(TTF_Font* ptr_loaded_font, const std::string& text, const SDL_Color& font_color)
{
    free();
    
    SDL_Surface* ptr_loaded_surface = nullptr;
    SDL_Texture* ptr_font_texture = nullptr;

    ptr_loaded_surface = TTF_RenderText_Blended(ptr_loaded_font, text.c_str(), font_color);
    
    if (ptr_loaded_surface == nullptr)
    {
        printf("Error loading texture of font with text %s. ERROR: %s\n", text.c_str(), TTF_GetError());
    }
    
    else
    {
    ptr_font_texture = SDL_CreateTextureFromSurface(g_ptr_renderer, ptr_loaded_surface);
    
    if (ptr_font_texture == nullptr)
        
    {
        printf("Error loading texture with text %s, ERROR: %s\n", text.c_str(), SDL_GetError());
        
    }
    else
     {
        
        m_width = ptr_loaded_surface->w;
        m_height = ptr_loaded_surface->h;
        
     }

     SDL_FreeSurface(ptr_loaded_surface);
    
 }

 m_ptr_texture = ptr_font_texture;
 m_font_color = font_color;

 return (ptr_font_texture != nullptr);
    
}

int Texture::get_height()
{
    return m_height;
}

int Texture::get_width()
{
  return m_width;
    
}

void Texture::set_font_color(const uint8_t &red, const uint8_t &green, const uint8_t &blue)
{
    m_font_color = {red, green, blue};
}

void Texture::set_color_key(const uint8_t &red, const uint8_t &green, const uint8_t &blue)
{
    m_color_key = SDL_MapRGB(m_ptr_format, red, green, blue);
    
}

std::string Texture::get_path()
{
    return m_texture_path;
}

void Texture::set_color_mod(const uint8_t& red, const uint8_t& green, const uint8_t& blue)
{
    SDL_SetTextureColorMod(m_ptr_texture, red, green, blue);
    
}

void Texture::set_alpha_mod(const uint8_t& alpha)

{
    SDL_SetTextureAlphaMod(m_ptr_texture, alpha);
}

void Texture::set_blend_mode(SDL_BlendMode blendmode)

{
    SDL_SetTextureBlendMode(m_ptr_texture, blendmode);
}

void Texture::render_texture(int x, int y, SDL_Rect* ptr_clip, double angle, SDL_Point* center, SDL_RendererFlip flip_state)
{
    SDL_Rect render_area;
   
    if (ptr_clip == nullptr)
        
    {
        render_area = {x, y, m_width, m_height};
       // SDL_RenderCopy(my_renderer, m_texture, NULL, &render_area);
        
    }
    
    else
    {
        render_area = {x, y, ptr_clip->w, ptr_clip->h};
    }
    
    SDL_RenderCopyEx(g_ptr_renderer, m_ptr_texture, ptr_clip, &render_area, angle, center, flip_state);
    // SDL_RenderCopy(my_renderer, m_texture, crop_image, &render_area);
    //Third parameter is portion of texture to crop
    //Fourth parameter is portion of target to copy into
}

void Texture::free()
{
    SDL_DestroyTexture(m_ptr_texture);
    m_ptr_texture = nullptr;
    m_width = 0;
    m_height = 0;
    
}

Texture::~Texture()
{
    free();
}


MouseButton::MouseButton()
{
    m_position = {0,0};
    
    m_width = 0;
    m_height = 0;
    
    m_current_clip = MOUSE_CLIP_OUT;
    
}

void MouseButton::handle_mouse_event (SDL_Event* ptr_event)
{
    if ((ptr_event->type == SDL_MOUSEBUTTONDOWN) || (ptr_event->type == SDL_MOUSEBUTTONUP) || (ptr_event->type == SDL_MOUSEMOTION))
    {
        m_current_clip = MOUSE_CLIP_OUT;
        
        int x, y;
        
        SDL_GetMouseState(&x, &y);
        
        bool inside_button = true;
        
        
        if (x < m_position.x)
            
            inside_button = false;
        
        else if (x > (m_position.x + m_width))
            
            inside_button = false;
        
        else if (y < m_position.y)
            
            inside_button = false;
        
        
        else if (y > (m_position.y + m_height))
            
            inside_button = false;
        
        if (inside_button)
        {
            m_current_clip = MOUSE_CLIP_OVER;
            
            switch (ptr_event->type)
            {
                    
                case SDL_MOUSEBUTTONDOWN:
                    m_current_clip = MOUSE_CLIP_PRESS_DOWN;
                    break;
                    
                case SDL_MOUSEBUTTONUP:
                    m_current_clip = MOUSE_CLIP_PRESS_UP;
                    break;
                    
                case SDL_MOUSEMOTION:
                    m_current_clip = MOUSE_CLIP_MOVE_OVER;
                    break;
                    
                 case SDL_MOUSEWHEEL:
                    m_current_clip = MOUSE_CLIP_SCROLL_OVER;
                    break;
            }
        }
    }
}
    
    
void MouseButton::set_position (int x, int y)
{
    
    m_position.x = x;
    m_position.y = y;
    
}

void MouseButton::set_width(int width)
{
    m_width = width;
}

void MouseButton::set_height(int height)
{
    m_height = height;
}

void MouseButton::set_button_sprite_texture(Texture* ptr_button_sprite_texture)
{
    m_ptr_button_sprite_texture = ptr_button_sprite_texture;
}

int MouseButton::get_current_clip()
{
    return m_current_clip;
    
}

void MouseButton::handle_extra_clip_states()

{
    m_ptr_button_sprite_texture->set_color_mod(0xFF, 0xFF, 0xFF);
    
    if (m_current_clip == MOUSE_CLIP_MOVE_OVER)
    {
        m_ptr_button_sprite_texture->set_color_mod(0x00, 0x60, 0x00);
        m_current_clip = MOUSE_CLIP_OVER;
    }
    if (m_current_clip == MOUSE_CLIP_SCROLL_OVER)
    {
        m_ptr_button_sprite_texture->set_color_mod(0x00, 0x60, 0x00);
        m_current_clip = MOUSE_CLIP_OVER;
    }

}

void MouseButton::render_button()
{
    handle_extra_clip_states();
    m_ptr_button_sprite_texture->render_texture(m_position.x, m_position.y, &g_button_clips[m_current_clip]);
}

bool init()
{
    
    bool success{true}; //flag for function (init) is set at start
    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        
        //can also only initialize video sub system, use SDL_INIT_EVERYTHING/SDL_INIT_VIDEO
    {
        success = false;
        printf("Error initializing everything. ERROR: %s\n", SDL_GetError());
    }
    
    else
        
    {
        Mix_Init(MIX_INIT_FLAC|MIX_INIT_MP3);
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            
        {
            printf("Warning: linear texture filtering not enabled\n");
        }
        
        else
        {
            g_ptr_window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
            
            if (TTF_Init() == -1)
            {
                printf("Error initializing TTF. ERROR: %s\n", TTF_GetError());
            }
            else
            {
                
                if (g_ptr_window == nullptr)
                    
                {
                    success = false;
                    printf("Error creating window. ERROR: %s\n", SDL_GetError());
                }
                else
                {
                    int sdl_image_flags = IMG_INIT_PNG;
                    // can use | (or bitwise operator) for multiple flags
                    // !(IMG_Init(sdl_image_flags) & sdl_image_flags) is only used to check is Init for PNG failed
                    
                    if (!(IMG_Init(sdl_image_flags) == sdl_image_flags))
                        
                    {
                        printf("Error initializing SDL_Image. ERROR: %s\n", IMG_GetError());
                        success = false;
                    }
                    
                    else
                        
                    {
                        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                        {
                            printf("Error initializing SDL_Mixer. ERROR: %s\n", Mix_GetError());
                            
                        }
                        
                        else
                        {
                            
                            g_ptr_renderer = SDL_CreateRenderer(g_ptr_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                            
                            if (g_ptr_renderer == nullptr)
                                
                            {
                                success = false;
                                printf("Error initializing renderer. ERROR: %s\n", SDL_GetError());
                                
                            }
                            
                            SDL_SetRenderDrawColor(g_ptr_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                        }
                    }
                }
            }
        }
    }
    
    return success;
}

bool load_media()
{
    
    bool success = true;
    
    if (!load_image_textures()) success = false;
    if (!load_fonts()) success = false;
    if (!load_text_textures()) success = false;
    if (!load_audio()) success = false;
    
    initialize_media();
    
    return success;
    
}

bool load_image_textures()
{
    bool success = true;
    
    if (!button_sprite_texture.load_from_file("Images/buttons.png"))
    {
        success = false;
        printf("Failed to load buttons image\n");
    }
    
    return success;
}

bool load_fonts()
{
    bool success = true;
    
    g_ptr_arial_font = load_font_from_file("Fonts/Arial.ttf", 20);
    
    if (g_ptr_arial_font == nullptr) success = false;
    
    return success;

}

TTF_Font* load_font_from_file(const std::string& font_path, int font_size)
{
    
    TTF_Font* ptr_font;
    
    ptr_font = (TTF_OpenFont(font_path.c_str(), font_size));
    
    if (ptr_font == nullptr)
    {
        printf("Failed to load font from font file with font_path %s\n", font_path.c_str());
        
    }
    
    return ptr_font;
    
}

bool load_text_textures()
{
    bool success = true;
    
    SDL_Color text_color = {0x50, 0x00, 0x00};
    
    if (!text_texture.load_texture_from_font(g_ptr_arial_font, "Move over buttons to change color!", text_color)) success = false;
    
    return success;
    
}

bool load_audio()
{
    bool success = true;
    
    g_ptr_background_music = Mix_LoadMUS("Audio/background_music.mp3");
   
    if (g_ptr_background_music == nullptr)
    {
        success = false;
        printf("Failed to load background music\n");
    }
    
    g_ptr_shuriken_sound = Mix_LoadWAV("Audio/shuriken2.wav");
    
    if (g_ptr_shuriken_sound == nullptr)
    {
        success = false;
        printf("Failed to load shuriken audio\n");
    }
    g_ptr_apple_hit_sound = Mix_LoadWAV("Audio/apple_hit2.wav");
    
    if (g_ptr_apple_hit_sound == nullptr)
    {
        success = false;
        printf("Failed to load apple hit audio\n");
    }
    
    return success;
}

void initialize_media()
{
    set_up_buttons();
    set_texture_clips();
}

void set_up_buttons()
{
    for (int i = 0; i < 4; i++)
    {
       g_buttons[i].set_button_sprite_texture(&button_sprite_texture);
       g_buttons[i].set_width(300);
       g_buttons[i].set_height(300);
    }
    g_buttons[0].set_position(0, 0);
    g_buttons[1].set_position(300, 0);
    g_buttons[2].set_position(0, 300);
    g_buttons[3].set_position(300, 300);
     
}

void set_texture_clips()
{
    g_button_clips[0] = {0, 0, 300, 300};
    g_button_clips[1] = {300, 0, 300, 300};
    g_button_clips[2] = {0, 300, 300, 300};
    g_button_clips[3] = {300, 300, 300, 300};
    
}

void close()
{
    // Destroyed all LOADED surfaces and textures
    
    button_sprite_texture.free();
    text_texture.free();
    text_time_texture.free();
     
    TTF_CloseFont(g_ptr_arial_font); //we need to close a font that is opened from TTF_OpenFont

    Mix_FreeMusic(g_ptr_background_music);
    Mix_FreeChunk(g_ptr_shuriken_sound);
    Mix_FreeChunk(g_ptr_apple_hit_sound);
    
    // Destroy Windows and Renderer, set pointers to NULL
    SDL_DestroyWindow(g_ptr_window);
    //Takes care of destroying my_screen_surface/my_current_texture
    SDL_DestroyRenderer(g_ptr_renderer);
    g_ptr_window = nullptr;
    g_ptr_renderer = nullptr;
    
    //Just like you initialize them, you have to quit SDL subsystems
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char* args[])
{
   if (!init())
   {
       printf("Error initializing. ERROR: %s\n", SDL_GetError());
   }
   else
   {
       
       if (!load_media())
       {
           printf("Error loading media. ERROR: %s\n", SDL_GetError());
       }
       else
       {
           
           bool quit = false; //Main loop flag
           SDL_Event event;
           ptr_current_texture = &text_texture;
           uint64_t time_after_last_reset {0};
           std::stringstream time_to_print;
           while (quit != true)
              
          {
              while (SDL_PollEvent(&event) != 0)
                  {
        
                  if (event.type == SDL_QUIT)
                      
                  {
                      quit = true;
                  }
                  
                  if (event.type == SDL_KEYUP)
                  {
                      switch (event.key.keysym.sym)
                      {
                              
                          case SDLK_m:
        
                              if (Mix_PlayingMusic() == 0) Mix_PlayMusic(g_ptr_background_music, -1);
                              
                              else if (Mix_PausedMusic() == 1) Mix_ResumeMusic();
                              
                              else Mix_PauseMusic();
                              
                              break;
                              
                          case SDLK_d:
                              Mix_PlayChannel(-1, g_ptr_shuriken_sound, 0);
                              break;
                              
                          case SDLK_f:
                              Mix_PlayChannel(-1, g_ptr_apple_hit_sound, 0);
                              break;
                              
                          case SDLK_r:
                              time_after_last_reset = SDL_GetTicks64();
                              break;
                      }
                      
                  }
                    
                  for (int i = 0; i < 4; i++)
                      
                      {
                          g_buttons[i].handle_mouse_event(&event);
                      }
    
              }
              
              SDL_SetRenderDrawColor(g_ptr_renderer, 0x2F, 0xFF, 0xFF, 0xFF);
              SDL_RenderClear(g_ptr_renderer);
              
              for (int i = 0; i < 4; i++)
                      
                {
                    g_buttons[i].render_button();
                          
                }
              
              text_texture.render_texture((SCREEN_WIDTH - ptr_current_texture->get_width())/2, (SCREEN_HEIGHT - ptr_current_texture->get_height())/2);
              
              time_to_print.str(""); //.str() discards previous content of stream and places new as ""
              
              time_to_print << "The time is " << (SDL_GetTicks64() - time_after_last_reset);
              
              text_time_texture.load_texture_from_font(g_ptr_arial_font, time_to_print.str(), {0x00, 0x00, 0x00});
              //.str() here converts copies stringstream into a string object and returns that
              
              text_time_texture.render_texture(240, 270);
              
              SDL_RenderPresent(g_ptr_renderer);
           }
       }
   }
    
    close();
    return 0;
}

// Emmited code written during practice, can be used later:

/*
SDL_Surface* load_surface(std::string path, FileType file_type)
{
    SDL_Surface* loaded_surface = nullptr;
    SDL_Surface* optimized_surface = nullptr;
    
    switch (file_type)
    {
        case TYPE_BMP:
            loaded_surface = SDL_LoadBMP(path.c_str());
            //.c_str() converts string to array with \0 (c-style string)
            break;
            
        case TYPE_PNG:
            loaded_surface = IMG_Load(path.c_str());
            break;
            
        default:
            printf("Error loading surface with path %s.\n Type is invalid", path.c_str());
            return nullptr;
            
    }
    
    if (loaded_surface == NULL)
    {
        printf("Error loading surface with path %s. ERROR: %s\n. ERROR: %s\n", path.c_str(), SDL_GetError(), IMG_GetError());
        // takes const char* as parameter type
    }
    else
        {
            optimized_surface = SDL_ConvertSurface(loaded_surface, my_surface->format, 0);
            // -> helps to access format in struct my_surface easily, since my_surface is a pointer and not actually an object (allocated on heap)
            // sometimes we only have a pointer to a class or struct (maybe allocated on heap), to access members we use -> instead of dereferencing pointer
            // so it would be same asame as (*my_surface).format
            if (optimized_surface == NULL)
            {
                printf("Error optimizing surface with path %s. ERROR: %s\n. ERROR: %s\n", path.c_str(), SDL_GetError(), IMG_GetError());
            }
      
            
        SDL_FreeSurface(loaded_surface);
        }
    
 return optimized_surface;

}
*/

/*
SDL_Texture* load_texture(const std::string& path, unsigned char file_type)

{
    
    SDL_Texture* loaded_texture = nullptr;
    SDL_Surface* loaded_surface = nullptr;
    
    // We first load surface, and then create texture from surface pixels (instead of converting it into display format, which we do with optimized_surface and SDL_ConvertSurface)
    // We still need the file path using this method since we nead to load the surface into memory first
    switch (file_type)
    {
        case TYPE_BMP:
            loaded_surface = SDL_LoadBMP(path.c_str());
            //.c_str() converts string to array with \0 (c-style string)
            // we use it whenever we want a const char* from an std::string type
            break;
            
        case TYPE_PNG:
            loaded_surface = IMG_Load(path.c_str());
            break;
    }
    if (loaded_surface == NULL)
    {
        printf("Error loading surface with path %s. ERROR: %s\n. ERROR: %s\n", path.c_str(), SDL_GetError(), IMG_GetError());
        // takes const char* as parameter type
    }
    else
    {
        loaded_texture = SDL_CreateTextureFromSurface(my_renderer, loaded_surface);
        if (loaded_texture == NULL)
        {
            printf("Error loading texture with path %s, ERROR: %s\n",path.c_str(), SDL_GetError());
            
        }
        SDL_FreeSurface(loaded_surface);
   }
    
    return loaded_texture;

}
*/
/*
 SDL_Rect crop_rect; // rectangle to be copied
 // x and y start from top left corner, goes to the right and downwards as x and y increase
 crop_rect.x = 40; // starting x and y
 crop_rect.y = 50;
 crop_rect.h = 400;
 crop_rect.w = 500;

 SDL_Rect stretch_rect; // rectangle that surface is copied into
 stretch_rect.x = 0;
 stretch_rect.y = 0;
 stretch_rect.h = SCREEN_HEIGHT;
 stretch_rect.w = SCREEN_WIDTH;
 
 */
/*
 bool load_media() //can be used for textures or surfaces
 {
     bool success = true;
     key_press_surfaces[DEFAULT_SURFACE] = load_IMG_texture("loaded.png");
     // remember that string literals are of type const char* not just char*
     if (key_press_surfaces[DEFAULT_SURFACE] == NULL)
     {
         printf("Failed to load default image");
         success = false;
     }
     key_press_surfaces[PRESS_KEYBOARD_UP] = load_IMG_texture("up.bmp");
     if (key_press_surfaces[PRESS_KEYBOARD_UP] == NULL)
     {
         printf("Failed to load up image");
         success = false;
     }
     
     key_press_surfaces[PRESS_KEYBOARD_DOWN] = load_IMG_texture("down.bmp");
     if ( key_press_surfaces[PRESS_KEYBOARD_DOWN] == NULL)
     {
         printf("Failed to load down image");
         success = false;
     }
     key_press_surfaces[PRESS_KEYBOARD_LEFT] = load_IMG_texture("left.bmp");
     if (key_press_surfaces[PRESS_KEYBOARD_LEFT] == NULL)
     {
         printf("Failed to load left image");
         success = false;
     }
     key_press_surfaces[PRESS_KEYBOARD_RIGHT] = load_IMG_texture("right.bmp");
     if (key_press_surfaces[PRESS_KEYBOARD_RIGHT] == NULL)
     {
         printf("Failed to load right image");
         success = false;
     }
     
     return success;
 }
 */
/*
 void close()
 {
     // Destroyed all LOADED surfaces and textures
     
     for (int i = 0; i < PRESS_KEYBOARD_TOTAL; i++)
     {
         SDL_DestroyTexture(key_press_surfaces[i]);
         key_press_surfaces[i] = NULL;
     }
     
     // Destroy Windows and Renderer, set pointers to NULL
     
     SDL_DestroyWindow(my_window);
     //Takes care of destroying my_screen_surface/my_current_texture
     SDL_DestroyRenderer(my_renderer);
     my_window = NULL;
     my_renderer = NULL;
     
     //Just like you initialize them, you have to quit SDL subsystems
     
     IMG_Quit();
     SDL_Quit();
 }
 */
/*
 if (event.type == SDL_QUIT) //what is the type compared?
 {
 quit = true;
 }
 else if (event.type == SDL_KEYDOWN)
 {
 switch(event.key.keysym.sym) // key symbol, accessing other unions in union?
 {
 case SDLK_UP:
 current_texture_display = key_press_surfaces[PRESS_KEYBOARD_UP];
 break;
 
 case SDLK_DOWN:
 current_texture_display = key_press_surfaces[PRESS_KEYBOARD_DOWN];
 break;
 
 case SDLK_LEFT:
 current_texture_display = key_press_surfaces[PRESS_KEYBOARD_LEFT];
 break;
 
 case SDLK_RIGHT:
 current_texture_display = key_press_surfaces[PRESS_KEYBOARD_RIGHT];
 break;
 
 }
 */
/*
When using surfaces instead of textures:

SDL_BlitScaled (current_surface_display, &crop_rect, my_surface, &stretch_rect);
// or SDL_BlitSurface(current_surface_display, NULL, my_surface, NULL);
SDL_UpdateWindowSurface(my_window);

*/
/*
 SDL_Texture* load_IMG_texture(const std::string& path)
 {
     SDL_Texture* loaded_texture = nullptr;
     
     loaded_texture = IMG_LoadTexture(my_renderer, path.c_str());
     // function requires a const char pointer
     // no file type required, only rendered and path of file
     if (loaded_texture == NULL)
     {
         printf("Error loading texture with path %s, ERROR: %s\n", path.c_str(), IMG_GetError());
         
     }
     
     return loaded_texture;
 }
 */
/*
SDL_RenderCopy(my_renderer, current_texture_display,NULL, NULL);
//primative rendering allows for drawing basic shapes withouth loading textures. So you don't need RenderCopy to draw texture on target

SDL_SetRenderDrawColor(my_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
SDL_RenderClear(my_renderer);

//clears target to set colour (fills target with the colour set)
//Errors in colouting occur withouth initializing background colour to this

SDL_Rect top_left_viewport = {0,0,SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
SDL_Rect top_right_viewport = {SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};


SDL_RenderSetViewport(my_renderer, &top_left_viewport);
SDL_RenderCopy(my_renderer, current_texture_display, NULL, NULL);
SDL_RenderSetViewport(my_renderer, &top_right_viewport);
SDL_RenderCopy(my_renderer, current_texture_display, NULL, NULL);

SDL_Rect bottom_viewport = {0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2};
//unspecified members will be initialized as zero
//can also use designated initiliazers. It is same as:
//SDL_Rect bottom_viewport = {.y = SCREEN_WIDTH/2, .h = SCREEN_HEIGHT/2, .w = SCREEN_WIDTH};

SDL_RenderSetViewport(my_renderer, &bottom_viewport);

SDL_SetRenderDrawColor(my_renderer, 0xFF, 0x00, 0x00, 0xFF);
SDL_Rect rectangle_filled = {(SCREEN_WIDTH/2) - 100, (SCREEN_HEIGHT/2) - 100, 200, 200};
// can initialize a struct my listing and initializing its variables

SDL_RenderFillRect(my_renderer, &rectangle_filled);
// takes in a rectangle shape and fills it on the current rendering target

SDL_SetRenderDrawColor(my_renderer, 0x00, 0xFF, 0xFF, 0xFF);
SDL_Rect rectangle_drawed = {(SCREEN_WIDTH/2) - 50, (SCREEN_HEIGHT/2) - 50, 100, 100};
SDL_RenderDrawRect(my_renderer, &rectangle_drawed);

SDL_SetRenderDrawColor(my_renderer, 0x00, 0x20, 0x00, 0xFF);
SDL_RenderDrawLine(my_renderer, 0, SCREEN_HEIGHT, SCREEN_WIDTH, 0);

SDL_SetRenderDrawColor(my_renderer, 0x00, 0x00, 0xF0, 0xFF);
for (int i = 0; i < SCREEN_DIAGONAL; i += 2)
{
    SDL_RenderDrawPoint(my_renderer, i, i);
}

//What is SDL_SetRenderTarget?
//SDL_RenderGetViewport?
 

// SDL_RenderCopy(my_renderer, current_texture_display, &crop_rect, &stretch_rect);
//draws texture to hidden target (according to associated rendering settings and the crop and stretch set)
SDL_RenderPresent(my_renderer);
//draws content of hidden target onto window associated to renderer
//Note: there can't be more than one renderer

*/
/*
 if(event.type != SDL_KEYUP) default_texture.render_texture();
 
 else
 {
     switch(event.key.keysym.sym) // key symbol, accessing other unions in union?
         
     {
         case SDLK_UP:
             up_texture.render_texture();
             break;
             
         case SDLK_DOWN:
             down_texture.render_texture();
             break;
             
         case SDLK_LEFT:
             left_texture.render_texture();
             break;
             
         case SDLK_RIGHT:
             right_texture.render_texture();
             break;
     }
 }
 */
/*
 case SDLK_UP:
     current_texture = &up_texture;
     break;
     
 case SDLK_DOWN:
     current_texture = &down_texture;
     break;
     
 case SDLK_LEFT:
     current_texture = &left_texture;
     break;
     
 case SDLK_RIGHT:
     current_texture = &right_texture;
     break;
 */
/*

dots_texture.set_color_mod(red, green, blue);
dots_texture.set_alpha_mod(alpha);

//font_texture.render_texture((SCREEN_WIDTH - current_texture->get_width())/2, (SCREEN_HEIGHT - current_texture->get_height())/2);

dots_texture.render_texture(0, 0, &dot_clips[0]);
dots_texture.render_texture(SCREEN_WIDTH -100, 0, &dot_clips[1]);
dots_texture.render_texture(0, SCREEN_HEIGHT - 100, &dot_clips[2]);
dots_texture.render_texture(SCREEN_WIDTH -100, SCREEN_HEIGHT - 100, &dot_clips[3]);
current_texture.render_texture();
 */

//smiles_texture.render_texture(415, 325, &g_smiles_clips[frame/15]);

//we use a pointer to object to fix issue with texture display. It is not possible to point to a class itself since they are not created at runtime - the objects are.
//flip_state = SDL_FLIP_VERTICAL;
//if ((frame % 10) == 0) flip_state = SDL_FLIP_NONE;
/*

if (frame < 15)
{
    arrow_texture.render_texture(30, 400, &g_stick_figure_clips[0]);
    stick_figure_backflip.render_texture(100, 400, &g_stick_figure_backflip_clips[0]);
}
else if (frame < 30)
{
    arrow_texture.render_texture(50, 400, &g_stick_figure_clips[1]);
    stick_figure_backflip.render_texture(200, 400, &g_stick_figure_backflip_clips[1]);

}

else if (frame < 45)
{
    arrow_texture.render_texture(80, 400, &g_stick_figure_clips[2]);
    stick_figure_backflip.render_texture(300, 400, &g_stick_figure_backflip_clips[2]);
}

else if (frame < 60)
{
    stick_figure_backflip.render_texture(400, 400, &g_stick_figure_backflip_clips[3]);
}

arrow_texture.render_texture( 500, 500, &g_arrow_clip, angle, nullptr, flip_state);

angle += 3;
if (angle == 180) angle = 0;

++frame;

if (frame == 60) frame = 0;

SDL_RenderPresent(g_renderer);

// auto start = std::chrono::high_resolution_clock::now();
// SDL_WaitEvent(&event);
*/
/*
 switch(event.key.keysym.sym) // key symbol, accessing other unions in union?
      
  {
        
      case SDLK_r:
          if (red + 25 <= 255) red += 25;
          break;
          
      case SDLK_g:
          if (green + 25 <= 255) green += 25;
          break;
          
      case SDLK_b:
          if (blue + 25 <= 255) blue += 25;
          break;
          
      case SDLK_l:
          if ((alpha - 10)>= 0) alpha -= 10;
          else alpha = 0;
          break;
          
      case SDLK_a:
          if ((alpha + 10) <= 255) alpha += 10;
          else alpha = 255;
          break;
          
  }
 */
 /*
  uint8_t red {200};
  uint8_t green {200};
  uint8_t blue {200};
  uint8_t alpha {255};
  double angle{0};
  int frame = 0;
  SDL_RendererFlip flip_state{SDL_FLIP_NONE};
  */
/*
 
 //When using surfaces instead of textures, we have to also get surface when intializing
 
 else
 {
 my_surface = SDL_GetWindowSurface(my_window);
 
 if (my_surface == nullptr)
 {
 printf("Error creating window surface. ERROR: %s\n", SDL_GetError());
 }
 */
/*
 Texture default_texture;
 Texture up_texture;
 Texture down_texture;
 Texture left_texture;
 Texture right_texture;
 Texture dots_sprite;
 Texture smiles_sprite;
 Texture stick_figure_backflips_sprite;
 Texture arrow_sprite; //for some reason I have drawn the arrow and the first backflip animation in this png file.
 
 if (!default_texture.load_from_file("Images/press.bmp"))
 {
     success = false;
     printf("Failed to load default image\n");
 }
 
 if (!up_texture.load_from_file("Images/up.bmp"))
 {
     success = false;
     printf("Failed to load up image\n");
 }
 
 if (!down_texture.load_from_file("Images/down.bmp"))
 {
     success = false;
     printf("Failed to load down image\n");
 }
 
 if (!left_texture.load_from_file("Images/left.bmp"))
 {
     success = false;
     printf("Failed to load left image\n");
 }
 
 if (!right_texture.load_from_file("Images/right.bmp"))
 {
     success = false;
     printf("Failed to load right image\n");
 }
 
 if (!dots_sprite.load_from_file("Images/dots.png"))
 {
     success = false;
     printf("Failed to load dots image\n");
 }
     
 if (!arrow_sprite.load_from_file("Images/arrow.png"))
 {
     success = false;
     printf("Failed to load dots image\n");
 }
 if (!smiles_sprite.load_from_file("Images/smiles.png"))

 {
     success = false;
     printf("Failed to load dots image\n");
 }
 if (!stick_figure_backflips_sprite.load_from_file("Images/stick_figure_backflip2.png"))
 {
     success = false;
     printf("Failed to load stick figure backflip image\n");
 }
 
default_texture.free();
up_texture.free();
down_texture.free();
left_texture.free();
right_texture.free();
dots_sprite.free();
smiles_sprite.free();
arrow_sprite.free();
 
 SDL_Rect g_dot_clips[4];
 SDL_Rect g_smiles_clips[4];
 SDL_Rect g_stick_figure_clips[3];
 SDL_Rect g_arrow_clip = {15, 15, 26, 54};
 SDL_Rect g_stick_figure_backflip_clips[4];

 g_dot_clips[0] = {0, 0, 100, 100};
 g_dot_clips[1] = {100, 0, 100, 100};
 g_dot_clips[2] = {0, 100, 100, 100};
 g_dot_clips[3] = {100, 100, 100, 100};
 dots_sprite.set_blend_mode();

 g_smiles_clips[0] = {40, 90, 65, 65};
 g_smiles_clips[1] = {30, 160, 80, 80};
 g_smiles_clips[2] = {20, 250, 105, 75};
 g_smiles_clips[3] = {10, 350, 150, 100};

 g_stick_figure_clips[0] = {54, 21, 14, 33};
 g_stick_figure_clips[1] = {67, 18, 13, 31};
 g_stick_figure_clips[2] = {78, 19, 22, 26};

 g_arrow_clip = {15, 15, 26, 54};

 g_stick_figure_backflip_clips[0] = {113, 184, 100, 175};
 g_stick_figure_backflip_clips[1] = {213, 184, 100, 175};
 g_stick_figure_backflip_clips[2] = {313, 184, 100, 175};
 g_stick_figure_backflip_clips[3] = {413, 184, 100, 175};
 */

//auto end = std::chrono::high_resolution_clock::now();
//std::chrono::duration<float> duration = end - start;
// if (duration.count() > 1) std::cout << "Wait time is " << duration.count() << " seconds\n";
/*
 #pragma once

 //variables all caps because they store constants

 enum KeyboardEvents
 {
     DEFAULT_SURFACE,
     PRESS_KEYBOARD_UP,
     PRESS_KEYBOARD_DOWN,
     PRESS_KEYBOARD_LEFT,
     PRESS_KEYBOARD_RIGHT,
     PRESS_KEYBOARD_TOTAL
     
 };

 enum FileTypes
 {
     TYPE_PNG,
     TYPE_BMP,
     TYPE_JPG
     
 };
 */
