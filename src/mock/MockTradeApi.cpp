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
MockTraderApi *MockTraderApi::CreateMockTraderApi()
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

///请求查询投资者持仓
int MockTraderApi::ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID)
{
    // 持仓情况
    if (InvestorPosition.find(this->instrumentIDs[0]) == InvestorPosition.end())
    {
        CThostFtdcInvestorPositionField cf = CThostFtdcInvestorPositionField();
        strcpy(cf.InstrumentID, this->instrumentIDs[0]);
        InvestorPosition[this->instrumentIDs[0]] = cf;
    }

    this->pTradeSpi->OnRspQryInvestorPosition(&InvestorPosition[this->instrumentIDs[0]], nullptr, 0, 0);
    return 0;
}

void MockTraderApi::TraderInit()
{
    // 初始化投资者账户
    this->pTradingAccount = new CThostFtdcTradingAccountField();
    strcpy(this->pTradingAccount->AccountID, "accountId");
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

    // 持仓情况
    if (InvestorPosition.find(this->instrumentIDs[0]) == InvestorPosition.end())
    {
        CThostFtdcInvestorPositionField cf = CThostFtdcInvestorPositionField();
        strcpy(cf.InstrumentID, this->instrumentIDs[0]);
        InvestorPosition[this->instrumentIDs[0]] = cf;
    }

    this->pTradeSpi->OnRspQryInvestorPosition(&InvestorPosition[this->instrumentIDs[0]], nullptr, 0, 0);
}

///报单录入请求
int MockTraderApi::ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID)
{
    CThostFtdcInvestorPositionField cf = this->InvestorPosition[pInputOrder->InstrumentID];
    double vol = pInputOrder->VolumeTotalOriginal;
    double price = pInputOrder->LimitPrice;
    if (pInputOrder->Direction == THOST_FTDC_D_Sell)
        vol = -vol;

    if (vol + cf.OpenVolume == 0)
    {
        cf.OpenAmount = 0;
        cf.OpenVolume = 0;
    }
    else
    {
        cf.OpenAmount = (cf.OpenAmount * cf.OpenVolume + price * vol) / (cf.OpenVolume + vol);
        cf.OpenVolume += vol;
    }
    this->InvestorPosition[pInputOrder->InstrumentID] = cf;
    this->pTradeSpi->OnRspOrderInsert(pInputOrder, nullptr, nRequestID, 0);
    return 0;
};

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