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
#include "timers.h"
#include "weapons.h"


static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;
static const int SCREEN_DIAGONAL = sqrt((SCREEN_WIDTH*SCREEN_WIDTH) + (SCREEN_HEIGHT*SCREEN_HEIGHT));

SDL_Window* gp_window = nullptr;
SDL_Renderer* gp_renderer = nullptr;

//Texture are efficient, driver-specific representation of pixel data. Textures are used during hardware rendering, and are stored in VRAM opposed to regular RAM, accelerating rendering operations using GPU. Meanwhile SDL_Surface is just a struct that contains pixel information.

//SDL_Renderer is a struct that handles ALL rendering and contains information about settings related to rendering


//Clips
SDL_Rect g_button_clips [4];
SDL_Rect g_player_animation_clips[12];

//Fonts
TTF_Font* gp_arial_font = nullptr;

//Chunks and music from SDL mixer
Mix_Music* gp_background_music = nullptr;
Mix_Chunk* gp_shuriken_sound = nullptr;
Mix_Chunk* gp_apple_hit_sound = nullptr;

//Instantiating objects:
//Note - suffixes _sprite and _text are used to indicate textures of sprites and textures of texts respectively

Texture* p_current_texture;
Texture button_sprite;
Texture button_text;
Texture frame_rate_text;
Texture animation_sprite;
Texture kunai_texture;

MouseButton g_buttons[4];

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
    m_texture_path = file_path;

    //We first load surface, and then create texture from surface pixels
    //If we use surfaces, we would then convert them to display format using: optimized_surface = SDL_ConvertSurface(loaded_surface, my_surface->format, 0);
    //However, this is not necessary here
    //We still need the file path using this method since we nead to load the surface into memory first
    
    p_loaded_surface = IMG_Load(m_texture_path.c_str());
    
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
               printf("Error loading texture with path %s, ERROR: %s\n",m_texture_path.c_str(), SDL_GetError());
               
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
 m_font_color = font_color;

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
void Texture::set_height(int height)
{
   m_height = height;
}

void Texture::set_width(int width)
{
   m_width = width;
    
}

void Texture::set_font_color(const uint8_t &red, const uint8_t &green, const uint8_t &blue)
{
    m_font_color = {red, green, blue};
}

void Texture::set_color_key(const uint8_t &red, const uint8_t &green, const uint8_t &blue)
{
    m_color_key = SDL_MapRGB(mp_format, red, green, blue);
    
}

std::string Texture::get_path()
{
    return m_texture_path;
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

//Below is the mainly used render function. It can render a texture, a clip of a sprite/texture and the flipped texture/clip. Using max_dim, it can also render clips of a sprite so that they are all centered within a certain width (this is usefull for animations)

void Texture::render_texture(int x, int y, SDL_Rect* p_clip, int max_dim, SDL_RendererFlip flip_state)

{
    int max_width {max_dim};
    int max_height {max_dim};
    SDL_Rect render_area{};

    if (p_clip == nullptr)
    {
        render_area = {x, y, m_width, m_height};
        SDL_RenderCopyEx(gp_renderer, mp_texture, p_clip, &render_area, 0, nullptr, flip_state);
        
    }
    
    else if ((max_dim == 0) || (max_width < p_clip->w) || (max_height < p_clip->h))
    {
        render_area = {x, y, p_clip->w, p_clip->h};
        SDL_RenderCopyEx(gp_renderer, mp_texture, p_clip, &render_area, 0, nullptr, flip_state);
    }
    
    else
    {
        render_area = {x + (max_width - (p_clip->w))/2, y + (max_height - (p_clip->h))/2, p_clip->w, p_clip->h};
        SDL_RenderCopyEx(gp_renderer, mp_texture, p_clip, &render_area, 0, nullptr, flip_state);
    }
    
    return;
}

//The below render function is used when the rotated texture/clip needs to be rendered. Centering is not implemented for this yet

void Texture::render_texture(int x, int y, SDL_Rect* p_clip, double angle, SDL_Point* center, SDL_RendererFlip flip_state)
{
    SDL_Rect render_area{};

    if (p_clip != nullptr)
    {
        render_area = {x, y, m_width, m_height};
        SDL_RenderCopyEx(gp_renderer, mp_texture, p_clip, &render_area, angle, center, flip_state);    }
    else
    {
        render_area = {x, y, p_clip->w, p_clip->h};
        SDL_RenderCopyEx(gp_renderer, mp_texture, p_clip, &render_area, angle, center, flip_state); 
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


MouseButton::MouseButton()
{
    m_position = {0,0};
    
    m_width = 0;
    m_height = 0;
    
    m_current_clip = MOUSE_CLIP_OUT;
    
}

//Changes m_current_clip (with type of an enum MouseClipState) depending on the type of mouse event returned during SDL_PollEvent()
void MouseButton::handle_mouse_event (SDL_Event& event)
{
    if ((event.type == SDL_MOUSEBUTTONDOWN) || (event.type == SDL_MOUSEBUTTONUP) || (event.type == SDL_MOUSEMOTION) || (event.type == SDL_MOUSEWHEEL))
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
            
            switch (event.type)
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

//Some mouse states may not change the clip to display. They may instead change the color of the button or have other effects.
void MouseButton::handle_extra_states()

{
    mp_button_sprite->set_color_mod(0xFF, 0xFF, 0xFF);
    
    if (m_current_clip == MOUSE_CLIP_MOVE_OVER)
    {
        mp_button_sprite->set_color_mod(0x00, 0x60, 0x00);
        m_current_clip = MOUSE_CLIP_OVER;
    }
    if (m_current_clip == MOUSE_CLIP_SCROLL_OVER)
    {
        mp_button_sprite->set_color_mod(0x00, 0x60, 0x00);
        m_current_clip = MOUSE_CLIP_OVER;
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

void MouseButton::set_button_sprite(Texture* p_button_sprite)
{
    mp_button_sprite = p_button_sprite;
}

int MouseButton::get_current_clip()
{
    return m_current_clip;
}

void MouseButton::render_button()
{
    handle_extra_states();
    mp_button_sprite->render_texture(m_position.x, m_position.y, &g_button_clips[m_current_clip]);
}

SDLTimer::SDLTimer()
{
    m_start_ticks = 0;
    m_paused_ticks = 0;
    m_is_started = false;
    m_is_paused = false;
    
}
void SDLTimer::start()
{
    m_is_started = true;
    m_is_paused = false;
    
    m_start_ticks = SDL_GetTicks64();
    m_paused_ticks = 0;
    
}

void SDLTimer::pause()

{
    if (m_is_started && !(m_is_paused))
    {
        m_is_paused = true;
        m_paused_ticks = SDL_GetTicks64() - m_start_ticks; //the current time on clock
        m_start_ticks = 0;
    }
}

void SDLTimer::unpause()

{
    if (m_is_started && m_is_paused)
    {
        m_is_paused = false;
        m_start_ticks = SDL_GetTicks64() - m_paused_ticks;
        //since the amount that start ticks is behind SDL_GetTicks is the time on the clock, we just update start ticks to unpause the clock
        m_paused_ticks = 0;
        
    }
    
}
void SDLTimer::stop()
{
    m_is_started = false;
    m_is_paused = false;
    
    m_start_ticks = 0;
    m_paused_ticks = 0;
    
}

bool SDLTimer::is_paused()
{
    return m_is_paused;
}

bool SDLTimer::is_started()
{
    return m_is_started;
}

uint64_t SDLTimer::get_time()
{
    if (is_started())
    {
        if (is_paused()) return m_paused_ticks;
        else return SDL_GetTicks64() - m_start_ticks;
    }
    
    return 0;
}

SDLTimer::~SDLTimer()
{
    m_start_ticks = 0;
    m_paused_ticks = 0;
    m_is_started = false;
    m_is_paused = false;
    
}

Kunai::Kunai()
{
    m_position_x = 0;
    m_position_y = 0;
    m_velocity_x = 2;
    m_velocity_y = 0;
    
}

void Kunai::handle_event(SDL_Event& event)
{
    
}
void Kunai::set_position(int x, int y)
{
    m_position_x = x;
    m_position_y = y;
}

void Kunai::update_position()
{
    m_position_x += m_velocity_x;
    m_position_y += m_velocity_y;
    if (((m_position_x + kunai_texture.get_width()) > SCREEN_WIDTH) || (m_position_x < 0))
    {
        m_position_x -= m_velocity_x;
        m_velocity_x = -m_velocity_x;
        (m_flip_state == SDL_FLIP_NONE) ? m_flip_state = SDL_FLIP_HORIZONTAL : m_flip_state = SDL_FLIP_NONE;
    }
    
}

void Kunai::render()
{
    kunai_texture.render_texture(m_position_x, m_position_y, nullptr, 0, m_flip_state);
}

bool init()
{
    
    bool success{true};
    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        
    {
        success = false;
        printf("Error initializing SDL. ERROR: %s\n", SDL_GetError());
    }
    
    else
        
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            
        {
            printf("Warning: linear texture filtering not enabled\n");
        }
        
        if (Mix_Init(MIX_INIT_FLAC|MIX_INIT_MP3) != (MIX_INIT_FLAC|MIX_INIT_MP3))
        {
            success = false;
            printf("Error initializing SDL Mixer. ERROR: %s\n", Mix_GetError());
        }
        
        else
        {
            
            if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
                
            {
                printf("Error initializing SDL_Image. ERROR: %s\n", IMG_GetError());
                success = false;
            }
            
            else
            {
                
                if (TTF_Init() == -1)
                {
                    printf("Error initializing TTF. ERROR: %s\n", TTF_GetError());
                    success = false;
                }
                
                else
                {
                    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                    {
                        printf("Error initializing SDL_Mixer. ERROR: %s\n", Mix_GetError());
                        success = false;
                        
                    }
                    
                    else
                    {
                        SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &gp_window, &gp_renderer);
                        
                        if (gp_window == nullptr || gp_renderer == nullptr)
                        {
                            printf("Error initializing window and renderer. ERROR: %s\n", SDL_GetError());
                            success = false;
                            
                        }
                        
                        else SDL_SetRenderDrawColor(gp_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
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
    
    if (!load_images()) success = false;
    if (!load_fonts()) success = false;
    if (!load_texts()) success = false;
    if (!load_audio()) success = false;
    
    initialize_media();
    
    return success;
    
}

bool load_images()
{
    bool success = true;
    
    if (!button_sprite.load_from_file("Images/buttons.png"))
    {
        success = false;
        printf("Failed to load buttons image\n");
    }
    if (!animation_sprite.load_from_file("Player_animations/player_animations2.png"))
    {
        success = false;
        printf("Failed to load player animations sprite\n");
    }
    if (!kunai_texture.load_from_file("Weapons/kunai.png"))
    {
        success = false;
        printf("Failed to load kunai image\n");
    }
    
    return success;
}

bool load_fonts()
{
    bool success = true;
    
    gp_arial_font = load_font_from_file("Fonts/Arial.ttf", 20);
    
    if (gp_arial_font == nullptr) 
    {
        success = false;
    }
    
    return success;

}

TTF_Font* load_font_from_file(const std::string& font_path, int font_size)
{
    
    TTF_Font* p_font;
    
    p_font = (TTF_OpenFont(font_path.c_str(), font_size));
    
    if (p_font == nullptr)
    {
        printf("Failed to load font from TTF file with font path %s\n", font_path.c_str());
        
    }
    
    return p_font;
    
}

bool load_texts()
{
    bool success = true;
    
    SDL_Color text_color = {0x50, 0x00, 0x00};
    
    if (!button_text.load_from_font(gp_arial_font, "Move over buttons to change color!", text_color))
    {
        success = false;
    }
    
    return success;
    
}

bool load_audio()
{
    bool success = true;
    
    gp_background_music = Mix_LoadMUS("Audio/background_music.mp3");
   
    if (gp_background_music == nullptr)
    {
        success = false;
        printf("Failed to load background music\n");
    }
    
    gp_shuriken_sound = Mix_LoadWAV("Audio/shuriken2.wav");
    
    if (gp_shuriken_sound == nullptr)
    {
        success = false;
        printf("Failed to load shuriken audio\n");
    }
    gp_apple_hit_sound = Mix_LoadWAV("Audio/apple_hit2.wav");
    
    if (gp_apple_hit_sound == nullptr)
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
    set_texture_size();
}

void set_up_buttons()
{
    for (int i = 0; i < 4; i++)
    {
       g_buttons[i].set_button_sprite(&button_sprite);
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
    
    g_player_animation_clips[0] = {19, 18, 108-19, 150-18};
    g_player_animation_clips[1] = {120, 19, 193-120, 150-19};
    g_player_animation_clips[2] = {216, 20, 283-216, 150-20};
    g_player_animation_clips[3] = {317, 22, 377-317, 151-22};
    g_player_animation_clips[4] = {405, 21, 459-405, 153-21};
    g_player_animation_clips[5] = {488, 22, 533-488, 151-22};
    
    g_player_animation_clips[6] = {94, 167, 147-94, 298-167};
    g_player_animation_clips[7] = {176, 166, 238-176, 296-166};
    g_player_animation_clips[8] = {263, 167, 339-263, 297-167};
    g_player_animation_clips[9] = {345, 167, 426-345, 297-167};
    g_player_animation_clips[10] = {435, 168, 531-435, 298-168};
    g_player_animation_clips[11] = {26, 303, 129-26, 434-303};
    
}

void set_texture_size()
{
    kunai_texture.set_width(30);
    kunai_texture.set_height(15);
    
}

void close()
{
    // Destroyed all LOADED surfaces and textures
    
    button_sprite.free();
    animation_sprite.free();   
    frame_rate_text.free();
    kunai_texture.free();
     
    TTF_CloseFont(gp_arial_font); //we need to close a font that is opened from TTF_OpenFont

    Mix_FreeMusic(gp_background_music);
    Mix_FreeChunk(gp_shuriken_sound);
    Mix_FreeChunk(gp_apple_hit_sound);
    
    // Destroy Windows and Renderer, set pointers to NULL
    SDL_DestroyWindow(gp_window);
    //Takes care of destroying my_screen_surface/my_current_texture
    SDL_DestroyRenderer(gp_renderer);
    gp_window = nullptr;
    gp_renderer = nullptr;
    
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
           Kunai starting_kunai;
           starting_kunai.set_position(10,10);
           SDL_Rect* current_clip = nullptr;
           
           int frame{0};
           int frame_rate {};

           double previous_time{};
           double change_in_time{};
           const int CAPPED_FRAME_RATE {60};
           const int MINIMUM_LOOP_TICKS {1000/CAPPED_FRAME_RATE};
           //loop ticks are in milliseconds. 1 seconds is 1000 ms so 1000/frame_rate is time in ms for each frame
           
           std::stringstream time_to_print;
           SDLTimer game_timer;
           game_timer.start();
           SDLTimer cap_timer;

           bool quit = false;
           SDL_Event event;
        
           while (quit != true)
              
          {
              cap_timer.start();
              
              //Events
              
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
        
                              if (Mix_PlayingMusic() == 0)
                              {
                                  Mix_PlayMusic(gp_background_music, -1);
                              }
                              
                              else if (Mix_PausedMusic() == 1)
                              {
                                  Mix_ResumeMusic();
                              }
                        
                              else Mix_PauseMusic();
                              
                              break;
                              
                          case SDLK_d:
                              Mix_PlayChannel(-1, gp_shuriken_sound, 0);
                              break;
                              
                          case SDLK_f:
                              Mix_PlayChannel(-1, gp_apple_hit_sound, 0);
                              break;
                              
                          case SDLK_r:
                              if (game_timer.is_started()) game_timer.stop();
                              game_timer.start();
                              break;
                              
                          case SDLK_p:
                              if (game_timer.is_paused()) game_timer.unpause();
                              else game_timer.pause();
                              break;
                              
                      }
                      
                  }
                    
                  for (int i = 0; i < 4; i++)
                      
                      {
                          g_buttons[i].handle_mouse_event(event);
                      }
    
              }
              
              //Logic
              
              //the variable frame is incremented from 0 and ends at 55 every loop. Some actions like loading text are only done at a specific frame to improve performance
              
              starting_kunai.update_position();

              time_to_print.str(""); //.str() discards previous content of stream and places new as ""
              time_to_print << "The current frame rate is " << frame_rate;
              
              if (frame == 0)
              {
                  frame_rate_text.load_from_font(gp_arial_font, time_to_print.str(), {0x00, 0x00, 0x00});
                  //str() here copies stringstream into a string object and returns that
              }
                            
              //Rendering
              
              SDL_SetRenderDrawColor(gp_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
              SDL_RenderClear(gp_renderer);
                            
              current_clip = &g_player_animation_clips[frame/5];
              animation_sprite.render_texture(100, 300, current_clip, 200);
              animation_sprite.render_texture(300, 300, current_clip, 200, SDL_FLIP_HORIZONTAL);
              
              frame_rate_text.render_texture(160, 270, nullptr);
              
              starting_kunai.render();
              
              SDL_RenderPresent(gp_renderer);
              
              frame ++;
              
              if (frame > 55) 
              {
                  frame = 0;
              }
              
              //waiting to keep a specific frame rate (for performance)
              
              change_in_time = (game_timer.get_time()/1000.0f) - previous_time;
              previous_time = (game_timer.get_time()/1000.0f);
              frame_rate = 1.0/change_in_time;
              if (frame_rate > 100000) frame_rate = 0;
              
              if (cap_timer.get_time() < MINIMUM_LOOP_TICKS)
              {
                  SDL_Delay((MINIMUM_LOOP_TICKS - cap_timer.get_time()));
              }
              
           }
       }
   }
    
    close();
    return 0;
}

// Ommited code written during practice, can be used later:

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
/*
for (int i = 0; i < 4; i++)
        
  {
      g_buttons[i].render_button();
            
  }
 */
/*
text_texture.render_texture((SCREEN_WIDTH - ptr_current_texture->get_width())/2, (SCREEN_HEIGHT - ptr_current_texture->get_height())/2);

time_to_print.str(""); //.str() discards previous content of stream and places new as ""

time_to_print << "The time is " << (SDL_GetTicks64() - time_after_last_reset);

text_time_texture.load_texture_from_font(g_ptr_arial_font, time_to_print.str(), {0x00, 0x00, 0x00});
//.str() here converts copies stringstream into a string object and returns that

text_time_texture.render_texture(240, 270);
*/
/*
 if (frame_rate > 30)
 {
     time_to_wait = (1000.0/30.0) - (change_in_time*1000.0f);
     SDL_Delay(time_to_wait);
 }
 
 void Texture::render_texture(int x, int y, SDL_Rect* p_clip)
 {
     SDL_Rect render_area{};
     
     if (p_clip != nullptr)
     {
         render_area = {x, y, m_width, m_height};
         SDL_RenderCopy(gp_renderer, mp_texture, p_clip, &render_area);
     }
     else
     {
         render_area = {x, y, p_clip->w, p_clip->h};
         SDL_RenderCopy(gp_renderer, mp_texture, p_clip, &render_area);
     }
     
 }
 gp_window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
 
 
 if (gp_window == nullptr)
     
 {
     success = false;
     printf("Error creating window. ERROR: %s\n", SDL_GetError());
 }

         else
         {
             
             gp_renderer = SDL_CreateRenderer(gp_window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
             //SDL_RENDERER_PRESENTVSYNC
             if (gp_renderer == nullptr)
                 
             {
                 success = false;
                 printf("Error initializing renderer. ERROR: %s\n", SDL_GetError());
                 
             }
             
             SDL_SetRenderDrawColor(gp_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
         }
 
 if (frame == 0)
 {
     frame_rate_text.load_from_font(gp_arial_font, time_to_print.str(), {0x00, 0x00, 0x00});
     //str() here copies stringstream into a string object and returns that
 }
 
  */
