#include "OptionIndex.h"

namespace simulator
{
// update
inline void OptionIndex::addInstrument(const std::string &instrumentId)
{
    instrumentMap[instrumentId] = std::vector<TradeInfo>();
}
inline void OptionIndex::updateInstrument(const std::string &instrumentId, const TradeInfo &tradeinfo)
{
    if (instrumentMap[instrumentId].size() > 120)
        instrumentMap[instrumentId].erase(instrumentMap[instrumentId].begin(), instrumentMap[instrumentId].begin() + 20);
    else
        instrumentMap[instrumentId].push_back(tradeinfo);
}

// get
std::vector<std::string> OptionIndex::getAllInstruments() const
{
    std::vector<std::string> ret;
    for (auto it = instrumentMap.begin(); it != instrumentMap.end(); it++)
        ret.push_back(it->first);

    return ret;
}
inline std::vector<TradeInfo> OptionIndex::getTradeInfoList(const std::string &instrumentId) const
{
    return instrumentMap.at(instrumentId);
}
} // namespace simulator
