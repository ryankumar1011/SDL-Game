//
//  game_objects.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 30/12/23.
//

#include "game_objects.h"
#include "hearts.h"
#include "player.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <SDL2/SDL.h>

void GameObjects::insert(Object* p_object)
{
    mp_added_objects.push_back(p_object);
}

void GameObjects::remove(Object* p_object)
{
    p_object->delete_mark = true;
}
    
void GameObjects::resolve_collisions()
{
    for (int i = 0; i < mp_objects.size(); i++)
    {
        for (int j = i + 1; j < mp_objects.size(); j++)
        {
            if(mp_objects[i]->check_collision(mp_objects[j]))
            {
                mp_objects[i]->resolve_collision(mp_objects[j]);
            }
        }
    }
}

void GameObjects::update()
{
    for (Object* p_added_object : mp_added_objects)
    {
        mp_objects.push_back(p_added_object);
    }
    
    mp_added_objects.clear();
    
    auto remove_if_lambda = [](Object* object)
    {
        if (object->delete_mark)
        {
            delete object;
            return true;
        }
        return false;
    };

    mp_objects.erase(std::remove_if(mp_objects.begin(), mp_objects.end(), remove_if_lambda), mp_objects.end());

    for (Object* p_object : mp_objects)
    {
        p_object->update_position();
    }

    resolve_collisions();
}

void GameObjects::render()
{
    for (Object* p_object : mp_objects)
    {
        p_object->render();
        p_object->render_colliders();
        
    }
}

