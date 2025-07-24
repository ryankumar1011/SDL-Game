//
//  game_buttons.cpp
//  SDL-Game
//
//  Created by Ryan Kumar on 13/3/24.
//

#include "game_buttons.h"

void GameButtons::insert(Button* p_button)
{
    mp_buttons.push_back(p_button);
}

void GameButtons::handle_event(SDL_Event event)
{
    for (Button* p_button : mp_buttons)
    {
        p_button->handle_event(event);
    }
}

void GameButtons::remove(Button* p_button)
{
  mp_buttons.erase(std::remove(mp_buttons.begin(), mp_buttons.end(), p_button), mp_buttons.end());
}

void GameButtons::update()
{
    for (Button* p_button : mp_buttons)
    {
        p_button->update();
    }
}

void GameButtons::render()
{
    for (Button* p_button : mp_buttons)
    {
        p_button->render();
    }
}


