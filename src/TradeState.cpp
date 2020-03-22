#include "TradeState.h"

namespace sail { namespace onepunch { namespace ctp {

void CTPState::reqOrderInsert(TThostFtdcInstrumentIDType instrumentID, TThostFtdcPriceType price, TThostFtdcVolumeType volume, TThostFtdcDirectionType direction)
{
    onepunchTradeSpi->reqOrderInsert(instrumentID, price, volume, direction);
}

void SimulatorState::reqOrderInsert(TThostFtdcInstrumentIDType instrumentID, TThostFtdcPriceType price, TThostFtdcVolumeType volume, TThostFtdcDirectionType direction)
{
    if (direction == THOST_FTDC_D_Buy)
        user->buy(std::string(instrumentID), volume, price);
    else
        user->sell(std::string(instrumentID), volume, price);
}

}}}