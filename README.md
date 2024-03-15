# About this project

This project is a simple multiplayer combat game made in  C++, using only SDL2 libraries such as SDL_Image, SDL_mixer and SDL_ttf. I’m hoping it gives me a taste of game design and supplements my learning of C++ during my course. Huge thanks to Lazy Foo’s online tutorials (add link) for guiding me with using these libraries.

# How to download 
~ I will soon add the .exec file

# Gameplay and Controls 
Below is the in game controls information screen in the game. 

![game_manual](https://github.com/ryankumar1011/SDL-Game/assets/65263492/1bad5add-06be-4459-8d54-90b6d69d8929)

In the case my drawings are worse than I think they are, it goes something like this:
* Getting hit by a kunai decreases a player’s health by 1
* Hitting an apple with a kunai gives a Player three additional kunai
* Throwing a kunai loses the player a kunai (duh..)
* A player loses the game when they have no health left

Apples are harmless objects that randomly fall somewhere in the middle of the screen. The counters for kunai and health left are shown at the top corners of the screen, as seen below.

<img width="999" alt="Screenshot 2024-03-15 at 6 33 38 AM" src="https://github.com/ryankumar1011/SDL-Game/assets/65263492/19f1fed7-34b5-4b5c-a97d-2cf7bd294924">

I’ve also implemented a shield a player can use to block a kunai (why…?).

# Animations and visual effects
I’ve spent too long making this 2 second animation for it to not have its own section (again....why???)

https://github.com/ryankumar1011/SDL-Game/assets/65263492/01fdc510-faf0-4bbb-acfa-6cd3907c632f

Here’s the sprite sheet

![player_animations2](https://github.com/ryankumar1011/SDL-Game/assets/65263492/1539fce8-20e9-479b-a170-04acc2508886)

Here’s how deploying the shield looks like. I’m just changing its scale factor until it reaches a cap.

https://github.com/ryankumar1011/SDL-Game/assets/65263492/e08c9ed4-c1df-400a-8b94-d4c922fa0b3f

I’ve also added visual and sound effects for button clicks and collisions, that can be seen in the game


Every visual element and object can be easily resized using a different scale factor. I’ve made sure the colliders, animations and collision system automatically account for this. For testing, the colliders can be rendered by uncommenting the below line of code.

<img width="368" alt="Screenshot 2024-03-15 at 7 06 48 AM" src="https://github.com/ryankumar1011/SDL-Game/assets/65263492/078acfb0-8e02-4e5b-9602-deef25abefb2">

And we can the results here 

<img width="998" alt="Screenshot 2024-03-15 at 7 12 04 AM" src="https://github.com/ryankumar1011/SDL-Game/assets/65263492/a4321571-3934-4378-98f7-57986a9e85c4">



# Code structure

Sorry if the documentation in the code is scarce, I’m currently working on it. Here’s the rundown:

Global variables in this project are declared in global_variables.h using the extern keyword. I’ve tried to keep to a minimum. They include pointers to the structs SDL_Window and SDL_Renderer (used for rendering), the screen width and height, and an instance of classes GameObjects and GameButtons.

The GameObjects and GameButtons instances are used to insert, remove, update and render the contents of two std::vectors containing pointers to all current instances of parent classes Object and Button respectively. Player, Kunai, Apple, and Shield are child classes of Object and MusicButton, ControlsButton, MenuButton are child classes of Button. This is how information and functionality for all objects and buttons is implemented.

The Hearts, KunaiCounter, FrameRate classes are all used to update and render visual elements and so are not under objects. The player class contains an instance of Hearts and KunaiCounter to update them accordingly.

The MusicHandler class stores pointers to the background music and sound effects. Its functions are called to play sound. The Texture class contains functionality on loading and rendering images and fonts as textures, with options for color keying, alpha modding, etc.

The init.cpp file contains functions for initializing SDL and its libraries. It gets the pointers for SDL_Window and SDL_Renderer and loads all images, fonts and audio. It also sets the clips for all used sprites. Before the main game loop, SDL is initialized and media is loaded using functions from init.cpp.

The main game loop is separated into the event handling, logic and rendering. These are separated into different files and called as functions for clarity. The global variables g_menu and g_controls_menu determine what texture to update and render.























