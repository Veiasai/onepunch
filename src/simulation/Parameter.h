#pragma once
#include <string>
#include <ctime>

namespace simulator
{

class TradeInfo
{
private:
    const double BASEPRICE = 800;
    long double BASEVOLUME = 5000;
    const double BASEDELTA = 3;
    long double BASEDELTAVOLUME = 100;

public:
    std::string instrumentId; // 合约ID
    time_t UpdateTime;        // 上次更新时间
    double LastPrice;         // 最新价格
    long Volume;              // 成交量
    double BidPrice1;         // 申买价1
    long BidVolume1;          // 申买量1
    double AskPrice1;         // 申卖价1
    long AskVolume1;          // 申卖量1

    TradeInfo(std::string instrumentId) : instrumentId(instrumentId), UpdateTime(time(NULL)), LastPrice(BASEPRICE), Volume(BASEVOLUME), BidPrice1(BASEPRICE - BASEDELTA), BidVolume1(BASEDELTAVOLUME), AskPrice1(BASEPRICE + BASEDELTA), AskVolume1(BASEDELTAVOLUME) {}
};

class UserInfo
{
private:
    const double BASEAVAILABLE = 100000000;

public:
    std::string UserID; // 用户ID
    long OpenVolume;    // 持仓量
    double Available;   // 可用资金
    double CloseProfit; // 平仓盈亏

    UserInfo(std::string userid) : UserID(userid), OpenVolume(0), Available(BASEAVAILABLE), CloseProfit(0) {}
};

} // namespace simulator
