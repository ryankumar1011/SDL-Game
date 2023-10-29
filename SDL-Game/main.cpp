//
//  main.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 22/10/23.
//

//libraries:
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <string>

//header files:
#include "texture_class.h"
#include "my_enums.h"

static const int SCREEN_WIDTH = 600;
static const int SCREEN_HEIGHT = 600;
static const int SCREEN_DIAGONAL = sqrt((SCREEN_WIDTH*SCREEN_WIDTH) + (SCREEN_HEIGHT*SCREEN_HEIGHT));

SDL_Window* my_window = nullptr;

//SDL_Window and SDL_Surface are types defined by SDL

SDL_Surface* my_surface = nullptr;
SDL_Surface* current_surface_display = nullptr;

// Image that will load is alse of type SDL_Surface, its pointer also needs to be initialized to zero

SDL_Texture* current_texture_display = nullptr;
SDL_Renderer* my_renderer = nullptr;
//SDL_Texture* key_press_surfaces[PRESS_KEYBOARD_TOTAL];

SDL_Rect dot_clips[4];



//Texture are efficient, driver-specific representation of pixel data. Textures are used during hardware rendering, and are stored in VRAM opposed to regular RAM, accelerating rendering operations using GPU. Meanwhile SDL_Surface is just a struct that contains pixel information.
// SDL_Renderer is a struct that handles ALL rendering and contains information about settings related to rendering

//Instantiating objects:

Texture* current_texture;
Texture default_texture("press.bmp");
Texture up_texture("up.bmp");
Texture down_texture("down.bmp");
Texture left_texture("left.bmp");
Texture right_texture("right.bmp");
Texture dots_texture("dots.png");


Texture::Texture(const std::string& texture_path)
    {
        m_height = 0;
        m_width = 0;
        m_texture = nullptr;
        m_texture_path = texture_path;
    
    }

bool Texture::load_from_file()
{
        SDL_Texture* loaded_texture = nullptr;
        SDL_Surface* loaded_surface = nullptr;
        
        // We first load surface, and then create texture from surface pixels (instead of converting it into display format, which we do with optimized_surface and SDL_ConvertSurface)
        // We still need the file path using this method since we nead to load the surface into memory first
        loaded_surface = IMG_Load(m_texture_path.c_str());
    
        if (loaded_surface == NULL)
            {
                printf("Error loading surface with path %s. ERROR: %s\n. ERROR: %s\n", m_texture_path.c_str(), SDL_GetError(), IMG_GetError());
  
            }
    
       else
       {
           
           SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0xFF, 0xFF, 0xFF));
           //MapRGB generates pixel colour to be made transperent, which is in the format of the used surface
           
           loaded_texture = SDL_CreateTextureFromSurface(my_renderer, loaded_surface);
           
           if (loaded_texture == NULL)
               
           {
               printf("Error loading texture with path %s, ERROR: %s\n",m_texture_path.c_str(), SDL_GetError());
               
           }
           else
            {
               
               m_width = loaded_surface->w;
               m_height = loaded_surface->h;
               
            }
    
            SDL_FreeSurface(loaded_surface);
           
        }
    
    m_texture = loaded_texture;

    return (loaded_texture != nullptr);
                
}

int Texture::get_height()
{
    return m_height;
}

int Texture::get_width()
{
  return m_width;
    
}
std::string Texture::get_path()
{
    return m_texture_path;
}

void Texture::set_color_mod(uint8_t& red, uint8_t& green, uint8_t& blue)
{
    SDL_SetTextureColorMod(m_texture, red, green, blue);
    
}

void Texture::render_texture(int x, int y, SDL_Rect* crop_image)
{
    
    if (crop_image == nullptr)
        
    {
        
        SDL_RenderCopy(my_renderer, m_texture, NULL, NULL);
        
        //printf("Error pointer crop_image for texture with path %s is null", get_path().c_str());
    }
    else
    {
        SDL_Rect render_area = {x, y, crop_image->w, crop_image->h};
        
        SDL_RenderCopy(my_renderer, m_texture, crop_image, &render_area);
        //Third parameter is portion of texture to crop
        //Fourth parameter is portion of target to copy into
    }
}

void Texture::free()
{
    m_texture = nullptr;
    SDL_DestroyTexture(m_texture);
    m_width = 0;
    m_height = 0;
    
}

Texture::~Texture()
{
    free();
    
}

bool init()
{
    
    bool success{true}; //flag for function (init) is set at start
    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        
        //can also only initialize video sub system, use SDL_INIT_EVERYTHING/SDL_INIT_VIDEO
    {
        success = false;
        printf("Error initializing everything. ERROR: %s\n", SDL_GetError());
    }
    else
    {
        my_window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        
        //my_window already created when pointer was initiliazed as NULL
        
        if (my_window == NULL)
        {
            success = false;
            printf("Error creating window. ERROR: %s\n", SDL_GetError());
            success = false;
            
        }
        /*
         
         //When using surfaces instead of textures, we have to also get surface when intializing
         
        else
        {
            my_surface = SDL_GetWindowSurface(my_window);
            
            if (my_surface == NULL)
            {
                printf("Error creating window surface. ERROR: %s\n", SDL_GetError());
            }
         */
            
            else
            {
               my_renderer = SDL_CreateRenderer(my_window, -1, SDL_RENDERER_ACCELERATED);
                
                if (my_renderer == NULL)
                {
                    success = false;
                    printf("Error initializing renderer. ERROR: %s\n", SDL_GetError());
                    
                }
                else
                {
                    SDL_SetRenderDrawColor(my_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    int sdl_image_flags = IMG_INIT_PNG;
                    // can use | (or bitwise operator) for multiple flags
                    // !(IMG_Init(sdl_image_flags) & sdl_image_flags) is only used to check is Init for PNG failed
                    if (!(IMG_Init(sdl_image_flags) == sdl_image_flags))
                    {
                        printf("Error initializing SDL_Image. ERROR: %s\n", IMG_GetError());
                        success = false;
                    }
                }
            }
        }
    
    return success;
}

//We can load a texture withouth creating a surface and using SDL_CreateTextureFromSurface through the following:

bool load_media()
{
    
    bool success = true;
    
    if (!default_texture.load_from_file())
    {
        success = false;
        printf("Failed to load default image");
    }
    
    if (!up_texture.load_from_file())
    {
        success = false;
        printf("Failed to load up image");
    }
    
    if (!down_texture.load_from_file())
    {
        success = false;
        printf("Failed to load down image");
    }
    
    if (!left_texture.load_from_file())
    {
        success = false;
        printf("Failed to load left image");
    }
    
    if (!right_texture.load_from_file())
    {
        success = false;
        printf("Failed to load right image");
    }
    
    if (!dots_texture.load_from_file())
    {
        success = false;
        printf("Failed to load dots image");
    }
      
    dot_clips[0] = {0, 0, 100, 100};
    dot_clips[1] = {100, 0, 100, 100};
    dot_clips[2] = {0, 100, 100, 100};
    dot_clips[3] = {100, 100, 100, 100};
    
    return success;
    
}

void close()
{
    // Destroyed all LOADED surfaces and textures
    default_texture.free();
    up_texture.free();
    down_texture.free();
    left_texture.free();
    right_texture.free();
    
    // Destroy Windows and Renderer, set pointers to NULL
    SDL_DestroyWindow(my_window);
    //Takes care of destroying my_screen_surface/my_current_texture
    SDL_DestroyRenderer(my_renderer);
    my_window = NULL;
    my_renderer = NULL;
    
    //Just like you initialize them, you have to quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char* args[])
{
   if (!init())
   {
       printf("Error initializing. ERROR: %s\n", SDL_GetError());
   }
   else
   {
       
       if (!load_media())
       {
           printf("Error loading media. ERROR: %s\n", SDL_GetError());
       }
       else
       {
           
           bool quit = false; //Main loop flag
           SDL_Event event;
           current_texture = &default_texture;
           uint8_t red {255};
           uint8_t green {255};
           uint8_t blue {255};
           
          while (quit != true)
              
          {
              SDL_SetRenderDrawColor(my_renderer, 0x2F, 0xFF, 0xFF, 0xFF);
              SDL_RenderClear(my_renderer);
              dots_texture.set_color_mod(red, green, blue);
              dots_texture.render_texture(0, 0, &dot_clips[0]);
              dots_texture.render_texture(SCREEN_WIDTH -100, 0, &dot_clips[1]);
              dots_texture.render_texture(0, SCREEN_HEIGHT - 100, &dot_clips[2]);
              dots_texture.render_texture(SCREEN_WIDTH -100, SCREEN_HEIGHT - 100, &dot_clips[3]);
              current_texture->render_texture();
              //we use a pointer to object to fix issue with texture display. It is not possible to point to a class itself since they are not created at runtime - the objects are.
              
               SDL_RenderPresent(my_renderer);
              
               SDL_WaitEvent(&event);
                   
               if (event.type == SDL_QUIT)
                       
                   {
                       quit = true;
                   } 
                   
                
                switch(event.key.keysym.sym) // key symbol, accessing other unions in union?
                           
                       {
                           case SDLK_UP:
                               current_texture = &up_texture;
                               break;
                               
                           case SDLK_DOWN:
                               current_texture = &down_texture;
                               break;
                               
                           case SDLK_LEFT:
                               current_texture = &left_texture;
                               break;
                               
                           case SDLK_RIGHT:
                               current_texture = &right_texture;
                               break;
                               
                           case SDLK_r:
                               red += 25;
                               break;
                               
                           case SDLK_g:
                               green += 25;
                               break;
                               
                           case SDLK_b:
                               blue += 25;
                               break;
                        }
               
           }
       }
   }
    
    close();
    return 0;
}

// Emmited code for practice, can be used later:

/*
SDL_Surface* load_surface(std::string path, FileType file_type)
{
    SDL_Surface* loaded_surface = nullptr;
    SDL_Surface* optimized_surface = nullptr;
    
    switch (file_type)
    {
        case TYPE_BMP:
            loaded_surface = SDL_LoadBMP(path.c_str());
            //.c_str() converts string to array with \0 (c-style string)
            break;
            
        case TYPE_PNG:
            loaded_surface = IMG_Load(path.c_str());
            break;
            
        default:
            printf("Error loading surface with path %s.\n Type is invalid", path.c_str());
            return nullptr;
            
    }
    
    if (loaded_surface == NULL)
    {
        printf("Error loading surface with path %s. ERROR: %s\n. ERROR: %s\n", path.c_str(), SDL_GetError(), IMG_GetError());
        // takes const char* as parameter type
    }
    else
        {
            optimized_surface = SDL_ConvertSurface(loaded_surface, my_surface->format, 0);
            // -> helps to access format in struct my_surface easily, since my_surface is a pointer and not actually an object (allocated on heap)
            // sometimes we only have a pointer to a class or struct (maybe allocated on heap), to access members we use -> instead of dereferencing pointer
            // so it would be same asame as (*my_surface).format
            if (optimized_surface == NULL)
            {
                printf("Error optimizing surface with path %s. ERROR: %s\n. ERROR: %s\n", path.c_str(), SDL_GetError(), IMG_GetError());
            }
      
            
        SDL_FreeSurface(loaded_surface);
        }
    
 return optimized_surface;

}
*/

/*
SDL_Texture* load_texture(const std::string& path, unsigned char file_type)

{
    
    SDL_Texture* loaded_texture = nullptr;
    SDL_Surface* loaded_surface = nullptr;
    
    // We first load surface, and then create texture from surface pixels (instead of converting it into display format, which we do with optimized_surface and SDL_ConvertSurface)
    // We still need the file path using this method since we nead to load the surface into memory first
    switch (file_type)
    {
        case TYPE_BMP:
            loaded_surface = SDL_LoadBMP(path.c_str());
            //.c_str() converts string to array with \0 (c-style string)
            // we use it whenever we want a const char* from an std::string type
            break;
            
        case TYPE_PNG:
            loaded_surface = IMG_Load(path.c_str());
            break;
    }
    if (loaded_surface == NULL)
    {
        printf("Error loading surface with path %s. ERROR: %s\n. ERROR: %s\n", path.c_str(), SDL_GetError(), IMG_GetError());
        // takes const char* as parameter type
    }
    else
    {
        loaded_texture = SDL_CreateTextureFromSurface(my_renderer, loaded_surface);
        if (loaded_texture == NULL)
        {
            printf("Error loading texture with path %s, ERROR: %s\n",path.c_str(), SDL_GetError());
            
        }
        SDL_FreeSurface(loaded_surface);
   }
    
    return loaded_texture;

}
*/
/*
 SDL_Rect crop_rect; // rectangle to be copied
 // x and y start from top left corner, goes to the right and downwards as x and y increase
 crop_rect.x = 40; // starting x and y
 crop_rect.y = 50;
 crop_rect.h = 400;
 crop_rect.w = 500;

 SDL_Rect stretch_rect; // rectangle that surface is copied into
 stretch_rect.x = 0;
 stretch_rect.y = 0;
 stretch_rect.h = SCREEN_HEIGHT;
 stretch_rect.w = SCREEN_WIDTH;
 
 */
/*
 bool load_media() //can be used for textures or surfaces
 {
     bool success = true;
     key_press_surfaces[DEFAULT_SURFACE] = load_IMG_texture("loaded.png");
     // remember that string literals are of type const char* not just char*
     if (key_press_surfaces[DEFAULT_SURFACE] == NULL)
     {
         printf("Failed to load default image");
         success = false;
     }
     key_press_surfaces[PRESS_KEYBOARD_UP] = load_IMG_texture("up.bmp");
     if (key_press_surfaces[PRESS_KEYBOARD_UP] == NULL)
     {
         printf("Failed to load up image");
         success = false;
     }
     
     key_press_surfaces[PRESS_KEYBOARD_DOWN] = load_IMG_texture("down.bmp");
     if ( key_press_surfaces[PRESS_KEYBOARD_DOWN] == NULL)
     {
         printf("Failed to load down image");
         success = false;
     }
     key_press_surfaces[PRESS_KEYBOARD_LEFT] = load_IMG_texture("left.bmp");
     if (key_press_surfaces[PRESS_KEYBOARD_LEFT] == NULL)
     {
         printf("Failed to load left image");
         success = false;
     }
     key_press_surfaces[PRESS_KEYBOARD_RIGHT] = load_IMG_texture("right.bmp");
     if (key_press_surfaces[PRESS_KEYBOARD_RIGHT] == NULL)
     {
         printf("Failed to load right image");
         success = false;
     }
     
     return success;
 }
 */
/*
 void close()
 {
     // Destroyed all LOADED surfaces and textures
     
     for (int i = 0; i < PRESS_KEYBOARD_TOTAL; i++)
     {
         SDL_DestroyTexture(key_press_surfaces[i]);
         key_press_surfaces[i] = NULL;
     }
     
     // Destroy Windows and Renderer, set pointers to NULL
     
     SDL_DestroyWindow(my_window);
     //Takes care of destroying my_screen_surface/my_current_texture
     SDL_DestroyRenderer(my_renderer);
     my_window = NULL;
     my_renderer = NULL;
     
     //Just like you initialize them, you have to quit SDL subsystems
     
     IMG_Quit();
     SDL_Quit();
 }
 */
/*
 if (event.type == SDL_QUIT) //what is the type compared?
 {
 quit = true;
 }
 else if (event.type == SDL_KEYDOWN)
 {
 switch(event.key.keysym.sym) // key symbol, accessing other unions in union?
 {
 case SDLK_UP:
 current_texture_display = key_press_surfaces[PRESS_KEYBOARD_UP];
 break;
 
 case SDLK_DOWN:
 current_texture_display = key_press_surfaces[PRESS_KEYBOARD_DOWN];
 break;
 
 case SDLK_LEFT:
 current_texture_display = key_press_surfaces[PRESS_KEYBOARD_LEFT];
 break;
 
 case SDLK_RIGHT:
 current_texture_display = key_press_surfaces[PRESS_KEYBOARD_RIGHT];
 break;
 
 }
 */
/*
When using surfaces instead of textures:

SDL_BlitScaled (current_surface_display, &crop_rect, my_surface, &stretch_rect);
// or SDL_BlitSurface(current_surface_display, NULL, my_surface, NULL);
SDL_UpdateWindowSurface(my_window);

*/
/*
 SDL_Texture* load_IMG_texture(const std::string& path)
 {
     SDL_Texture* loaded_texture = nullptr;
     
     loaded_texture = IMG_LoadTexture(my_renderer, path.c_str());
     // function requires a const char pointer
     // no file type required, only rendered and path of file
     if (loaded_texture == NULL)
     {
         printf("Error loading texture with path %s, ERROR: %s\n", path.c_str(), IMG_GetError());
         
     }
     
     return loaded_texture;
 }
 */
/*
SDL_RenderCopy(my_renderer, current_texture_display,NULL, NULL);
//primative rendering allows for drawing basic shapes withouth loading textures. So you don't need RenderCopy to draw texture on target

SDL_SetRenderDrawColor(my_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
SDL_RenderClear(my_renderer);

//clears target to set colour (fills target with the colour set)
//Errors in colouting occur withouth initializing background colour to this

SDL_Rect top_left_viewport = {0,0,SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
SDL_Rect top_right_viewport = {SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};


SDL_RenderSetViewport(my_renderer, &top_left_viewport);
SDL_RenderCopy(my_renderer, current_texture_display, NULL, NULL);
SDL_RenderSetViewport(my_renderer, &top_right_viewport);
SDL_RenderCopy(my_renderer, current_texture_display, NULL, NULL);

SDL_Rect bottom_viewport = {0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2};
//unspecified members will be initialized as zero
//can also use designated initiliazers. It is same as:
//SDL_Rect bottom_viewport = {.y = SCREEN_WIDTH/2, .h = SCREEN_HEIGHT/2, .w = SCREEN_WIDTH};

SDL_RenderSetViewport(my_renderer, &bottom_viewport);

SDL_SetRenderDrawColor(my_renderer, 0xFF, 0x00, 0x00, 0xFF);
SDL_Rect rectangle_filled = {(SCREEN_WIDTH/2) - 100, (SCREEN_HEIGHT/2) - 100, 200, 200};
// can initialize a struct my listing and initializing its variables

SDL_RenderFillRect(my_renderer, &rectangle_filled);
// takes in a rectangle shape and fills it on the current rendering target

SDL_SetRenderDrawColor(my_renderer, 0x00, 0xFF, 0xFF, 0xFF);
SDL_Rect rectangle_drawed = {(SCREEN_WIDTH/2) - 50, (SCREEN_HEIGHT/2) - 50, 100, 100};
SDL_RenderDrawRect(my_renderer, &rectangle_drawed);

SDL_SetRenderDrawColor(my_renderer, 0x00, 0x20, 0x00, 0xFF);
SDL_RenderDrawLine(my_renderer, 0, SCREEN_HEIGHT, SCREEN_WIDTH, 0);

SDL_SetRenderDrawColor(my_renderer, 0x00, 0x00, 0xF0, 0xFF);
for (int i = 0; i < SCREEN_DIAGONAL; i += 2)
{
    SDL_RenderDrawPoint(my_renderer, i, i);
}

//What is SDL_SetRenderTarget?
//SDL_RenderGetViewport?
 

// SDL_RenderCopy(my_renderer, current_texture_display, &crop_rect, &stretch_rect);
//draws texture to hidden target (according to associated rendering settings and the crop and stretch set)
SDL_RenderPresent(my_renderer);
//draws content of hidden target onto window associated to renderer
//Note: there can't be more than one renderer

*/
/*
 if(event.type != SDL_KEYUP) default_texture.render_texture();
 
 else
 {
     switch(event.key.keysym.sym) // key symbol, accessing other unions in union?
         
     {
         case SDLK_UP:
             up_texture.render_texture();
             break;
             
         case SDLK_DOWN:
             down_texture.render_texture();
             break;
             
         case SDLK_LEFT:
             left_texture.render_texture();
             break;
             
         case SDLK_RIGHT:
             right_texture.render_texture();
             break;
     }
 }
 */
