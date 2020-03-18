#include "Strategy.h"
#include "Parameters.h"
#include <mutex>
#include <vector>
#include "Timer.h"
#include <iostream>

// 线程互斥量
std::mutex DataMutex;

void BaseStrategy::doStrategy()
{
    // timer start
    const auto start = timer::rdtscp_clock::now();

    // 加锁
    std::lock_guard<std::mutex> lk(DataMutex);

    if (mode == 1)
    {
        //CTP
        TickToKlineHelper tickToKlineObject = g_KlineHash.at(std::string(instrumentID));
        // 策略
        std::vector<double> priceVec = tickToKlineObject.m_priceVec;

        int len = priceVec.size();
        if (len > 3)
            last3Stategy(priceVec[len - 1], priceVec[len - 2], priceVec[len - 3], 1);
    }
    else
    {
        // simulator
        std::vector<simulator::TradeInfo> list = (state->getOptionIndex())->getTradeInfoList(std::string(instrumentID));

        int ssize = list.size();
        if (ssize > 3)
            last3Stategy(list[ssize - 1].LastPrice, list[ssize - 2].LastPrice, list[ssize - 3].LastPrice, 1);
    }

    // timer end
    const auto duration = timer::rdtscp_clock::now() - start;
    ulong count = duration.count();
    std::cout << "It took " << count / 2.099996 << " (ns)" << std::endl;
}

inline void BaseStrategy::last3Stategy(double price1, double price2, double price3, TThostFtdcVolumeType volume)
{
    if (price1 > price2 && price2 > price3)
        state->reqOrderInsert(instrumentID, price1, volume, THOST_FTDC_D_Buy);
    else if (price1 < price2 && price2 < price3)
        state->reqOrderInsert(instrumentID, price1, volume, THOST_FTDC_D_Sell);
}