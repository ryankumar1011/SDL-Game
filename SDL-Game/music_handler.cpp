//
//  music_handler.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 13/3/24.
//

#include "music_handler.h"
#include "global_variables.h"

void MusicHandler::play_kunai_throw()
{
    Mix_PlayChannel(-1, gp_kunai_throw_sound, 0);
}
void MusicHandler::play_kunai_hit()
{
    Mix_PlayChannel(-1, gp_kunai_hit_sound, 0);
}
void MusicHandler::play_click()
{
    Mix_PlayChannel(-1, gp_click_sound, 0);
}
void MusicHandler::play_shield_hit()
{
    Mix_PlayChannel(-1, gp_shield_hit_sound, 0);
}

void MusicHandler::play_apple_hit()
{
    Mix_PlayChannel(-1, gp_apple_hit_sound, 0);
}

void MusicHandler::toggle_music()
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(gp_background_music, -1);
    }
    
    else if (Mix_PausedMusic() == 1)
    {
        Mix_ResumeMusic();
    }
    
    else Mix_PauseMusic();
}

void MusicHandler::handle_event(SDL_Event event)
{
    if (event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_p:
                toggle_music();
                break;
        }
    }
}



