//
//  Intialize.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 25/12/23.
//

#include "init.h"
#include "texture.h"
#include "mouse_button.h"
#include "global_variables.h"

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
    
    if (!player_sprite.load_from_file("Player_animations/player_animations2.png"))
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
    
    gp_arial_font = load_font_from_file("Fonts/Arial.ttf", 13);
    
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
    
    g_player_clips[0] = {19, 18, 108-19, 150-18};
    g_player_clips[1] = {120, 19, 193-120, 150-19};
    g_player_clips[2] = {216, 20, 283-216, 150-20};
    g_player_clips[3] = {317, 22, 377-317, 151-22};
    g_player_clips[4] = {405, 21, 459-405, 153-21};
    g_player_clips[5] = {488, 22, 533-488, 151-22};
    
    g_player_clips[6] = {94, 167, 147-94, 298-167};
    g_player_clips[7] = {176, 166, 238-176, 296-166};
    g_player_clips[8] = {263, 167, 339-263, 297-167};
    g_player_clips[9] = {345, 167, 426-345, 297-167};
    g_player_clips[10] = {435, 168, 531-435, 298-168};
    g_player_clips[11] = {26, 303, 129-26, 434-303};
    
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
    player_sprite.free();
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
