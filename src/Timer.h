#pragma once
// ---- 时间测量的类 ---- //

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <ratio>
#include <iostream>
#include <fstream>

namespace timer
{
// An implementation of the 'TrivialClock' concept using the rdtscp instruction.
struct rdtscp_clock
{
    using rep = std::uint64_t;
    using period = std::ratio<1>;
    using duration = std::chrono::duration<rep, period>;
    using time_point = std::chrono::time_point<rdtscp_clock, duration>;

    rdtscp_clock(int i, int j)
    {
        ask_start_index = i;
        ask_end_index = j;
    }

    static auto now() noexcept -> time_point
    {
        std::uint32_t hi, lo;
        __asm__ __volatile__("rdtscp"
                             : "=d"(hi), "=a"(lo));
        return time_point(duration((static_cast<std::uint64_t>(hi) << 32) | lo));
    }

    time_point ask_start[10];
    int ask_start_index;

    void timer_ask_start()
    {
        std::uint32_t hi, lo;
        __asm__ __volatile__("rdtscp"
                             : "=d"(hi), "=a"(lo));
        ask_start[ask_start_index] = time_point(duration((static_cast<std::uint64_t>(hi) << 32) | lo));
        ask_start_index++;
    }

    time_point ask_end[10];
    int ask_end_index;

    void timer_ask_end()
    {
        std::uint32_t hi, lo;
        __asm__ __volatile__("rdtscp"
                             : "=d"(hi), "=a"(lo));
        ask_end[ask_end_index] = time_point(duration((static_cast<std::uint64_t>(hi) << 32) | lo));
        ask_end_index++;
    }

    void timer_ask_print()
    {
        std::ofstream outFile;
        outFile.open("out", std::ios::app);
        for (int i = 0; i < ask_end_index; i++)
            outFile << (ask_end[i] - ask_start[i]).count() / 2.5 << ",";
        
        outFile << std::endl;
    }

    void init(){
        ask_start_index = 0;
        ask_end_index = 0;
    }
};

// Times how long it takes a function to execute using the specified clock.
template <class Clock = rdtscp_clock, class Func>
auto time(Func &&function) -> typename Clock::duration
{
    const auto start = Clock::now();
    function();
    return Clock::now() - start;
}

} // namespace timer
