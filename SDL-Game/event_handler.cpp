//
//  event_handler.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 13/3/24.
//

#include "event_handler.h"
#include "game_objects.h"
#include "game_buttons.h"
#include "music_handler.h"
#include "global_variables.h"
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2/SDL.h>

namespace EventHandler
{
bool handle_events(SDL_Event event)
{
    bool quit {false};
    
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
            
        {
            quit = true;
        }
        
        if (!g_menu_state && !g_controls_manual_state)
        {
            g_game_objects.handle_event(event);
        }
        
        g_game_buttons.handle_event(event);
        
        MusicHandler::handle_event(event);
        
    }
    return quit;
}
}
