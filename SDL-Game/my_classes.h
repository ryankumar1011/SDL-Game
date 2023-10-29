//
//  Texture_class.h
//  SDL-Game
//
//  Created by Ryan Kumar on 26/10/23.
//

#ifndef texture_class
#define texture_class

#include <string>
#include <chrono>

class Texture;
class Timer;

class Texture
{

private:
  SDL_Texture* m_texture;
  int m_height;
  int m_width;
  std::string m_texture_path;
    
public:

Texture();

Texture(const std::string& texture_path);
    
bool load_from_file();
    
void set_color_mod(uint8_t& red, uint8_t& green, uint8_t& blue);

void set_alpha_mod(uint8_t& alpha);

void set_blend_mode(SDL_BlendMode blendmode = SDL_BLENDMODE_BLEND);
    
void render_texture(int x = 0, int y = 0, SDL_Rect* render_area = nullptr);
    
void free();
    
~Texture();
    
int get_height();
        
int get_width();
    
std::string get_path();
    
};

struct Timer
{
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;
    int timer_number;

    Timer(int number)
    {
        start = std::chrono::high_resolution_clock::now();
        timer_number = number;
    
    }
    
    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << "Time for timer number" << timer_number << " is " << duration.count()*1000000000 << "ns\n";
        
    }
    
};


#endif
