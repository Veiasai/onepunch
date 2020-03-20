#pragma once

#include "TradeState.h"
#include "string.h"

class Strategy
{
public:
    Strategy(TradeState *state, TThostFtdcInstrumentIDType src) : state(state)
    {
        memcpy(instrumentID, src, 31);
    }
    
    virtual void doStrategy() = 0;

protected:
    TradeState *state;
    TThostFtdcInstrumentIDType instrumentID;
};

class BaseStrategy : public Strategy
{
public:
    BaseStrategy(TradeState *state, TThostFtdcInstrumentIDType instrumentID) : Strategy(state, instrumentID) {}

    virtual void doStrategy() override;

private:
    inline void last3Stategy(double price1, double price2, double price3, TThostFtdcVolumeType volume);
};
