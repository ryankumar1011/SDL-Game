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
    static const ObjectName NAME = KUNAI;
    static constexpr float WIDTH = 31;
    static constexpr float HEIGHT = 15;
    
public:
    Kunai();
    ObjectName get_name() override;
    float get_height() override;
    float get_width() override;
    void handle_event(SDL_Event& event) override;
    void update_position() override;
    void update_colliders() override;
    void render() override;
    ~Kunai() override;
    
    //for testing
    void scale_colliders();
    void render_scaled();

};

