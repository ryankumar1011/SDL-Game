//
//  player.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 26/12/23.
//

#pragma once

#include "texture.h"
#include "hearts.h"
#include "kunai_counter.h"
#include "shield.h"
#include "object.h"
#include <SDL2/SDL.h>

class Player : public Object
{
public:
    static constexpr ObjectName NAME = PLAYER;
    static constexpr float MASS = 60;
    static constexpr float SCALE_FACTOR = 1;
    static constexpr float WIDTH = 89*SCALE_FACTOR;
    static constexpr float HEIGHT = 132*SCALE_FACTOR;
    static constexpr float MAX_VELOCITY_X = 10;
    static constexpr float MAX_VELOCITY_Y = 15;
    static constexpr float MAX_ACCELERATION_X = 0.35; //Note: static floats are required to be constexpr
    static constexpr float JUMP_VELOCITY_Y = 11.5;
    
public:
    Player(int type);
    static Texture& get_texture();
    float get_mass() override;
    static void set_clips();
    Hearts& get_hearts();
    KunaiCounter& get_kunai_counter();
    void create_kunai();
    
    ObjectName get_name() override;
    void handle_event(SDL_Event& event) override;
    void update_position() override;
    void resolve_collision(Object* p_other) override;
    void render() override;
    ~Player() override;
    
private:
    static Texture m_sprite;
    static SDL_Rect m_clips[12];
    int m_type;
    int m_frame;
    Hearts m_hearts;
    KunaiCounter m_kunai_counter;
    Shield m_shield;
    
    void update_colliders();
};

