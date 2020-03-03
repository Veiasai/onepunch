#include "Strategy.h"
#include <mutex>

namespace simulator
{
std::mutex MarketDataMutex;

void BaseStrategy::onUnderlyingChanged(const std::string &instrumentId, const OptionIndex &optionIndex)
{
    // 加锁
    std::lock_guard<std::mutex> lk(MarketDataMutex);

    std::vector<TradeInfo> list = optionIndex.getTradeInfoList(instrumentId);
    int ssize = list.size();

    if (ssize > 3)
    {
        // 最后连续三个上涨就买开仓,反之就卖开仓,这里暂时用最后一个价格下单

        if (list[ssize - 1].LastPrice > list[ssize - 2].LastPrice && list[ssize - 2].LastPrice > list[ssize - 3].LastPrice)
            buyOption(instrumentId, 1, list[ssize - 1].LastPrice);
        else if (list[ssize - 1].LastPrice < list[ssize - 2].LastPrice && list[ssize - 2].LastPrice < list[ssize - 3].LastPrice)
            sellOption(instrumentId, 1, list[ssize - 1].LastPrice);
    }
};
} // namespace simulator
