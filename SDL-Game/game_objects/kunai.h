//
//  weapons.h
//  SDL-Game
//
//  Created by Ryan Kumar on 5/11/23.
//

#pragma once

#include "texture.h"
#include "object.h"
#include <SDL2/SDL.h>

class Kunai : public Object
{
public:
    static const ObjectName NAME = KUNAI;
    static constexpr float SCALE_FACTOR = 1.2;
    static constexpr float WIDTH = 31*SCALE_FACTOR;
    static constexpr float HEIGHT = 15*SCALE_FACTOR;
    
public:
    Kunai();
    static Texture& get_texture();
    
    ObjectName get_name() override;
    int get_width() override;
    float get_scale_factor() override;
    void update_position() override;
    void update_colliders() override;
    void resolve_collision(Object* p_other) override;
    void render() override;
    ~Kunai() override;

private:
    static Texture m_texture;
};

