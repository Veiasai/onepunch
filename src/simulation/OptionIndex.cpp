#include "OptionIndex.h"

namespace sail { namespace onepunch { namespace simulator {

// update
void OptionIndex::updateInstrument(const std::string &instrumentId, TradeInfo tradeinfo)
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

}}} // namespace simulator
