//
//  frame_rate.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 1/1/24.
//

#include "frame_rate.h"
#include "texture.h"
#include "global_variables.h"

FrameRate::FrameRate()
{
    m_text.set_alpha_mod(0xAA);
}

bool FrameRate::load_texture()
{
    return m_text.load_from_font(gp_arial_font, m_text_stream.str(), m_color);
    //str() here copies stringstream into a string object and returns that
    //load_from_font() will already free any texture mp_text points to when loading a new texture
}

void FrameRate::update(int frame_rate)
{
    m_text_stream.str(""); //.str() discards previous content of stream and places new as ""
    m_text_stream << "FR:" << frame_rate;
    
    load_texture();
}

void FrameRate::render()
{
    m_text.render(SCREEN_WIDTH-40, 5, nullptr);
}
FrameRate::~FrameRate()
{
    m_text.free();
}
