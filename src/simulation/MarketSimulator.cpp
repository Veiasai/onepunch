#include "MarketSimulator.h"
#include <random>
#include <ctime>
#include <iostream>
#include <thread>

namespace sail { namespace onepunch { namespace simulator {

void Market::run()
{
    running = true;

    // random seed
    std::random_device r;
    std::default_random_engine e1(r());
    // 每次变化价格为0~3中的一个double
    std::uniform_real_distribution<double> uniform_dist(-3, 3);

    int lastTime = time(0);
    int thisTime;
    const int elapsed = 3; // sec

    while (running)
    {
        thisTime = time(0);
        if (thisTime - lastTime > elapsed)
        {
            double delta = uniform_dist(e1);

            tradeinfo.LastPrice += delta;
            tradeinfo.AskPrice1 += delta;
            tradeinfo.BidPrice1 += delta;
            tradeinfo.UpdateTime = thisTime;

            lastTime = thisTime;
        }
    }
}

TradeInfo Market::getTradeInfo()
{

    std::tm *ptm = std::localtime(&tradeinfo.UpdateTime);
    char buffer[32];
    // Format: Mo, 15.06.2009 20:20:00
    std::strftime(buffer, 32, "%a, %Y.%m.%d %H:%M:%S", ptm);

    std::cout << "--获取 " << tradeinfo.instrumentId << " 当前信息--" << std::endl
              << "上次更新时间: " << buffer << std::endl
              << "最新价格: " << tradeinfo.LastPrice << std::endl
              << "成交量: " << tradeinfo.Volume << std::endl
              << "申买价1: " << tradeinfo.BidPrice1 << std::endl
              << "申买量1: " << tradeinfo.BidVolume1 << std::endl
              << "申卖价1: " << tradeinfo.AskPrice1 << std::endl
              << "申卖量1: " << tradeinfo.AskVolume1 << std::endl;

    return tradeinfo;
}

}}} // namespace simulator
