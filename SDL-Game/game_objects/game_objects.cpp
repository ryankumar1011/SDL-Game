//
//  game_objects.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 30/12/23.
//

#include "game_objects.h"
#include <vector>
#include <iostream>
#include "hearts.h"
#include "player.h"
#include "global_variables.h"

void GameObjects::insert(Object* p_object)
{
    mp_added_objects.push_back(p_object);
}

void GameObjects::remove(Object* p_object)
{
    p_object->delete_mark = true;
}

void GameObjects::resolve_collision(Object* p_object_1, Object* p_object_2)
{
    //can use dynamic casting instead of enums
    
    ObjectName object_1_name = p_object_1->get_name();
    ObjectName object_2_name = p_object_2->get_name();
    
    switch (object_1_name)
    {
        case KUNAI:
            
            switch(object_2_name)
            {
                case PLAYER:
                    remove(p_object_1);
                    
                    std::cout << "Kunai hit\n";
                    
                    if ((static_cast<Player*>(p_object_2))->pop_heart())
                    {
                        std::cout << "you loose\n";
                    }
                    
                    break;

                case KUNAI:
                    remove(p_object_1);
                    remove(p_object_2);
                    
                    break;
            }
            
            break;
            
        case PLAYER:
            
            switch(object_2_name)
            {
                case KUNAI:
                   
                    remove(p_object_2);
                    
                    std::cout << "Kunai hit\n";
                    
                    if (!(static_cast<Player*>(p_object_1))->pop_heart())
                    {
                        std::cout << "you loose\n";
                    }
                    
                    break;
            }
            
            break;
    }
}
    
void GameObjects::resolve_all_collisions()
{
    for (int i = 0; i < mp_objects.size(); i++)
    {
        for (int j = i + 1; j < mp_objects.size(); j++)
        {
            if(mp_objects[i]->check_collision(mp_objects[j]))
            {
                resolve_collision(mp_objects[i], mp_objects[j]);
                
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

    resolve_all_collisions();

}

void GameObjects::render()
{
    for (Object* p_object : mp_objects)
    {
        p_object->render();
        p_object->render_colliders();
    }
}

