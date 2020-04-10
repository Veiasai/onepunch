#include <ctime>
#include <iostream>

#include "MockTradeApi.h"

namespace sail
{
namespace onepunch
{
namespace mock
{

///创建TraderApi
///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
///@return 创建出的UserApi
static MockTraderApi *CreateMockTraderApi()
{
    static MockTraderApi singleton;
    return &singleton;
}

///获取当前交易日
///@retrun 获取到的交易日
///@remark 只有登录成功后,才能得到正确的交易日
const char *MockTraderApi::GetTradingDay()
{
    time_t now = time(0);
    return ctime(&now);
}

void MockTraderApi::TraderInit()
{
    // 初始化投资者账户
    this->pTradingAccount = new CThostFtdcTradingAccountField();
    memcpy(this->pTradingAccount->AccountID, "accountId", 10);
    this->pTradingAccount->Available = 1000000.0;
    this->pTradingAccount->WithdrawQuota = 1000000.0;
    this->pTradingAccount->CurrMargin = 100;
    this->pTradingAccount->CloseProfit = 0;

    // 初始化持仓情况
    this->InvestorPosition = {};

    // 建立网络与认证
    this->pTradeSpi->OnFrontConnected();
    this->pTradeSpi->OnRspAuthenticate(nullptr, nullptr, 0, 0);
    std::cout << "=====账户登录成功=====" << std::endl;

    // 查询投资者资金账户
    this->pTradeSpi->OnRspQryTradingAccount(this->pTradingAccount, nullptr, 0, 0);
    // this->pTradeSpi->OnRspQryInvestorPosition()
}

///初始化
///@remark 初始化运行环境,只有调用后,接口才开始工作
void MockTraderApi::Init()
{
    this->traderThread = std::thread(std::bind(&MockTraderApi::TraderInit, this));
}

///等待接口线程结束运行
///@return 线程退出代码
int MockTraderApi::Join()
{
    this->traderThread.join();
}

} // namespace mock
} // namespace onepunch
} // namespace sail