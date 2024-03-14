//
//  renderer.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 13/3/24.
//

#include "renderer.h"
#include "texture.h"
#include "game_buttons.h"
#include "game_objects.h"
#include "global_variables.h"

namespace Renderer
{
    void render_all()
    {
        SDL_SetRenderDrawColor(gp_renderer, 0xE7, 0xFF, 0xCE, 0xFF);
        SDL_RenderClear(gp_renderer);
                
        if (g_menu_state)
        {
            g_menu.render();
        }
        
        else if (g_controls_manual_state)
            
        {
            g_controls_manual.render();
        }
        
        else
        {            
            g_game_objects.render();
        }
            
        g_game_buttons.render();
        
       // SDL_RenderPresent(gp_renderer);

    }
}
