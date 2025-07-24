//
//  timer.h
//  SDL-Game
//
//  Created by Ryan Kumar on 1/11/23.
//

#pragma once 

#include <chrono>
#include <iostream>

class SDLTimer
{
    
public:
    
    SDLTimer();
    
    void start();
    
    void pause();
    
    void unpause();
    
    void stop();
    
    uint64_t get_time(); // this will get time since of program minus time since start
    
    bool is_paused();
    
    bool is_started();
    
    ~SDLTimer();
    
private:
    
    uint64_t m_start_ticks;
    
    uint64_t m_paused_ticks; // this is the different between time of program and time since start when paused
    
    bool m_is_paused;
    
    bool m_is_started;
};

//The below struct measures the time it takes for an instance of it to go out of scope. It can be used to measure the time taken for a function to execute

class ChronoTimer
{
   
public:
    
    ChronoTimer();
    
    ~ChronoTimer();
    
private:
    
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    
    std::chrono::duration<float> duration;
    
};


