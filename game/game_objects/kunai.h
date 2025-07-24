//
//  weapons.h
//  SDL-Game
//
//  Created by Ryan Kumar on 5/11/23.
//

#pragma once

#include "texture.h"
#include "player.h"
#include "object.h"
#include <SDL2/SDL.h>

class Kunai : public Object
{
public:
    static constexpr ObjectName NAME = KUNAI;
    static constexpr float SCALE_FACTOR = 1;
    static constexpr float WIDTH = 31*SCALE_FACTOR;
    static constexpr float HEIGHT = 15*SCALE_FACTOR;
    
public:
    Kunai(Player& player);
    static Texture& get_texture();
    Player& get_player();
    
    ObjectName get_name() override;
    void update_position() override;
    void resolve_collision(Object* p_other) override;
    void render() override;
    ~Kunai() override;

private:
    static Texture m_texture;
    Player& m_player;
    void update_colliders();
};

