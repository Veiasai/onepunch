#include "DepthMarketDataGenerator.h"
#include <string.h>

namespace sail { namespace onepunch { namespace mock {

void DepthMarketDataGenerator::poll(int num)
{
    for (; num > 0; num--)
    {
        double price = normal_dist(mt);
        memcpy(data.InstrumentID, instrumentId.c_str(), 32);
        data.LastPrice = price;
        data.Volume = 5;
        data.BidPrice1 = price + 5;
        data.BidVolume1 = 5;
        data.AskPrice1 = price - 5;
        data.AskVolume1 = 5;
        
        DepthMarketDataHash[instrumentId].push_back(data);
    }
}

} // namespace mock
} // namespace onepunch
} // namespace sail