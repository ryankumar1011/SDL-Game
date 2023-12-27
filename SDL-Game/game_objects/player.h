//
//  player.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 26/12/23.
//

#pragma once

#include "object.h"

class Player : public Object
{
    
public:
    Player();
    void handle_event(SDL_Event& event) override;
    void update_position() override;
    void update_colliders() override;
    void render() override;
    
private:
    SDL_Rect* mp_current_clip;
    int m_frame;
    
};

