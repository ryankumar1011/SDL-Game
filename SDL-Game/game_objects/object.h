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
    static constexpr float GRAVITY_ACCELERATION = 0.3;
    static constexpr float FRICTION_MULTIPLIER = 0.03;
    static constexpr float AIR_RESISTANCE = 0.03;
    
    //remove_mark: remove from game_objects vector
    //destroy_mark: remove from game_objects vector AND deallocate using delete
    
    bool destroy_mark = false;
    bool remove_mark = false;

public:
    virtual ObjectName get_name() = 0;
    SDL_FPoint& get_position();
    SDL_FPoint& get_velocity();
    SDL_FPoint& get_acceleration();
    inline virtual void handle_event(SDL_Event& event) {}
    inline virtual void update_position() {}
    bool check_collision(Object* other);
    inline virtual void resolve_collision(Object* p_other) {};
    inline virtual void render() {};
    void render_colliders(); //for testing
    virtual ~Object() = default;

protected:
    SDL_FPoint m_position;
    SDL_FPoint m_velocity;
    SDL_FPoint m_acceleration;
    SDL_FPoint m_normal;
    SDL_FPoint m_penetration;
    std::vector<SDL_FRect> m_colliders;
    SDL_RendererFlip m_flip_state;
    
    inline virtual float get_mass() {return 999999;} //Objects with greater mass won't moved in this game, so this is a fitting default
    SDL_FPoint& get_normal();
    SDL_FPoint& get_penetration();
    std::vector<SDL_FRect>& get_colliders();
    
    //Calc for resolving collisions
    void calc_normal(Object* other, float m_left, float m_right, float m_top, float m_bottom, float other_left, float other_right, float other_top, float other_bottom);
    void calc_penetration(Object* other, float m_left, float m_right, float m_top, float m_bottom, float other_left, float other_right, float other_top, float other_bottom);
    
    //For changing velocity/acceleration/other var by amount with a cap.
    //Variable will be limited between -cap and cap
    void change_var_capped(float& var, float amount, float cap);
    
    void flip_colliders(float object_width);
    void scale_colliders(float scale_factor); //sets scaled width & height
    void update_scaled_colliders(float scale_factor); //sets correct position for scaled collider
    void collide(Object* p_other);
    
    //When object initialized:
    //->width and height of m_colliders set
    //->scale_colliders(SCALE_FACTOR) called
    //->update_colliders called
    
    //When update_colliders() called:
    //->collider position updated according to object position
    //->update_scaled_colliders(scale_factor) called
    //->depending on m_flip_state, flip_colliders() is called

    //update_colliders() called again every time object position is updated
    
};
