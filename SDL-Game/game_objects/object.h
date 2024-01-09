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
    APPLE,
    SHIELD
};

class Object
{
public:
    bool delete_mark = false;
    bool remove_mark = false;

public:
    virtual ObjectName get_name() = 0;
    SDL_FPoint& get_position();
    SDL_FPoint& get_velocity();
    SDL_FPoint& get_acceleration();
    inline virtual void handle_event(SDL_Event& event) {}
    inline virtual void update_position() {}
    virtual void resolve_collision(Object* p_other) = 0;
    virtual void render() = 0;
    virtual ~Object() = default;
    
    bool check_collision(Object* other);
    void render_colliders(); //for testing


protected:
    static constexpr float GRAVITY_ACCELERATION = 0.3;
    static constexpr float FRICTION_MULTIPLIER = 0.03;
    static constexpr float AIR_RESISTANCE = 0.03;
    
    SDL_FPoint m_position;
    SDL_FPoint m_velocity;
    SDL_FPoint m_acceleration;
    SDL_FPoint m_normal;
    SDL_FPoint m_penetration;
    std::vector<SDL_FRect> m_colliders;
    SDL_RendererFlip m_flip_state;
    
    inline virtual float get_mass() {return 0;}
    SDL_FPoint& get_normal();
    SDL_FPoint& get_penetration();
    std::vector<SDL_FRect>& get_colliders();
    void change_var(float& var, float amount, float cap);
    void flip_colliders(float width);
    void scale_colliders(float scale_factor);
    void update_scaled_colliders(float scale_factor);
    void collide(Object* p_other);
};
