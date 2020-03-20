#pragma once
// ---- 全局参数配置的类 ---- //

#include <unordered_map>
#include <string>
#include "CustomMdSpi.h"
#include "CustomTradeSpi.h"
#include "TickToKlineHelper.h"

// ---- 全局变量声明 ---- //
// 公共参数
extern TThostFtdcBrokerIDType gBrokerID;         // 模拟经纪商代码
extern TThostFtdcInvestorIDType gInvesterID;     // 投资者账户名
extern TThostFtdcPasswordType gInvesterPassword; // 投资者密码
extern TThostFtdcExchangeIDType gExchangeID;

// 行情参数
extern CThostFtdcMdApi *g_pMdUserApi;                                  // 行情指针
extern char gMdFrontAddr[63];                                             // 模拟行情前置地址
extern char *g_pInstrumentID[];                                        // 行情合约代码列表，中、上、大、郑交易所各选一种
extern int instrumentNum;                                              // 行情合约订阅数量
extern std::unordered_map<std::string, TickToKlineHelper> g_KlineHash; // 不同合约的k线存储表

// 交易参数
extern CThostFtdcTraderApi *g_pTradeUserApi;            // 交易指针
extern char gTradeFrontAddr[63];                           // 模拟交易前置地址
extern TThostFtdcInstrumentIDType g_pTradeInstrumentID; // 所交易的合约代码
extern TThostFtdcDirectionType gTradeDirection;         // 买卖方向
extern TThostFtdcPriceType gLimitPrice;                 // 交易价格

// 运行模式
// 1: CTP ; 2: simulator
extern int mode;

// 初始化配置函数
int initConfig();
