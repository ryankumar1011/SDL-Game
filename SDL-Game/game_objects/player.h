//
//  player.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 26/12/23.
//

#pragma once

#include "object.h"
#include "kunai.h"
#include "hearts.h"

class Player : public Object
{
    
public:
    static const ObjectName NAME = PLAYER;
    static constexpr float WIDTH = 89;
    static constexpr float HEIGHT = 132;
    static constexpr float MAX_VELOCITY_X = 10;
    static constexpr float MAX_VELOCITY_Y = 15;
    static constexpr float MAX_ACCELERATION_X = 0.35;
    static constexpr float JUMP_VELOCITY_Y = 11.5;
    
public:
    Player();
    void static set_clips();
    void create_kunai();
    void set_hearts(Hearts* p_hearts);
    bool pop_heart();
    

    ObjectName get_name() override;
    float get_height() override;
    float get_width() override;
    void handle_event(SDL_Event& event) override;
    void update_position() override;
    void update_colliders() override;
    void render() override;
    void delete_kunai(Kunai* p_kunai);
    ~Player() override;
    
private:
    int m_frame;
    static SDL_Rect m_player_clips[12];
    Hearts* mp_hearts;
    
};
