//
//  Apple.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 2/1/24.
//

#pragma once
#include "object.h"
#include "texture.h"

class Apple : public Object
{
public:
    static constexpr ObjectName NAME = APPLE;
    static constexpr float MASS = 1;
    static constexpr float SCALE_FACTOR = 1.3;
    static constexpr float WIDTH = 15.0*SCALE_FACTOR;
    static constexpr float HEIGHT = 17.0*SCALE_FACTOR;
    static constexpr float MAX_VELOCITY_Y = 3;
    static constexpr float MAX_VELOCITY_X = 3;
    
    Apple();
    static Texture& get_texture();
    ObjectName get_name() override;
    float get_mass() override;
    void update_position() override;
    void resolve_collision(Object* p_other) override;
    void render() override;
    
private:
    static Texture m_texture;
    static SDL_Rect m_clip;
    double m_angle;
    double m_angle_velocity = 3;
    void update_colliders();
};

