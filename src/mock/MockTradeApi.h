#pragma once
// ---- 派生的交易类 ---- //
#include "../CTP_API/inc/ThostFtdcTraderApi.h"
#include <unordered_map>
#include "../TickToKlineHelper.h"

namespace sail
{
namespace onepunch
{
namespace mock
{

class MockTraderApi : public CThostFtdcTraderApi
{
public:
    ///客户端认证请求
    int ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID) { return 0; };

    ///用户口令更新请求
    int ReqUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID) { return 0; };

    ///登出请求
    int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID) { return 0; };

    ///投资者结算结果确认
    int ReqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID);

    ///请求查询合约
    int ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID);

    ///请求查询资金账户
    int ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID);

    ///请求查询投资者持仓
    int ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID);

    ///报单录入请求
    int ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID);

    ///报单操作请求
    int ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID);
};

} // namespace mock
} // namespace onepunch
} // namespace sail