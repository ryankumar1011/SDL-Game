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

void Object::change_var(float& var, float amount, float cap)
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

//This function uses seperate axis theorem to check for a collision. This can be easily done by SDL function SDL_HasIntersection(), but this is just for practice.

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
            
            if ((m_bottom <= other_top) || (m_top >= other_bottom) || (m_right <= other_left) || (m_left >= other_right))
            {
                //if they are seperated along x and y axis
                continue;
            }
            
            //if they are not seperated along x and y axis
            
            SDL_FPoint& other_penetration = other->get_penetration();
            SDL_FPoint& other_normal = other->get_normal();
            
            SDL_FPoint m_center = {(m_left + m_right)/2, (m_top + m_bottom)/2};
            SDL_FPoint other_center = {(other_left + other_right)/2, (other_top + other_bottom)/2};
            
            m_normal.x = other_center.x - m_center.x;
            m_normal.y = other_center.y - m_center.y;
            
            float magnitude = sqrt(m_normal.x*m_normal.x + m_normal.y*m_normal.y);
            
            m_normal.x = m_normal.x/magnitude;
            m_normal.y = m_normal.y/magnitude;
            
            other_normal.x = -m_normal.x;
            other_normal.y = -m_normal.y;
            
            float overlap_left;
            float overlap_right;
            float overlap_top;
            float overlap_bottom;
            
            overlap_left = std::max(m_left, other_left);
            overlap_top = std::max(m_top, other_top);
            overlap_right = std::min(m_right, other_right);
            overlap_bottom = std::min(m_bottom, other_bottom);
            
            if (((overlap_right == m_right) && (overlap_left == m_left) && (overlap_top == m_top) && (overlap_bottom == m_bottom)) || ((overlap_right == other_right) && (overlap_left == other_left) && (other_top == other_top) && (other_bottom == other_bottom)))
            {
                m_penetration.x = m_normal.x;
                m_penetration.y = m_normal.y;
            }
            
            if (((overlap_right == m_right) && (overlap_left == m_left)) || ((overlap_right == other_right) && (overlap_left == other_left)))
            {
                m_penetration.x = 0;
            }
            
            else if (((overlap_top == m_top) && (overlap_bottom == m_bottom)) || ((other_top == other_top) && (other_bottom == other_bottom)))
            {
                m_penetration.y = 0;
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
                
                if (overlap_bottom == m_bottom)
                {
                    m_penetration.y = overlap_bottom - overlap_top;
                }
                else
                {
                    m_penetration.y = overlap_top - overlap_bottom;
                }
                
                other_penetration.x = -m_penetration.x;
                other_penetration.y = -m_penetration.y;
            }
            return true;
        }
    }
    return false;
}

void Object::collide(Object* p_other)
{
    float linear_impulse;
    SDL_FPoint relative_velocity;
    SDL_FPoint& other_position = p_other->get_position();
    SDL_FPoint& other_velocity = p_other->get_velocity();
    float m1_inverse = 1.0/get_mass();
    float m2_inverse = 1.0/p_other->get_mass();
    
    relative_velocity.x = m_velocity.x - other_velocity.x;
    relative_velocity.y = m_velocity.y - other_velocity.y;
    
    std::cout << "Debug Info:" << std::endl;
    std::cout << "m_position: (" << m_position.x << ", " << m_position.y << ")" << std::endl;
    std::cout << "other_position: " << other_position.x << ", " << other_position.y << ")" << std::endl;
    std::cout << "m_velocity: (" << m_velocity.x << ", " << m_velocity.y << ")" << std::endl;
    std::cout << "other_velocity: " << other_velocity.x << ", " << other_velocity.y << ")" << std::endl;
    std::cout << "mass 1: " << 1/m1_inverse << std::endl;
    std::cout << "mass 2: " << 1/m2_inverse << std::endl;
    
    m_position.x -= m_penetration.x*0.55;
    m_position.y -= m_penetration.y*0.55;
    other_position.x += m_penetration.x*0.55;
    other_position.y += m_penetration.y*0.55;
    

    float dot_product = (relative_velocity.x*m_normal.x + relative_velocity.y*m_normal.y);
    
    linear_impulse = -2*dot_product*(1.0/(m1_inverse + m2_inverse));
        
    m_velocity.x += m1_inverse*linear_impulse*m_normal.x;
    m_velocity.y += m1_inverse*linear_impulse*m_normal.y;
        
    other_velocity.x -= m2_inverse*linear_impulse*m_normal.x;
    other_velocity.y -= m2_inverse*linear_impulse*m_normal.y;
    
    std::cout << "Normal: (" << m_normal.x << ", " << m_normal.y << ")" << std::endl;
    std::cout << "Penetration: (" << m_penetration.x << ", " << m_penetration.y << ")" << std::endl;
    std::cout << "Dot Product: " << dot_product << std::endl;
    std::cout << "Linear Impulse: " << linear_impulse << std::endl;
    std::cout << "new m_velocity: (" << m_velocity.x << ", " << m_velocity.y << ")" << std::endl;
    std::cout << "new other_velocity: " << other_velocity.x << ", " << other_velocity.y << ")" << std::endl;
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


void Object::flip_colliders(float width)
{
    for (auto& i : m_colliders)
    {
        //the x position of the left side will be changed, so m_collider[i].x is changed accordingly
        i.x = m_position.x + (width - (i.x - m_position.x));
        
        //since the collider's left x position becomes the right x position when horizontally flipped, we need to change m_collider[i].x to the new left position
        i.x = i.x - i.w;
    }
}

//This function is for testing. It is used to render the positions of the colliders.

void Object::render_colliders()
{
    SDL_SetRenderDrawColor(gp_renderer, 0x00, 0x00, 0x00, 0xFF);
    
    for (auto& i : m_colliders)
    {
        SDL_RenderDrawRectF(gp_renderer, &i);
    }
}

/*
 SDL_FPoint linear_impulse;
 SDL_FPoint relative_velocity;

 SDL_FPoint& other_position = p_other->get_position();
 SDL_FPoint& other_velocity = p_other->get_velocity();

 m_position.x -= m_penetration.x * 0.1;
 m_position.y -= m_penetration.y * 0.1;

 other_position.x += m_penetration.x * 0.1;
 other_position.y += m_penetration.y * 0.1;

 float m1_inverse = 1.0 / get_mass();
 float m2_inverse = 1.0 / p_other->get_mass();

 relative_velocity.x = m_velocity.x - other_velocity.x;
 relative_velocity.y = m_velocity.y - other_velocity.y;

 linear_impulse.x = relative_velocity.x * (1.0 / (m1_inverse + m2_inverse));
 linear_impulse.y = relative_velocity.y * (1.0 / (m1_inverse + m2_inverse));

 m_velocity.x -= linear_impulse.x / get_mass();
 m_velocity.y -= linear_impulse.y / get_mass();

 other_velocity.x += linear_impulse.x / p_other->get_mass();
 other_velocity.y += linear_impulse.y / p_other->get_mass();
 
 else if ((other_left > m_left) && (other_right < m_right) && (other_bottom < m_top) && (other_top > m_bottom))
 {
     if (other_left-m_left < other_right-m_right)
     {
         other_penetration.x = other_left-m_left;
     }
     else other_penetration.x = -(other_right-m_right);
     
     if (other_top-m_top < m_bottom-other_bottom)
     {
         other_penetration.y = other_top-m_top ;
     }
     else other_penetration.y = -(m_bottom-other_bottom);
 }
 */
/*
 if (((m_left > other_left) && (m_right < other_right) && (m_bottom < other_bottom) && (m_top > other_top)) || ((other_left > m_left) && (other_right < m_right) && (other_bottom < m_bottom) && (other_top > m_top)))
 {
     
     m_penetration.x =  (other_left + other_right)/2 - (m_left + m_right)/2;
     m_penetration.y = (other_top + other_bottom)/2 - (m_top + m_bottom)/2;
     
     float magnitude = sqrt(m_penetration.x*m_penetration.x + m_penetration.y*m_penetration.y);
     m_penetration.x /= magnitude;
     m_penetration.y /= magnitude;
     
     other_penetration.x = -m_penetration.x;
     other_penetration.y = -m_penetration.y;
     
     return true;
 }
 
 linear_impulse.x = (-2.0 * get_mass() * p_other->get_mass()) / (get_mass() + p_other->get_mass()) * dot_product;
 linear_impulse.y = (-2.0 * get_mass() * p_other->get_mass()) / (get_mass() + p_other->get_mass()) * dot_product;
 
 m_velocity.x = m_velocity.x + (linear_impulse.x / get_mass()) * m_penetration.x;
 m_velocity.y = m_velocity.y + (linear_impulse.y / get_mass()) * m_penetration.y;
 
 other_velocity.x = other_velocity.x - (linear_impulse.x / p_other->get_mass()) * m_penetration.x;
 other_velocity.y = other_velocity.y - (linear_impulse.y / p_other->get_mass()) * m_penetration.y;
 SDL_FPoint linear_impulse;
 
 SDL_FPoint relative_velocity;
 SDL_FPoint normalized_penetration;
 float penetration_norm;
 float penetration_magnitude;
 float impulse_magnitude;
     
 SDL_FPoint& other_position = p_other->get_position();
 SDL_FPoint& other_velocity = p_other->get_velocity();
 
 float m1_inverse = 1.0/get_mass();
 float m2_inverse = 1.0/p_other->get_mass();
 
 relative_velocity.x = m_velocity.x - other_velocity.x;
 relative_velocity.y = m_velocity.y - other_velocity.y;
  
 penetration_magnitude = relative_velocity.x*m_penetration.x + relative_velocity.y*m_penetration.y;
 impulse_magnitude = penetration_magnitude*(1.0 / (m1_inverse + m2_inverse));
 
 penetration_norm = sqrt(m_penetration.x*m_penetration.x + m_penetration.y*m_penetration.y);
 normalized_penetration.x = m_penetration.x/penetration_norm;
 normalized_penetration.y = m_penetration.y/penetration_norm;
 
 linear_impulse.x = impulse_magnitude*m_penetration.x;
 linear_impulse.y = impulse_magnitude*m_penetration.y;
 
 m_position.x -= m_penetration.x*1.01;
 m_position.y -= m_penetration.y*1.01;
     
 other_position.x += m_penetration.x*1.01;
 other_position.y += m_penetration.y*1.01;
 
 m_velocity.x = m_velocity.x + (linear_impulse.x / get_mass()) * m_penetration.x;
 m_velocity.y = m_velocity.y + (linear_impulse.y / get_mass()) * m_penetration.y;
 
 other_velocity.x = other_velocity.x - (linear_impulse.x / p_other->get_mass()) * m_penetration.x;
 other_velocity.y = other_velocity.y - (linear_impulse.y / p_other->get_mass()) * m_penetration.y;
    
std::cout << "m_position: (" << m_position.x << ", " << m_position.y << ")" << std::endl;
std::cout << "other_position: (" << other_position.x << ", " << other_position.y << ")" << std::endl;
std::cout << "relative_velocity: (" << relative_velocity.x << ", " << relative_velocity.y << ")" << std::endl;
std::cout << "linear_impulse: (" << linear_impulse.x << ", " << linear_impulse.y << ")" << std::endl;
std::cout << "normalized_penetration: (" << normalized_penetration.x << ", " << normalized_penetration.y << ")" << std::endl;

std::cout << "penetration_norm: " << penetration_norm << std::endl;
std::cout << "penetration_magnitude: " << penetration_magnitude << std::endl;
std::cout << "impulse_magnitude: " << impulse_magnitude << std::endl;

std::cout << "new m_velocity: (" << m_velocity.x << ", " << m_velocity.y << ")" << std::endl;
std::cout << "new other_velocity: (" << other_velocity.x << ", " << other_velocity.y << ")" << std::endl;
 
 m_penetration.x /= magnitude;
 m_penetration.y /= magnitude;
 
 
 
 if ((m_right > other_left) && (m_left < other_right))
 {
     m_penetration.x = m_right - other_left;
 }
 
 else if ((other_right > m_left) && (other_left < m_right))
 {
     m_penetration.x = -(other_right - m_left);
 }
 
 else m_penetration.x = 0;
 
 if ((m_bottom > other_top) && (m_top < other_bottom)) //m going down
 {
     m_penetration.y = m_bottom - other_top;
 }
 
 else if ((other_bottom > m_top) && (other_top < m_bottom))
 {
     m_penetration.y = -(other_bottom - m_top);
 }
 
 else m_penetration.y = 0;
 
 float magnitude = sqrt(m_penetration.x*m_penetration.x + m_penetration.y*m_penetration.y);
 m_penetration.x /= magnitude;
 m_penetration.y /= magnitude;
 
 
 if ((overlap_right == m_right) && (overlap_left == m_left) && (overlap_top == m_top) && (overlap_bottom == m_bottom))
 {
     if (m_right - other_left < other_right - m_left)
     {
         m_penetration.x = m_right - other_left;
     }
     
     else m_penetration.x = - (other_right - m_left);
     
     if (m_bottom - other_top < other_bottom - m_top)
     {
         m_penetration.y = m_bottom - other_top;
     }
     
     else m_penetration.y = - (other_bottom - m_top);
     
 }
 else if ((overlap_right == other_right) && (overlap_left == other_left) && (other_top == other_top) && (other_bottom == other_bottom))
 {
     if (other_right - m_left < m_right - other_left)
     {
         m_penetration.x = - (other_right - m_left);
     }
     
     else m_penetration.x = m_right - other_left;
     
     if (other_bottom - m_top < m_bottom - other_top)
     {
         m_penetration.y = -(other_bottom - m_top);
     }
     
     else m_penetration.y = m_bottom - other_top;
 }
 
 

 */
