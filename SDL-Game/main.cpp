//
//  main.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 22/10/23.
//

#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <string>



const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

//variables all caps because they store constants

enum KeyboardEvents : unsigned char
{
    DEFAULT_SURFACE,
    PRESS_KEYBOARD_UP,
    PRESS_KEYBOARD_DOWN,
    PRESS_KEYBOARD_LEFT,
    PRESS_KEYBOARD_RIGHT,
    PRESS_KEYBOARD_TOTAL
    
};

enum FileType : unsigned char
{
    TYPE_PNG,
    TYPE_BMP,
    TYPE_JPG
    
};

SDL_Window* my_window = nullptr; 

//SDL_Window and SDL_Surface are types defined by SDL

SDL_Surface* my_surface = nullptr;
SDL_Surface* current_surface_display = nullptr;

// Image that will load is alse of type SDL_Surface, its pointer also needs to be initialized to zero

SDL_Texture* current_texture_display = nullptr;
SDL_Renderer* my_renderer = nullptr;
SDL_Texture* key_press_surfaces[PRESS_KEYBOARD_TOTAL];


//Texture are efficient, driver-specific representation of pixel data. Textures are used during hardware rendering, and are stored in VRAM opposed to regular RAM, accelerating rendering operations using GPU. Meanwhile SDL_Surface is just a struct that contains pixel information.
// SDL_Renderer is a struct that handles ALL rendering and contains information about settings related to renderingijop-[-

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
           
           SDL_Event event;
           current_texture_display = key_press_surfaces[DEFAULT_SURFACE];
        
           while (quit != true)
           {
               while (SDL_WaitEvent(&event)) //event handler, feed memory address of event to PollEvent. Takes in pointer of an event
               {
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
                       
                   }
                   
                   SDL_RenderClear(my_renderer);
                   //clears target to set colour
                   SDL_RenderCopy(my_renderer, current_texture_display, &crop_rect, &stretch_rect);
                   //draws texture to hidden target (according to associated rendering settings and the crop and stretch set)
                   SDL_RenderPresent(my_renderer);
                   //draws content of hidden target onto window associated to renderer
                   //Note: there can't be more than one renderer
                
                   /*
                    When using surfaces instead of textures:
                    
                   SDL_BlitScaled (current_surface_display, &crop_rect, my_surface, &stretch_rect);
                   // or SDL_BlitSurface(current_surface_display, NULL, my_surface, NULL);
                  SDL_UpdateWindowSurface(my_window);
                    
                    */
               }
                
           }
       }
   }
    close();
    return 0;
}
