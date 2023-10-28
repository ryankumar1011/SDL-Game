//
//  Texture_class.h
//  SDL-Game
//
//  Created by Ryan Kumar on 26/10/23.
//

#ifndef texture_class
#define texture_class

#include <string>

class Texture;

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
    
void render_texture(int x = 0, int y = 0, SDL_Rect* render_area = nullptr);
    
void free();
    
~Texture();
    
int get_height();
        
int get_width();
    
std::string get_path();
    

};


#endif
