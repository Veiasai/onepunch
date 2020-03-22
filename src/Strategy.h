#pragma once

#include "TradeState.h"
#include "string.h"
#include <unordered_map>
#include "TickToKlineHelper.h"

namespace sail { namespace onepunch { namespace strategy {

class Strategy
{
public:
    Strategy(ctp::TradeState *state, TThostFtdcInstrumentIDType src) : state(state)
    {
        memcpy(instrumentID, src, 31);
    }
    
    virtual void doStrategy(const std::unordered_map<std::string, TickToKlineHelper> & g_KlineHash) = 0;

protected:
    ctp::TradeState *state;
    TThostFtdcInstrumentIDType instrumentID;
};

class BaseStrategy : public Strategy
{
public:
    BaseStrategy(ctp::TradeState *state, TThostFtdcInstrumentIDType instrumentID) : Strategy(state, instrumentID) {}

    virtual void doStrategy(const std::unordered_map<std::string, TickToKlineHelper> & g_KlineHash) override;

private:
    inline void last3Stategy(double price1, double price2, double price3, TThostFtdcVolumeType volume);
};

}}}