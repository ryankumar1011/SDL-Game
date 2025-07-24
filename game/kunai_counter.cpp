//
//  kunai_counter.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 3/1/24.
//

#include "kunai_counter.h"
#include "kunai.h"
#include "global_variables.h"

Texture KunaiCounter::m_trans_kunai = Kunai::get_texture();

KunaiCounter::KunaiCounter()
{
    m_count = 0;
    m_color = {0x00, 0x00, 0x00};
    update_count();
}

void KunaiCounter::set_position(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
}
void KunaiCounter::set_count(int count)
{
    m_count = count;
    update_count();
}

bool KunaiCounter::decrease_count(int amount)
{
    m_count -= amount;
    
    if (m_count < 0)
    {
        m_count = 0;
        return false;
    }
    
    update_count();
    
    return true;
}

void KunaiCounter::increase_count(int amount)
{
    m_count += amount;
    
    update_count();
}


void KunaiCounter::update_count()
{
    m_text_stream.str("");
    
    m_text_stream << "x" << m_count;
   
    m_text.load_from_font(gp_crayon_font, m_text_stream.str(), m_color);
      
}

void KunaiCounter::render()
{
    if (m_count <= 0)
    {
        Kunai::get_texture().set_alpha_mod(0xAA);
        Kunai::get_texture().render(m_position.x, m_position.y, nullptr, SCALE_FACTOR);
        Kunai::get_texture().set_alpha_mod(0xFF);
    }
    else Kunai::get_texture().render(m_position.x, m_position.y, nullptr, SCALE_FACTOR);
    
    m_text.render(m_position.x + 32, m_position.y - 1.5, nullptr);

}

KunaiCounter::~KunaiCounter()
{
    m_text.free();
}
