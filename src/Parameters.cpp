#include <iostream>
#include <libconfig.h++>
#include "Parameters.h"
#include <string.h>
#include <assert.h>

using namespace std;
using namespace libconfig;

namespace sail { namespace onepunch { namespace parameter {

Config* readConfigFromFile(const string & cfgFile)
{
    static Config config;
    libconfig::Config cfg;

    // Read the file. If there is an error, report it and exit.
    cfg.readFile(cfgFile.c_str());

    const Setting &root = cfg.getRoot();

    // 公共参数
    strcpy(config.gBrokerID, root["gBrokerID"].c_str());
    strcpy(config.gInvesterID, root["gInvesterID"].c_str());
    strcpy(config.gInvesterPassword, root["gInvesterPassword"].c_str());
    strcpy(config.gExchangeID, root["gExchangeID"].c_str());

    // 行情参数
    assert(root["g_pInstrumentID"].isArray());
    config.instrumentNum = root["g_pInstrumentID"].getLength();
    assert(config.instrumentNum > 0);
    config.g_pInstrumentID = new char *[config.instrumentNum];
    int i = 0;
    for (auto it = root["g_pInstrumentID"].begin(); it != root["g_pInstrumentID"].end(); ++it)
    {
        config.g_pInstrumentID[i] = new char[10];
        strcpy(config.g_pInstrumentID[i], it->c_str());
        i++;
    }
    
    strcpy(config.gMdFrontAddr, root["gMdFrontAddr"].c_str());

    // 交易参数
    strcpy(config.gTradeFrontAddr, root["gTradeFrontAddr"].c_str());
    strcpy(config.g_pTradeInstrumentID, root["g_pTradeInstrumentID"].c_str());

    // 运行模式
    // 1: CTP ; 2: simulator
    config.mode = root["mode"];
    config.marketDataRamdomSeed = root["marketDataRamdomSeed"];
    config.interval = root["interval"];
    return &config;
}

}}}