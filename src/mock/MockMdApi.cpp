#include <ctime>
#include <algorithm>

#include "MockMdApi.h"

namespace sail
{
namespace onepunch
{
namespace mock
{
void MockMdApi::setDepthMarketDataGenerator(const std::string &instrumentId, int marketDataRandomSeed)
{
    dmdg = new DepthMarketDataGenerator(DepthMarketDataHash, instrumentId, marketDataRandomSeed);
}

///创建MdApi
///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
///@return 创建出的UserApi
///modify for udp marketdata
MockMdApi * MockMdApi::CreateMockMdApi()
{
    static MockMdApi singleton;
    return &singleton;
}

///获取当前交易日
///@retrun 获取到的交易日
///@remark 只有登录成功后,才能得到正确的交易日
const char *MockMdApi::GetTradingDay()
{
    time_t now = time(0);
    return ctime(&now);
};

void MockMdApi::MdApiInit()
{
    // 设置前置地址
    g_pMdUserSpi->OnFrontConnected();

    // 订阅合约
    std::cout << "=====账户登录成功=====" << std::endl;
    std::cout << "登录时间： " << GetTradingDay() << std::endl;
    std::cout << ">>>>>>发送订阅行情请求成功" << std::endl;

    // 订阅行情应答
    CThostFtdcSpecificInstrumentField *pSpecificInstrument = new CThostFtdcSpecificInstrumentField();
    memcpy(pSpecificInstrument->InstrumentID, &instrumentIDs[0], 32);
    CThostFtdcRspInfoField *pRspInfo = new CThostFtdcRspInfoField();
    pRspInfo->ErrorID = 0;
    g_pMdUserSpi->OnRspSubMarketData(pSpecificInstrument, pRspInfo, 0, 0);

    while (1)
    {
        // 获得深度行情
        dmdg->poll(1);
        auto a = DepthMarketDataHash[instrumentIDs[0]];
        g_pMdUserSpi->OnRtnDepthMarketData(&a[a.size() - 1]);
        std::this_thread::sleep_for(std::chrono::seconds(this->interval_time));
    }
}

///初始化
///@remark 初始化运行环境,只有调用后,接口才开始工作
void MockMdApi::Init()
{
    MdApiThread = std::thread(std::bind(&MockMdApi::MdApiInit, this));
}

///等待接口线程结束运行
///@return 线程退出代码
int MockMdApi::Join()
{
    MdApiThread.join();
}

///订阅行情。
///@param ppInstrumentID 合约ID
///@param nCount 要订阅/退订行情的合约个数
///@remark
int MockMdApi::SubscribeMarketData(char *ppInstrumentID[], int nCount)
{
    for (int i = 0; i < nCount; i++)
        instrumentIDs.push_back(ppInstrumentID[i]);

    return 0;
}

///退订行情。
///@param ppInstrumentID 合约ID
///@param nCount 要订阅/退订行情的合约个数
///@remark
int MockMdApi::UnSubscribeMarketData(char *ppInstrumentID[], int nCount)
{
    for (int i = 0; i < nCount; i++)
    {
        std::string s = ppInstrumentID[i];
        auto it = find(instrumentIDs.begin(), instrumentIDs.end(), s);
        if (it != instrumentIDs.end())
            instrumentIDs.erase(it);
        else
            return 1;
    }

    return 0;
}

} // namespace mock
} // namespace onepunch
} // namespace sail