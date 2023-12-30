//
//  game_objects.hpp
//  SDL-Game
//
//  Created by Ryan Kumar on 30/12/23.
//

#pragma once
#include "object.h"

class GameObjects
{
public:
    void insert(Object* p_object);
    void remove(Object* p_object);
    void resolve_collision(Object* p_object_1, Object* p_object_2);
    void resolve_all_collisions();
    void update();
    void render();
    
private:
    std::vector<Object*> mp_objects;
    std::vector<Object*> mp_added_objects;
    
};


