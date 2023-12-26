//
//  weapons.h
//  SDL-Game
//
//  Created by Ryan Kumar on 5/11/23.
//

#pragma once

#include "object.h"
#include "sdl_libraries.h"
#include <vector>


class Kunai : public Object
{
    
public:
    Kunai();
    void handle_event(SDL_Event& event) override;
    void update_position() override;
    void update_colliders() override;
    void render() override;
    
    //for testing
    void scale_colliders();
    void render_scaled();

};

