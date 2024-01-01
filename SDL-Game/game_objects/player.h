//
//  player.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 26/12/23.
//

#pragma once

#include "texture.h"
#include "hearts.h"
#include "kunai.h"
#include "object.h"
#include <SDL2/SDL.h>

class Player : public Object
{
public:
    static const ObjectName NAME = PLAYER;
    static constexpr int WIDTH = 89;
    static constexpr int HEIGHT = 132;
    static constexpr float MAX_VELOCITY_X = 10;
    static constexpr float MAX_VELOCITY_Y = 15;
    static constexpr float MAX_ACCELERATION_X = 0.35; //Note: floats are required to be constexpr
    static constexpr float JUMP_VELOCITY_Y = 11.5;
    
public:
    Player();
    static Texture& get_texture();
    Hearts& get_hearts();
    static void set_clips();
    void create_kunai();
    
    ObjectName get_name() override;
    int get_width() override;
    void handle_event(SDL_Event& event) override;
    void update_position() override;
    void update_colliders() override;
    void render() override;
    ~Player() override;
private:
    int m_frame;
    Hearts m_hearts;
    static Texture m_sprite;
    static SDL_Rect m_clips[12];
};

