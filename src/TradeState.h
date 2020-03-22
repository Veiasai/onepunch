#pragma once

#include "CTP_API/inc/ThostFtdcUserApiStruct.h"
#include "TickToKlineHelper.h"
#include "OnePunchTradeSpi.h"
#include "simulation/OptionIndex.h"
#include "simulation/User.h"

namespace sail { namespace onepunch { namespace ctp {

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
    CTPState(OnePunchTradeSpi *onepunchTradeSpi) : onepunchTradeSpi(onepunchTradeSpi) {}

    virtual void reqOrderInsert(TThostFtdcInstrumentIDType instrumentID, TThostFtdcPriceType price, TThostFtdcVolumeType volume, TThostFtdcDirectionType direction) override;

    virtual simulator::OptionIndex *getOptionIndex() override
    {
        return nullptr;
    }

private:
    OnePunchTradeSpi *onepunchTradeSpi;
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

}}}