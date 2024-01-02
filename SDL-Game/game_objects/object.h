//
//  Object.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 26/12/23.
//

#pragma once
#include <vector>
#include <SDL2/SDL.h>

enum ObjectName
{
    KUNAI,
    PLAYER,
    APPLE
};

class Object
{
public:
    bool delete_mark = false;

public:
    void set_position(float x, float y);
    void set_velocity(float x, float y);
    bool check_collision(Object* other);
    void render_colliders(); //for testing
    
    virtual ObjectName get_name() = 0;
    virtual void update_position() = 0;
    virtual void resolve_collision(Object* p_other) = 0;
    virtual void render() = 0;
    virtual ~Object() = default;

protected:
    static constexpr float GRAVITY_ACCELERATION = 0.3;
    static constexpr float FRICTION_MULTIPLIER = 0.03;
    static constexpr float AIR_RESISTANCE = 0.03;
    
    float m_position_x;
    float m_position_y;
    float m_velocity_x;
    float m_velocity_y;
    float m_acceleration_x;
    float m_acceleration_y;
    std::vector<SDL_FRect> m_colliders;
    SDL_RendererFlip m_flip_state;
    
    void change_var(float& var, float amount, float cap);
    std::vector<SDL_FRect>& get_colliders();
    void flip_colliders();
    void scale_colliders();
    void update_colliders_scaled();
    
    virtual float get_scale_factor();
    virtual int get_width() = 0; //this is needed for flip_colliders() to work for all base classes
    virtual void update_colliders() = 0;
};
