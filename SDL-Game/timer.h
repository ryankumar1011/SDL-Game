//
//  timer.h
//  SDL-Game
//
//  Created by Ryan Kumar on 1/11/23.
//

#pragma once 

struct Timer
{
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;
    int timer_number;

    Timer(int number)
    {
        start = std::chrono::high_resolution_clock::now();
        timer_number = number;
    
    }
    
    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << "Time for timer number" << timer_number << " is " << duration.count()*1'000'000'000 << "ns\n";
        
    }
    
};


