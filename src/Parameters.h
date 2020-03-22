#pragma once
// ---- 全局参数配置的类 ---- //
#include "CTP_API/inc/ThostFtdcTraderApi.h"
#include "CTP_API/inc/ThostFtdcMdApi.h"
#include <string>
#include <iostream>

namespace sail { namespace onepunch { namespace parameter {

struct Config {
    // 公共参数
    TThostFtdcBrokerIDType gBrokerID;         // 模拟经纪商代码
    TThostFtdcInvestorIDType gInvesterID;     // 投资者账户名
    TThostFtdcPasswordType gInvesterPassword; // 投资者密码
    TThostFtdcExchangeIDType gExchangeID;

    // 行情参数
    char gMdFrontAddr[63];                                             // 模拟行情前置地址
    char ** g_pInstrumentID;                                        // 行情合约代码列表，中、上、大、郑交易所各选一种
    int instrumentNum;                                              // 行情合约订阅数量

    // 交易参数
    char gTradeFrontAddr[63];                           // 模拟交易前置地址
    TThostFtdcInstrumentIDType g_pTradeInstrumentID; // 所交易的合约代码

    // 运行模式
    // 1: CTP ; 2: simulator
    int mode;

    // Simulate
    int marketDataRamdomSeed;
    int interval;

    private:
	    friend std::ostream& operator<<(std::ostream &out, Config &c) {
            out << "gbrokerID:"  << c.gBrokerID << std::endl;
            out << "gInvesterID: " << c.gInvesterID << std::endl;
            out << "gInvesterPassword: " << c.gInvesterPassword << std::endl;
            out << "gExchangeID: " << c.gExchangeID << std::endl;
            out << "gMdFrontAddr: " << c.gMdFrontAddr << std::endl;
            out << "instrumentNum: " << c.instrumentNum << std::endl;
            for (int i = 0; i<c.instrumentNum; i++) {
                out << c.g_pInstrumentID[i] << " ";
            }
            out << std::endl;
            out << "gTradeFrontAddr: " << c.gTradeFrontAddr << std::endl;
            out << "g_pTradeInstrumentID: " << c.g_pTradeInstrumentID << std::endl;
            out << "mode: " << c.mode << std::endl;
            out << "marketDataRamdomSeed: " << c.marketDataRamdomSeed << std::endl;
            out << "interval: " << c.interval << std::endl;
        }
};

// 初始化配置函数
// never release this pointer.
// the struct is reused by config.
Config* readConfigFromFile(const std::string & cfgFile);


}}}




