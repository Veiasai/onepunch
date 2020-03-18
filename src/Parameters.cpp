#include <iostream>
#include <libconfig.h++>
#include "Parameters.h"
#include <string.h>

using namespace std;
using namespace libconfig;

// ---- 全局变量定义 ---- //
// 公共参数
TThostFtdcBrokerIDType gBrokerID = "";         // 模拟经纪商代码
TThostFtdcInvestorIDType gInvesterID = "";     // 投资者账户名
TThostFtdcPasswordType gInvesterPassword = ""; // 投资者密码
TThostFtdcExchangeIDType gExchangeID = "";

// 行情参数
CThostFtdcMdApi *g_pMdUserApi = nullptr;              // 行情指针
char gMdFrontAddr[63] = "";                           // 模拟行情前置地址
char *g_pInstrumentID[] = {"i2003"};                  // 行情合约代码列表，中、上、大、郑交易所各选一种
int instrumentNum = 1;                                // 行情合约订阅数量
unordered_map<string, TickToKlineHelper> g_KlineHash; // 不同合约的k线存储表

// 交易参数
CThostFtdcTraderApi *g_pTradeUserApi = nullptr;              // 交易指针
char gTradeFrontAddr[63] = "";                               // 模拟交易前置地址
TThostFtdcInstrumentIDType g_pTradeInstrumentID = "";        // 所交易的合约代码
TThostFtdcDirectionType gTradeDirection = THOST_FTDC_D_Sell; // 买卖方向
TThostFtdcPriceType gLimitPrice = 700;                       // 交易价格

// 1:CTP  2:simulator
int mode = 2;

int initConfig()
{

    Config cfg;

    // Read the file. If there is an error, report it and exit.
    try
    {
        cfg.readFile("./config/ctpconfig.cfg");
    }
    catch (const FileIOException &fioex)
    {
        cerr << "I/O error while reading file." << endl;
        return (EXIT_FAILURE);
    }
    catch (const ParseException &pex)
    {
        cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
             << " - " << pex.getError() << endl;
        return (EXIT_FAILURE);
    }

    const Setting &root = cfg.getRoot();

    // 公共参数
    string gBrokerID_c = root["gBrokerID"];
    string gInvesterID_c = root["gInvesterID"];
    string gInvesterPassword_c = root["gInvesterPassword"];
    string gExchangeID_c = root["gExchangeID"];

    strcpy(gBrokerID, gBrokerID_c.c_str());
    strcpy(gInvesterID, gInvesterID_c.c_str());
    strcpy(gInvesterPassword, gInvesterPassword_c.c_str());
    strcpy(gExchangeID, gExchangeID_c.c_str());

    // 行情参数
    string gMdFrontAddr_c = root["gMdFrontAddr"];
    instrumentNum = root["instrumentNum"];

    strcpy(gMdFrontAddr, gMdFrontAddr_c.c_str());

    // 交易参数
    string gTradeFrontAddr_c = root["gTradeFrontAddr"];
    string g_pTradeInstrumentID_c = root["g_pTradeInstrumentID"];
    strcpy(gTradeFrontAddr, gTradeFrontAddr_c.c_str());
    strcpy(g_pTradeInstrumentID, g_pTradeInstrumentID_c.c_str());

    // 运行模式
    // 1: CTP ; 2: simulator
    mode = root["mode"];

    return EXIT_SUCCESS;
}
