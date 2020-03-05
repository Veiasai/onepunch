#pragma once

#include <unordered_map>
#include "Parameter.h"
#include <iostream>

namespace simulator
{
class Market
{
public:
    Market(std::string instrumentId) : tradeinfo(instrumentId), running(false)
    {
        std::cout << "初始化行情" << std::endl
                  <<"======================="<< std::endl;
    }

    // update tradeinfo per 3 seconds
    void run();
    // get latest tradeinfo
    TradeInfo getTradeInfo();
    // stop market running
    inline void stop() { running = false; };

private:
    TradeInfo tradeinfo;
    bool running;
};
} // namespace simulator
