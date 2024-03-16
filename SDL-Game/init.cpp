//
//  Intialize.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 25/12/23.
//

#include "init.h"
#include "texture.h"
#include "player.h"
#include "kunai.h"
#include "apple.h"
#include "menu_button.h"
#include "controls_button.h"
#include "music_button.h"
#include "global_variables.h"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>

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
    if (!load_audio()) success = false;
    
    initialize_media();
    
    return success;
    
}

bool load_images()
{
    bool success = true;
    
    if (!Player::get_texture().load_from_file("Images/player_animations2.png"))
    {
        success = false;
        printf("Failed to load player animations sprite\n");
    }
    
    if (!Kunai::get_texture().load_from_file("Images/kunai.png"))
    {
        success = false;
        printf("Failed to load kunai image\n");
    }
    
    if (!Hearts::get_texture().load_from_file("Images/pixel_hearts.png"))
    {
        success = false;
        printf("Failed to load heart sprite\n");
    }
    if (!Apple::get_texture().load_from_file("Images/apple.png"))
    {
        success = false;
        printf("Failed to load apple image\n");
    }
    if (!Shield::get_texture().load_from_file("Images/shield.png"))
    {
        success = false;
        printf("Failed to load shield image\n");
    }
    if (!MenuButton::get_texture().load_from_file("Images/home_icon.png"))
    {
        success = false;
        printf("Failed to load home icon image\n");
    }
    
    if (!MusicButton::get_texture_on().load_from_file("Images/sound_on_icon.png"))
    {
        success = false;
        printf("Failed to load sound on image\n");
    }
    
    if (!MusicButton::get_texture_off().load_from_file("Images/sound_off_icon.png"))
    {
        success = false;
        printf("Failed to load sound off image\n");
    }
    
    if (!ControlsButton::get_texture().load_from_file("Images/controls_button.png"))
    {
        success = false;
        printf("Failed to load controls button image\n");
    }
    if (!g_controls_manual.load_from_file("Images/game_manual.png"))
    {
        success = false;
        printf("Failed to load controls menu \n");
    }
    if (!g_menu.load_from_file("Images/menu_in_progress.png"))
    {
        success = false;
        printf("Failed to load controls menu \n");
    }
    
    return success;
}

bool load_fonts()
{
    bool success = true;
    
    gp_arial_font = load_font_from_file("Fonts/arial.ttf", 13);
    
    if (gp_arial_font == nullptr)
    {
        success = false;
        printf("Failed to load arial font\n");
    }
    
    gp_crayon_font = load_font_from_file("Fonts/pastel_crayon.ttf", 17);
    
    if (gp_arial_font == nullptr)
    {
        success = false;
        printf("Failed to load crayon font\n");
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

bool load_audio()
{
    bool success = true;
    
    gp_background_music = Mix_LoadMUS("Audio/background_music.mp3");
   
    if (gp_background_music == nullptr)
    {
        success = false;
        printf("Failed to load background music\n");
    }
    
    gp_kunai_throw_sound = Mix_LoadWAV("Audio/kunai_throw.wav");
    
    if (gp_kunai_throw_sound == nullptr)
    {
        success = false;
        printf("Failed to load kunai throw audio\n");
    }
    gp_kunai_hit_sound = Mix_LoadWAV("Audio/kunai_hit.wav");
    
    if (gp_kunai_hit_sound == nullptr)
    {
        success = false;
        printf("Failed to load kunai hit audio\n");
    }
    
    gp_click_sound = Mix_LoadWAV("Audio/click.wav");
    
    if (gp_click_sound == nullptr)
    {
        success = false;
        printf("Failed to load click audio\n");
    }
    
    gp_shield_hit_sound = Mix_LoadWAV("Audio/shield_hit.wav");
        
    if (gp_shield_hit_sound == nullptr)
    {
        success = false;
        printf("Failed to load shield hit audio\n");
    }
    
    gp_apple_hit_sound = Mix_LoadWAV("Audio/apple_hit.wav");
    
    if (gp_apple_hit_sound == nullptr)
    {
        success = false;
        printf("Failed to load apple hit audio\n");
    }
    
    return success;
}

void initialize_media()
{
    set_texture_clips();
    //set_up_buttons();
    //set_texture_size();
}

void set_texture_clips()
{
    Player::set_clips();
}

void close()
{
    // Destroyed all LOADED surfaces and textures
    
    Kunai::get_texture().free();
    Player::get_texture().free();
    Hearts::get_texture().free();
    Apple::get_texture().free();
    Shield::get_texture().free();
    MenuButton::get_texture().free();
    MusicButton::get_texture_on().free();
    MusicButton::get_texture_off().free();
    ControlsButton::get_texture().free();
    g_controls_manual.free();
    g_menu.free();
    
    //we need to close a font that is opened from TTF_OpenFont
    TTF_CloseFont(gp_arial_font);
    TTF_CloseFont(gp_crayon_font);

    Mix_FreeMusic(gp_background_music);
    Mix_FreeChunk(gp_kunai_throw_sound);
    Mix_FreeChunk(gp_kunai_hit_sound);
    Mix_FreeChunk(gp_click_sound);
    Mix_FreeChunk(gp_shield_hit_sound);
    Mix_FreeChunk(gp_apple_hit_sound);
    
    // Destroy Windows and Renderer, set pointers to NULL
    SDL_DestroyWindow(gp_window);
    SDL_DestroyRenderer(gp_renderer);
    gp_window = nullptr;
    gp_renderer = nullptr;
    
    //Just like you initialize them, you have to quit SDL subsystems
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
