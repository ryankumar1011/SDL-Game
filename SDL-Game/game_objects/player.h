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
    static constexpr float WIDTH = 89;
    static constexpr float HEIGHT = 132;
    
public:
    Player();
    float get_height() override;
    float get_width() override;
    void handle_event(SDL_Event& event) override;
    void update_position() override;
    void update_colliders() override;
    void render() override;
    
private:
    int m_frame;
    
};

