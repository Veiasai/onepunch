#pragma once

#include <unordered_map>
#include "Parameter.h"
#include <iostream>
#include <random>
#include "../TickToKlineHelper.h"

namespace sail { namespace onepunch { namespace simulator {

class KLineGenerator
{
public:
    KLineGenerator(std::unordered_map<std::string, TickToKlineHelper> & g_KlineHash, const std::string & instrumentId, int marketDataRandomSeed)
     : instrumentId(instrumentId), g_KlineHash(g_KlineHash)
    {
        if (g_KlineHash.find(instrumentId) == g_KlineHash.end())
		    g_KlineHash[instrumentId] = TickToKlineHelper();
        mt.seed(marketDataRandomSeed);
    }
    void poll(int insertNum);
private:
    const std::string instrumentId;
    std::unordered_map<std::string, TickToKlineHelper> & g_KlineHash;
    KLineDataType k_line_data;
    std::mt19937 mt;
    std::normal_distribution<double> normal_dist = std::normal_distribution<double>(200, 6);
};

}}} // namespace simulator
