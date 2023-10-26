//
//  my_enums.h
//  SDL-Game
//
//  Created by Ryan Kumar on 26/10/23.
//

//#pragma once
#ifndef my_enums
#define my_enums

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
#endif
