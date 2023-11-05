//
//  timer.h
//  SDL-Game
//
//  Created by Ryan Kumar on 1/11/23.
//

#pragma once 


class SDLTimer
{
    public:
    SDLTimer();
    void start();
    void pause();
    void unpause();
    void stop();
    uint64_t get_time_since_start(); // this will get time since of program minus time since start
    bool is_paused();
    bool is_started();
    ~SDLTimer();
    
private:
    uint64_t m_start_ticks;
    uint64_t m_paused_ticks; // this is the different between time of program and time since start when paused
    bool m_is_paused;
    bool m_is_started;

};

struct ChronoTimer
{
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;
    int timer_number;

    ChronoTimer(int number)
    {
        start = std::chrono::high_resolution_clock::now();
        timer_number = number;
    
    }
    
    ~ChronoTimer()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << "Time for timer number" << timer_number << " is " << duration.count()*1'000'000'000 << "ns\n";
        
    }
};


