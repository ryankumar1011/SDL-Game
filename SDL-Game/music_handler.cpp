//
//  music_handler.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 13/3/24.
//

#include "music_handler.h"

//play clickbutton

namespace MusicHandler
{
    void play_kunai()
    {
        Mix_PlayChannel(-1, gp_kunai_sound, 0);
    }

    void play_apple_hit()
    {
        Mix_PlayChannel(-1, gp_apple_hit_sound, 0);
    }

    void toggle_music()
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

    void handle_event(SDL_Event event)
    {
        if (event.type == SDL_KEYUP)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_p:
                    toggle_music();
                    break;
                    
                case SDLK_v:
                    Mix_PlayChannel(-1, gp_kunai_sound, 0);
                    break;
                    
                case SDLK_b:
                    Mix_PlayChannel(-1, gp_apple_hit_sound, 0);
                    break;
            }
        }
    }
}


