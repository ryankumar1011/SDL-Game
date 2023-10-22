//
//  main.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 22/10/23.
//

#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>



const int SCREEN_WIDTH = 600; //variables all caps because stores constant
const int SCREEN_HEIGHT = 600;

SDL_Window* my_window = NULL; //SDL_Window and SDL_Surface are types defined by SDL
SDL_Surface* my_surface = NULL; //use pointers
SDL_Surface* image_hello_world = NULL; // Image that will load is alse of type SDL_Surface, its pointer also needs to be initialized to zero
SDL_Surface* current_surface_display = NULL;
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


SDL_Surface* key_press_surfaces[PRESS_KEYBOARD_TOTAL];


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
        int sdl_image_flags = IMG_INIT_PNG; //is constant from an enum
        // can use | (or bitwise operator)for multiple flags
        // !(IMG_Init(sdl_image_flags) & sdl_image_flags) is only used to check is Init for PNG failed
        if (!(IMG_Init(sdl_image_flags) == sdl_image_flags))
        {
            printf("Error initializing SDL_Image. ERROR: %s\n", IMG_GetError());
            success = false;
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
            else
                my_surface = SDL_GetWindowSurface(my_window);
        }
    }
    
    return success;
}

SDL_Surface* load_surface(std::string path, unsigned char file_type)
{
    SDL_Surface* loaded_surface = NULL;
    SDL_Surface* optimized_surface = NULL;
    switch (file_type)
    {
        case TYPE_BMP:
        loaded_surface = SDL_LoadBMP(path.c_str());
            // what does path.c_str() do?
            
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
        optimized_surface = SDL_ConvertSurface(loaded_surface, my_surface->format, 0);
        // -> helps to access format in struct my_surface easily, since my_surface is a pointer and not actually a object (allocated on heap).
        //Same as (*my_surface).format
        if (optimized_surface == NULL)
        {
            printf("Error optimizing surface with path %s. ERROR: %s\n. ERROR: %s\n", path.c_str(), SDL_GetError(), IMG_GetError());
        }
        
        SDL_FreeSurface(loaded_surface);
    }

    return optimized_surface;
    
}


bool load_media()
{
    bool success = true;
    key_press_surfaces[DEFAULT_SURFACE] = load_surface("loaded.png", TYPE_PNG);
    if (key_press_surfaces[DEFAULT_SURFACE] == NULL)
    {
        printf("Failed to load default image");
        success = false;
    }
    key_press_surfaces[PRESS_KEYBOARD_UP] = load_surface("up.bmp", TYPE_BMP);
    if (key_press_surfaces[PRESS_KEYBOARD_UP] == NULL)
    {
        printf("Failed to load up image");
        success = false;
    }
    
    key_press_surfaces[PRESS_KEYBOARD_DOWN] = load_surface("down.bmp", TYPE_BMP);
    if ( key_press_surfaces[PRESS_KEYBOARD_DOWN] == NULL)
    {
        printf("Failed to load down image");
        success = false;
    }
    key_press_surfaces[PRESS_KEYBOARD_LEFT] = load_surface("left.bmp", TYPE_BMP);
    if (key_press_surfaces[PRESS_KEYBOARD_LEFT] == NULL)
    {
        printf("Failed to load left image");
        success = false;
    }
    key_press_surfaces[PRESS_KEYBOARD_RIGHT] = load_surface("right.bmp", TYPE_BMP);
    if (key_press_surfaces[PRESS_KEYBOARD_RIGHT] == NULL)
    {
        printf("Failed to load right image");
        success = false;
    }
    
    return success;
}

void close()
{
    for (int i = 0; i < PRESS_KEYBOARD_TOTAL; i++)
    {
        SDL_FreeSurface(key_press_surfaces[i]);
        key_press_surfaces[i] = NULL;
    }
    // Destroyed all LOADED surfaces
    SDL_DestroyWindow(my_window); //Takes care of destroying my_screen_surface
    IMG_Quit(); //Just like you initialize them, you have to quit them
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
           
           SDL_Rect crop_image;
           crop_image.x = 0; // x and y start from top left corner, goes to the right and downwards as x and y increase
           crop_image.y = 0;
           crop_image.h = 400;
           crop_image.w = 400;

           SDL_Rect stretch_rect;
           stretch_rect.x = 0;
           stretch_rect.y = 0;
           stretch_rect.h = SCREEN_HEIGHT;
           stretch_rect.w = SCREEN_WIDTH;
           
           SDL_Event event;
           current_surface_display = key_press_surfaces[DEFAULT_SURFACE];
           SDL_BlitScaled (current_surface_display, &crop_image, my_surface, &stretch_rect);
           //SDL_BlitSurface(current_surface_display, NULL, my_surface, NULL);
           SDL_UpdateWindowSurface(my_window);
           
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
                               current_surface_display = key_press_surfaces[PRESS_KEYBOARD_UP];
                               break;
                               
                           case SDLK_DOWN:
                               current_surface_display = key_press_surfaces[PRESS_KEYBOARD_DOWN];
                               break;
                               
                           case SDLK_LEFT:
                               current_surface_display = key_press_surfaces[PRESS_KEYBOARD_LEFT];
                               break;
                               
                           case SDLK_RIGHT:
                               current_surface_display = key_press_surfaces[PRESS_KEYBOARD_RIGHT];
                               break;
                               
                       }
                       
                   }
                   
                   // can update surface in SDL_POLLEVENT to optimize (only updates if event happens)
                   SDL_BlitScaled (current_surface_display, &crop_image, my_surface, &stretch_rect);
                   //SDL_BlitSurface(current_surface_display, NULL, my_surface, NULL);
                  SDL_UpdateWindowSurface(my_window);
               }
               
               //SDL_BlitScaled (current_surface_display, &crop_image, my_surface, &stretch_rect);
               //SDL_BlitSurface(current_surface_display, NULL, my_surface, NULL);
               //SDL_UpdateWindowSurface(my_window);
               //only updates surface after event handler takes all events of queue and returns 0
                
           }
       }
   }
    close();
    return 0;
}
