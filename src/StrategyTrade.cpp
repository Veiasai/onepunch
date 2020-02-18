#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include "StrategyTrade.h"
#include "Parameters.h"

// 线程互斥量
std::mutex marketDataMutex;

void StrategyCheckAndTrade(TThostFtdcInstrumentIDType instrumentID, CustomTradeSpi *customTradeSpi)
{
	// // 加锁
	// std::lock_guard<std::mutex> lk(marketDataMutex);
	// TickToKlineHelper tickToKlineObject = g_KlineHash.at(std::string(instrumentID));
	// // 策略
	// std::vector<double> priceVec = tickToKlineObject.m_priceVec;
	// if (priceVec.size() >= 3)
	// {
	// 	int len = priceVec.size();
	// 	// 最后连续三个上涨就买开仓,反之就卖开仓,这里暂时用最后一个价格下单
		
	// 	if (priceVec[len - 1] > priceVec[len - 2] && priceVec[len - 2] > priceVec[len - 3])
	// 	{
	// 		std::cerr << "orderBuy:" << priceVec[len - 1] << std::endl;
	// 		customTradeSpi->reqOrderInsert(instrumentID, priceVec[len - 1], 1, THOST_FTDC_D_Buy);
	// 	}
	// 	else if (priceVec[len - 1] < priceVec[len - 2] && priceVec[len - 2] < priceVec[len - 3])
	// 	{
	// 		std::cerr << "orderSell:" << priceVec[len - 1] << std::endl;
	// 		customTradeSpi->reqOrderInsert(instrumentID, priceVec[len - 1], 1, THOST_FTDC_D_Sell);
	// 	}
	// }
}
