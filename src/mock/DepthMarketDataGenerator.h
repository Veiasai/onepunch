#pragma once

#include <unordered_map>
#include <iostream>
#include <random>
#include <vector>
#include "../CTP_API/inc/ThostFtdcUserApiStruct.h"

namespace sail { namespace onepunch { namespace mock {

class DepthMarketDataGenerator
{
public:
    DepthMarketDataGenerator(std::unordered_map<std::string, std::vector<CThostFtdcDepthMarketDataField>> & DepthMarketDataHash, const std::string & instrumentId, int marketDataRandomSeed)
     : instrumentId(instrumentId), DepthMarketDataHash(DepthMarketDataHash)
    {
        if (DepthMarketDataHash.find(instrumentId) == DepthMarketDataHash.end())
		    DepthMarketDataHash[instrumentId] = {CThostFtdcDepthMarketDataField()}  ;
        mt.seed(marketDataRandomSeed);
    }
    void poll(int insertNum);

    std::unordered_map<std::string, std::vector<CThostFtdcDepthMarketDataField>> & DepthMarketDataHash;
private:
    const std::string instrumentId;
    CThostFtdcDepthMarketDataField data;
    std::mt19937 mt;
    std::normal_distribution<double> normal_dist = std::normal_distribution<double>(200, 6);
};

}}} // namespace simulator