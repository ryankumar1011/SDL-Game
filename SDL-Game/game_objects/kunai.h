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
    static constexpr int WIDTH = 31;
    static constexpr int HEIGHT = 15;
    
public:
    Kunai();
    static Texture& get_texture();
    ObjectName get_name() override;
    int get_width() override;
    void handle_event(SDL_Event& event) override;
    void update_position() override;
    void update_colliders() override;
    void render() override;
    ~Kunai() override;
    
    //for testing
    void scale_colliders();
    void render_scaled();

private:
    static Texture m_texture;
};

