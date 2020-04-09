#pragma once
// ---- 派生的行情类 ---- //
#include <vector>
#include <unordered_map>
#include "../CTP_API/inc/ThostFtdcMdApi.h"
#include "../TickToKlineHelper.h"

namespace sail
{
namespace onepunch
{
namespace mock
{

class MockMdApi : public CThostFtdcMdApi
{
public:
    ///用户登录请求
    int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID) { return 0; };

    ///订阅行情。
    ///@param ppInstrumentID 合约ID
    ///@param nCount 要订阅/退订行情的合约个数
    ///@remark
    int SubscribeMarketData(char *ppInstrumentID[], int nCount) { return 0; };
};

} // namespace mock
} // namespace onepunch
} // namespace sail