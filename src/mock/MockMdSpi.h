#pragma once
// ---- 派生的行情类 ---- //
#include <vector>
#include <unordered_map>
#include "../CTP_API/inc/ThostFtdcMdApi.h"
#include "../TickToKlineHelper.h"
#include "MockMdApi.h"

namespace sail { namespace onepunch { namespace mock {

class MockMdSpi : public CThostFtdcMdSpi
{
private:
    char *gBrokerID;         // 模拟经纪商代码
    char *gInvesterID;       // 投资者账户名
    char *gInvesterPassword; // 投资者密码
    char *gExchangeID;
    char *gMdFrontAddr;     // 模拟行情前置地址
    char **g_pInstrumentID; // 行情合约代码列表，中、上、大、郑交易所各选一种
    int instrumentNum;      // 行情合约订阅数量

    std::unordered_map<std::string, TickToKlineHelper> &g_KlineHash; // 不同合约的k线存储表
    MockMdApi *g_pMdUserApi;
    // ---- 继承自CTP父类的回调接口并实现 ---- //
public:
    MockMdSpi(std::unordered_map<std::string, TickToKlineHelper> &g_KlineHash,
              char *gBrokerID,         // 模拟经纪商代码
              char *gInvesterID,       // 投资者账户名
              char *gInvesterPassword, // 投资者密码
              char *gExchangeID,
              char *gMdFrontAddr,
              char **g_pInstrumentID,
              int instrumentNum) : g_KlineHash(g_KlineHash), gBrokerID(gBrokerID),
                                   gInvesterID(gInvesterID), gInvesterPassword(gInvesterPassword),
                                   gExchangeID(gExchangeID), gMdFrontAddr(gMdFrontAddr), g_pInstrumentID(g_pInstrumentID),
                                   instrumentNum(instrumentNum){};

    void setMdUserApi(MockMdApi *g_pMdUserApi) { this->g_pMdUserApi = g_pMdUserApi; };
    ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
    void OnFrontConnected();

    ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
    ///@param nReason 错误原因
    ///        0x1001 网络读失败
    ///        0x1002 网络写失败
    ///        0x2001 接收心跳超时
    ///        0x2002 发送心跳失败
    ///        0x2003 收到错误报文
    void OnFrontDisconnected(int nReason);

    ///心跳超时警告。当长时间未收到报文时，该方法被调用。
    ///@param nTimeLapse 距离上次接收报文的时间
    void OnHeartBeatWarning(int nTimeLapse);

    ///登录请求响应
    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///登出请求响应
    void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///错误应答
    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///订阅行情应答
    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///取消订阅行情应答
    void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///订阅询价应答
    void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///取消订阅询价应答
    void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///深度行情通知
    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

    ///询价通知
    void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);
};

} // namespace mock
} // namespace onepunch
} // namespace sail