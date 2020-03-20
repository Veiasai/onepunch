#pragma once

#include "CTP_API/inc/ThostFtdcUserApiStruct.h"
#include "TickToKlineHelper.h"
#include "CustomTradeSpi.h"
#include "simulation/OptionIndex.h"
#include "simulation/User.h"

class TradeState
{
public:
    virtual void
    reqOrderInsert(TThostFtdcInstrumentIDType instrumentID, TThostFtdcPriceType price, TThostFtdcVolumeType volume, TThostFtdcDirectionType direction) = 0;

    virtual simulator::OptionIndex *getOptionIndex() = 0;
};

class CTPState : public TradeState
{
public:
    CTPState(CustomTradeSpi *customTradeSpi) : customTradeSpi(customTradeSpi) {}

    virtual void reqOrderInsert(TThostFtdcInstrumentIDType instrumentID, TThostFtdcPriceType price, TThostFtdcVolumeType volume, TThostFtdcDirectionType direction) override;

    virtual simulator::OptionIndex *getOptionIndex() override
    {
        return nullptr;
    }

private:
    CustomTradeSpi *customTradeSpi;
};

class SimulatorState : public TradeState
{
public:
    SimulatorState(simulator::User *user, simulator::OptionIndex *optionIndex) : user(user), optionIndex(optionIndex) {}

    virtual void reqOrderInsert(TThostFtdcInstrumentIDType instrumentID, TThostFtdcPriceType price, TThostFtdcVolumeType volume, TThostFtdcDirectionType direction) override;

    virtual simulator::OptionIndex *getOptionIndex() override
    {
        return optionIndex;
    }

private:
    simulator::User *user;
    simulator::OptionIndex *optionIndex;
};
