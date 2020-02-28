#pragma once
// ---- 时间测量的类 ---- //

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <ratio>

namespace timer
{
// An implementation of the 'TrivialClock' concept using the rdtscp instruction.
struct rdtscp_clock
{
    using rep = std::uint64_t;
    using period = std::ratio<1>;
    using duration = std::chrono::duration<rep, period>;
    using time_point = std::chrono::time_point<rdtscp_clock, duration>;

    static auto now() noexcept -> time_point
    {
        std::uint32_t hi, lo;
        __asm__ __volatile__("rdtscp"
                             : "=d"(hi), "=a"(lo));
        return time_point(duration((static_cast<std::uint64_t>(hi) << 32) | lo));
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
