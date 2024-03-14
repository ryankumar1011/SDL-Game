//
//  Object.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 26/12/23.
//

#include "object.h"
#include "iostream"
#include "global_variables.h"

SDL_FPoint& Object::get_position()
{
    return m_position;
}

SDL_FPoint& Object::get_velocity()
{
    return m_velocity;
}

SDL_FPoint& Object::get_acceleration()
{
    return m_acceleration;
}

SDL_FPoint& Object::get_normal()
{
    return m_normal;
}

SDL_FPoint& Object::get_penetration()
{
    return m_penetration;
}

void Object::change_var_capped(float& var, float amount, float cap)
{
    float new_var{};
    
    if (amount > 0) cap = abs(cap);
    
    else cap = - abs(cap);
    
    new_var = var + amount;
    
    if ((cap >= 0 && new_var <= cap) || (cap < 0 && new_var >= cap))
    {
        var = new_var;
    }
    else
    {
        var = cap;
    }
}

std::vector<SDL_FRect>& Object::get_colliders()
{
    return m_colliders;
}

void Object::scale_colliders(float scale_factor)
{
    for (auto& i : m_colliders)
    {
        i.w *= scale_factor;
        i.h *= scale_factor;
    }
}

void Object::update_scaled_colliders(float scale_factor)
{
    for (auto& i : m_colliders)
    {
        i.x = m_position.x + (i.x - m_position.x)*scale_factor;
        i.y = m_position.y + (i.y - m_position.y)*scale_factor;
    }
}

//Function is called if m_flip_state is SDL_HORIZONTAL

void Object::flip_colliders(float object_width)
{
    for (auto& i : m_colliders)
    {
        //the x position of the left side will be changed, so m_collider[i].x is changed accordingly
        i.x = m_position.x + (object_width - (i.x - m_position.x));
        
        //since the collider's left x position becomes the right x position when horizontally flipped, we need to change m_collider[i].x to the new left position
        i.x = i.x - i.w;
    }
}

//Uses seperate axis theorem to check for a collision. Can be easily done by SDL function SDL_HasIntersection() instead, but this is just for practice.

bool Object::check_collision(Object* other)
{
    std::vector<SDL_FRect>& other_colliders = other->get_colliders();
    
    float m_left;
    float m_right;
    float m_top;
    float m_bottom;
    
    float other_left;
    float other_right;
    float other_top;
    float other_bottom;
    
    for (auto& i : m_colliders)
    {
        m_left = i.x;
        m_top = i.y;
        m_right = i.x + i.w;
        m_bottom = i.y + i.h;
        
        for (auto& j : other_colliders)
        {
            other_left = j.x;
            other_top = j.y;
            other_right = j.x + j.w;
            other_bottom = j.y + j.h;
            
            //the collision boxes will be in collision if they are not seperated in either x or y axis
            //in SDL x increases from left to right, and y increases from top to the bottom of the screen
            
            if ((m_bottom <= other_top) || (m_top >= other_bottom) || (m_right <= other_left) || (m_left >= other_right))
            {
                //if they are seperated along x and y axis
                continue;
            }
            
            //if they are not seperated along x and y axis
            
            calc_normal(other, m_left, m_right, m_top, m_bottom, other_left, other_right, other_top, other_bottom);
            
            calc_penetration(other, m_left, m_right, m_top, m_bottom, other_left, other_right, other_top, other_bottom);
           
            return true;
        }
    }
    return false;
}

void Object::calc_normal(Object* other, float m_left, float m_right, float m_top, float m_bottom, float other_left, float other_right, float other_top, float other_bottom)

{
    SDL_FPoint& other_normal = other->get_normal();
    
    SDL_FPoint m_center = {(m_left + m_right)/2, (m_top + m_bottom)/2};
    SDL_FPoint other_center = {(other_left + other_right)/2, (other_top + other_bottom)/2};
    
    //we take the normal vector to be from the center of one object to the other
    
    m_normal.x = other_center.x - m_center.x;
    m_normal.y = other_center.y - m_center.y;
    
    float magnitude = sqrt(m_normal.x*m_normal.x + m_normal.y*m_normal.y);
    
    //we normalize the normal vector using its magnitude
    
    m_normal.x = m_normal.x/magnitude;
    m_normal.y = m_normal.y/magnitude;
    
    //the normal vector will be equal and opposite for other object
    
    other_normal.x = -m_normal.x;
    other_normal.y = -m_normal.y;
}
void Object::calc_penetration(Object* other, float m_left, float m_right, float m_top, float m_bottom, float other_left, float other_right, float other_top, float other_bottom)
{
    SDL_FPoint& other_penetration = other->get_penetration();

    float overlap_left;
    float overlap_right;
    float overlap_top;
    float overlap_bottom;
    
    //positions of sides of overlapping rectangle formed during intersection
    overlap_left = std::max(m_left, other_left);
    overlap_top = std::max(m_top, other_top);
    overlap_right = std::min(m_right, other_right);
    overlap_bottom = std::min(m_bottom, other_bottom);
    
    //if m_rectangle is inside other_rectangle
    if ((overlap_right == m_right) && (overlap_left == m_left) && (overlap_top == m_top) && (overlap_bottom == m_bottom))
    {
        //we find the least amount needed to move out of other_rectangle (penetration vector)
        m_penetration.x = std::min(m_right - other_left, other_right - m_left);
        m_penetration.y = std::min(m_bottom - other_top, other_bottom - m_top);
    }
    
    //if other_rectangle is inside m_rectangle
    else if ((overlap_right == other_right) && (overlap_left == other_left) && (overlap_top == other_top) && (overlap_bottom == other_bottom))
    {
        //we find the least amount needed to move out of m_rectangle (penetration vector)
        m_penetration.x = std::min(other_right - m_left, m_right - other_left);
        m_penetration.y = std::min(other_bottom - m_top, m_bottom - other_top);
    }
    
    else
    {
        //since collision boxes are of different sizes, the smaller rectangle can be between the left and right end of the larger rectangle. we just set x penetration to 0 here
        if (((overlap_right == m_right) && (overlap_left == m_left)) || ((overlap_right == other_right) && (overlap_left == other_left)))
        {
            m_penetration.x = 0;
        }
        else
        {
            if (overlap_right == m_right)
            {
                m_penetration.x = overlap_right - overlap_left;
            }
            else
            {
                m_penetration.x = overlap_left - overlap_right;
            }
        }
        
        //since collision boxes are of different sizes, the smaller rectangle can be between the top and bottom end of the larger rectangle. we just set y penetration to 0 here
        if (((overlap_top == m_top) && (overlap_bottom == m_bottom)) || ((overlap_top == other_top) && (overlap_bottom == other_bottom)))
        {
            m_penetration.y = 0;
        }
        else
        {
            if (overlap_bottom == m_bottom)
            {
                m_penetration.y = overlap_bottom - overlap_top;
            }
            else
            {
                m_penetration.y = overlap_top - overlap_bottom;
            }
        }
    }
    
    other_penetration.x = -m_penetration.x;
    other_penetration.y = -m_penetration.y;
}

void Object::collide(Object* p_other)
{
    SDL_FPoint& other_position = p_other->get_position();
    SDL_FPoint& other_velocity = p_other->get_velocity();
    
    //debugging info
    std::cout << "m_position: (" << m_position.x << ", " << m_position.y << ")" << std::endl;
    std::cout << "other_position: " << other_position.x << ", " << other_position.y << ")" << std::endl;
    std::cout << "m_velocity: (" << m_velocity.x << ", " << m_velocity.y << ")" << std::endl;
    std::cout << "other_velocity: " << other_velocity.x << ", " << other_velocity.y << ")" << std::endl;
    
    //using inverse masses is easier for the used formulas
    float m1_inverse = 1.0/get_mass();
    float m2_inverse = 1.0/p_other->get_mass();
    
    SDL_FPoint relative_velocity;
    relative_velocity.x = m_velocity.x - other_velocity.x;
    relative_velocity.y = m_velocity.y - other_velocity.y;
    
    SDL_FPoint correction;
    
    //we correct the position before giving object velocity. The object is corrected by the penetration amount in the direction opposite to normal

    correction.x = -1.01*(m_penetration.x*m_normal.x + m_penetration.y*m_normal.y)*m_normal.x;
    correction.y = -1.01*(m_penetration.x*m_normal.x + m_penetration.y*m_normal.y)*m_normal.y;
    
    //for simplicity in game, only the lighter object will be moved

    if (m1_inverse > m2_inverse)
    {
        m_position.x += correction.x;
        m_position.y += correction.y;
    }
    else
    {
        other_position.x -= correction.x;
        other_position.y -= correction.y;
    }
    
    //how much of relative_velocity is along normal of collision
    
    float dot_product = (relative_velocity.x*m_normal.x + relative_velocity.y*m_normal.y);
    
    //calculating linear impulse using its formula. 2 over here represenets (1 + coeffecient of restitution). Coeff of resitution = 1 means collision is completely elastic and no energy is lost
    
    float linear_impulse = -2*dot_product*(1.0/(m1_inverse + m2_inverse));
        
    m_velocity.x += m1_inverse*linear_impulse*m_normal.x;
    m_velocity.y += m1_inverse*linear_impulse*m_normal.y;
        
    other_velocity.x -= m2_inverse*linear_impulse*m_normal.x;
    other_velocity.y -= m2_inverse*linear_impulse*m_normal.y;
    
    std::cout << "mass 1: " << 1/m1_inverse << std::endl;
    std::cout << "mass 2: " << 1/m2_inverse << std::endl;
    std::cout << "Normal: (" << m_normal.x << ", " << m_normal.y << ")" << std::endl;
    std::cout << "Penetration: (" << m_penetration.x << ", " << m_penetration.y << ")" << std::endl;
    std::cout << "correction: (" << correction.x << ", " << correction.y << ")" << std::endl;
    std::cout << "Dot Product: " << dot_product << std::endl;
    std::cout << "Linear Impulse: " << linear_impulse << std::endl;
    std::cout << "new m_velocity: (" << m_velocity.x << ", " << m_velocity.y << ")" << std::endl;
    std::cout << "new other_velocity: " << other_velocity.x << ", " << other_velocity.y << ")" << std::endl;
   
}

//To check position of colliders. To test add line p_object->render_colliders(); in GameObjects::render()

void Object::render_colliders()
{
    SDL_SetRenderDrawColor(gp_renderer, 0x00, 0x00, 0x00, 0xFF);
    
    for (auto& i : m_colliders)
    {
        SDL_RenderDrawRectF(gp_renderer, &i);
    }
}
