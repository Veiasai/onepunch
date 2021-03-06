#pragma once

#include <map>
#include <vector>
#include "Parameter.h"

namespace sail { namespace onepunch { namespace simulator {

class OptionIndex
{
protected:
    // instrumentId -> tradeInfo list
    // each vector's maxsize is 120
    std::map<std::string, std::vector<TradeInfo>> instrumentMap;

public:
    explicit OptionIndex() : instrumentMap(){};
    explicit OptionIndex(const std::map<std::string, std::vector<TradeInfo>> &iMap) : instrumentMap(iMap){};

    // update
    inline void addInstrument(const std::string &instrumentId) { instrumentMap[instrumentId] = std::vector<TradeInfo>(); }
    void updateInstrument(const std::string &instrumentId, TradeInfo tradeinfo);

    // get
    std::vector<std::string> getAllInstruments() const;
    inline std::vector<TradeInfo> getTradeInfoList(const std::string &instrumentId) const { return instrumentMap.at(instrumentId); };
};

}}} // namespace simulator
