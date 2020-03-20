#include <iostream>
#include <stdio.h>
#include <string>
#include "Parameters.h"
#include "simulation/MarketSimulator.h"
#include "Strategy.h"
#include <thread>

using namespace std;

void CTPMain()
{
	
	// 初始化行情线程
	cout << "初始化行情..." << endl;
	g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi(); // 创建行情实例
	CThostFtdcMdSpi *pMdUserSpi = new CustomMdSpi;	 // 创建行情回调实例
	g_pMdUserApi->RegisterSpi(pMdUserSpi);			   // 注册事件类
	g_pMdUserApi->RegisterFront(gMdFrontAddr);		   // 设置行情前置地址

	g_pMdUserApi->Init(); // 连接运行

	// 初始化交易线程
	cout << "初始化交易..." << endl;
	g_pTradeUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(); // 创建交易实例

	CustomTradeSpi *pTradeSpi = new CustomTradeSpi;				// 创建交易回调实例
	g_pTradeUserApi->RegisterSpi(pTradeSpi);					// 注册事件类
	g_pTradeUserApi->SubscribePublicTopic(THOST_TERT_RESTART);  // 订阅公共流
	g_pTradeUserApi->SubscribePrivateTopic(THOST_TERT_RESTART); // 订阅私有流
	g_pTradeUserApi->RegisterFront(gTradeFrontAddr);			// 设置交易前置地址
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

void simulatorMain()
{

	TThostFtdcInstrumentIDType instrumentId = "i2005";
	simulator::Market one = simulator::Market(instrumentId);

	simulator::User *user = new simulator::User("zwq");
	simulator::OptionIndex *optionIndex = new simulator::OptionIndex();
	optionIndex->addInstrument(string(instrumentId));

	TradeState *ts = new SimulatorState(user, optionIndex);
	Strategy *s1 = new BaseStrategy(ts, instrumentId);

	thread t1(bind(&simulator::Market::run, &one));

	// 每三秒去一次信息，取得五次信息就结束程序
	int lastTime = time(0);
	int thisTime;
	const int elapsed = 3; // sec

	int count = 0;
	while (true)
	{
		thisTime = time(0);
		if (thisTime - lastTime > elapsed)
		{
			simulator::TradeInfo ti = one.getTradeInfo();
			optionIndex->updateInstrument(instrumentId, ti);

			s1->doStrategy();

			lastTime = thisTime;

			count++;
		}
	}

	one.stop();

	t1.join();
}

int main()
{
	// 初始化全局参数配置
	cout << "初始化参数..." << endl;
	if (initConfig())
		cerr << "参数配置出错" << endl;

	// 1:CTP 2:simulator
	if (mode == 1)
		CTPMain();
	else
		simulatorMain();

	return 0;
}
