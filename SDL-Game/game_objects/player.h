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
    float GRAVITY_ACCELERATION = 0.3;
    
public:
    Player();
    void handle_event(SDL_Event& event) override;
    void update_position() override;
    void update_colliders() override;
    void render() override;
    
private:
    int m_frame;
    
};

