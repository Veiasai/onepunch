#pragma once
#include <string>
#include <map>
#include <ctime>

namespace simulator
{

class TradeInfo
{
private:
    static constexpr double BASEPRICE = 800;
    static constexpr long BASEVOLUME = 5000;
    static constexpr double BASEDELTA = 3;
    static constexpr long BASEDELTAVOLUME = 100;

public:
    std::string instrumentId; // 合约ID
    time_t UpdateTime;        // 上次更新时间
    double LastPrice;         // 最新价格
    long Volume;              // 成交量
    double BidPrice1;         // 申买价1
    long BidVolume1;          // 申买量1
    double AskPrice1;         // 申卖价1
    long AskVolume1;          // 申卖量1

    TradeInfo(const std::string &instrumentId) : instrumentId(instrumentId), UpdateTime(time(NULL)), LastPrice(BASEPRICE), Volume(BASEVOLUME), BidPrice1(BASEPRICE - BASEDELTA), BidVolume1(BASEDELTAVOLUME), AskPrice1(BASEPRICE + BASEDELTA), AskVolume1(BASEDELTAVOLUME) {}
};

class UserInfo
{
private:
    static constexpr double BASEAVAILABLE = 100000000;

public:
    std::string UserID;                     // 用户ID
    std::map<std::string, long> OpenVolume; // 各股持仓量
    double Available;                       // 可用资金
    double CloseProfit;                     // 平仓盈亏

    UserInfo(const std::string &userid) : UserID(userid), OpenVolume(), Available(BASEAVAILABLE), CloseProfit(0) {}
};

} // namespace simulator
