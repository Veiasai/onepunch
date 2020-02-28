#include <iostream>
#include <stdio.h>
#include <string>
#include "Parameters.h"

using namespace std;

int main()
{
	// 账号密码
	// cout << "请输入账号： ";
	// scanf("%s", gInvesterID);
	// cout << "请输入密码： ";
	// scanf("%s", gInvesterPassword);

	// 初始化全局参数配置
	cout << "初始化参数..." << endl;
	if (initConfig())
		cerr << "参数配置出错" << endl;

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
	return 0;
}