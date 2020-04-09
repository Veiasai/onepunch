#include <iostream>
#include <stdio.h>
#include <string>
#include "Parameters.h"
#include "OnePunchMdSpi.h"
#include "OnePunchTradeSpi.h"
#include "simulation/MarketSimulator.h"
#include "simulation/KLineGenerator.h"
#include "mock/MockMdApi.h"
#include "mock/MockTradeApi.h"
#include "Strategy.h"
#include <thread>
#include "assert.h"

using namespace std;
using namespace sail::onepunch;

int main()
{
	// 初始化全局参数配置
	cout << "初始化参数..." << endl;
	parameter::Config *config = parameter::readConfigFromFile("./config/ctpconfig.cfg");
	cout << *config;
	std::unordered_map<std::string, TickToKlineHelper> g_KlineHash;
	ctp::OnePunchMdSpi *pMdUserSpi = new ctp::OnePunchMdSpi(g_KlineHash,
															config->gBrokerID, config->gInvesterID, config->gInvesterPassword, config->gExchangeID,
															config->gMdFrontAddr, config->g_pInstrumentID, config->instrumentNum); // 创建行情回调实例
	ctp::OnePunchTradeSpi *pTradeSpi = new ctp::OnePunchTradeSpi(g_KlineHash,
																 config->gBrokerID, config->gInvesterID, config->gInvesterPassword, config->gExchangeID,
																 config->g_pTradeInstrumentID); // 创建交易回调实例
	// 1:CTP 2:simulator
	if (config->mode == 1)
	{
		// 初始化行情线程
		cout << "初始化行情..." << endl;
		CThostFtdcMdApi *g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi(); // 创建行情实例
		pMdUserSpi->setMdUserApi(g_pMdUserApi);
		g_pMdUserApi->RegisterSpi(pMdUserSpi);			   // 注册事件类
		g_pMdUserApi->RegisterFront(config->gMdFrontAddr); // 设置行情前置地址
		g_pMdUserApi->Init();							   // 连接运行

		// 初始化交易线程
		cout << "初始化交易..." << endl;
		CThostFtdcTraderApi *g_pTradeUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(); // 创建交易实例
		pTradeSpi->setTradeUserApi(g_pTradeUserApi);
		g_pTradeUserApi->RegisterSpi(pTradeSpi);					// 注册事件类
		g_pTradeUserApi->SubscribePublicTopic(THOST_TERT_RESTART);	// 订阅公共流
		g_pTradeUserApi->SubscribePrivateTopic(THOST_TERT_RESTART); // 订阅私有流
		g_pTradeUserApi->RegisterFront(config->gTradeFrontAddr);	// 设置交易前置地址
		g_pTradeUserApi->Init();									// 连接运行

		// 等到线程退出
		g_pMdUserApi->Join();
		delete pMdUserSpi;
		g_pMdUserApi->Release();

		g_pTradeUserApi->Join();
		delete pTradeSpi;
		g_pTradeUserApi->Release();

		// 转换本地k线数据
		// TickToKlineHelper tickToKlineHelper;
		// tickToKlineHelper.KLineFromLocalData("market_data.csv", "K_line_data.csv");

		// getchar();
	}
	else if (config->mode == 2)
	{
		simulator::KLineGenerator *kg = new simulator::KLineGenerator(g_KlineHash, config->g_pTradeInstrumentID, config->marketDataRamdomSeed);
		simulator::User *user = new simulator::User(config->gInvesterID);
		simulator::OptionIndex *optionIndex = new simulator::OptionIndex();
		optionIndex->addInstrument(string(config->g_pTradeInstrumentID));

		ctp::TradeState *ts = new ctp::SimulatorState(user, optionIndex);
		strategy::Strategy *s1 = new strategy::BaseStrategy(ts, config->g_pTradeInstrumentID);
		while (true)
		{
			kg->poll(1);
			s1->doStrategy(g_KlineHash);
			std::this_thread::sleep_for(std::chrono::seconds(config->interval));
		}
	}
	else if (config->mode == 3)
	{
		// TODO
		// Refer to the mode 1
		// But use Mock CTP MdApi and Mock CTP TradeApi,

		// 初始化行情线程
		cout << "初始化行情..." << endl;
		mock::MockMdApi *g_pMdUserApi = mock::MockMdApi::CreateFtdcMdApi(); // 创建行情实例
		pMdUserSpi->setMdUserApi(g_pMdUserApi);
		g_pMdUserApi->RegisterSpi(pMdUserSpi);											   // 注册事件类
		g_pMdUserApi->RegisterFront(config->gMdFrontAddr);								   // 设置行情前置地址
		g_pMdUserApi->SubscribeMarketData(config->g_pInstrumentID, config->instrumentNum); // 设置订阅合约
		g_pMdUserApi->Init();															   // 连接运行

		// 初始化交易线程
		cout << "初始化交易..." << endl;
		mock::MockTraderApi *g_pTradeUserApi = mock::MockTraderApi::CreateFtdcTraderApi(); // 创建交易实例
		pTradeSpi->setTradeUserApi(g_pTradeUserApi);
		g_pTradeUserApi->RegisterSpi(pTradeSpi);					// 注册事件类
		g_pTradeUserApi->SubscribePublicTopic(THOST_TERT_RESTART);	// 订阅公共流
		g_pTradeUserApi->SubscribePrivateTopic(THOST_TERT_RESTART); // 订阅私有流
		g_pTradeUserApi->RegisterFront(config->gTradeFrontAddr);	// 设置交易前置地址
		g_pTradeUserApi->Init();									// 连接运行

		// 等到线程退出
		g_pMdUserApi->Join();
		delete pMdUserSpi;
		g_pMdUserApi->Release();

		g_pTradeUserApi->Join();
		delete pTradeSpi;
		g_pTradeUserApi->Release();
	}
	else
	{
		assert(0);
	}

	return 0;
}
