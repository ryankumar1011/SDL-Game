//
//  shield.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 3/1/24.
//

#pragma once

#include "texture.h"
#include "object.h"

class Shield : public Object
{
public:
    Shield();
    static constexpr ObjectName NAME = SHIELD;
    static constexpr float MAX_SCALE_FACTOR = 1.2;
    
    static Texture& get_texture();
    ObjectName get_name() override;
    bool get_state();
    void set_state(bool state);
    void update_position(SDL_FPoint center);
    void resolve_collision(Object* p_other) override;
    void render() override;

private:
    static Texture m_texture;
    float m_scale_factor = 0;
    float m_width = 33*m_scale_factor;
    float m_height = 70*m_scale_factor;
    bool m_state = false;
    
    void update_colliders();
};
