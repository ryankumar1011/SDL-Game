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
    static const ObjectName NAME = APPLE;
    static constexpr float SCALE_FACTOR = 1.3;
    static constexpr float WIDTH = 15*SCALE_FACTOR;
    static constexpr float HEIGHT = 17*SCALE_FACTOR;
    static constexpr float MAX_VELOCITY_Y = 3;
    
    Apple();
    static Texture& get_texture();
    ObjectName get_name() override;
    int get_width() override;
    float get_scale_factor() override;
    void update_position() override;
    void update_colliders() override;
    void resolve_collision(Object* p_other) override;
    void render() override;
    
private:
    double m_angle;
    SDL_FPoint m_center;
    static SDL_Rect m_clip;
    static Texture m_texture;
};
