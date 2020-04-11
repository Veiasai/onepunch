#pragma once
// ---- 派生的行情类 ---- //
#include <vector>
#include <unordered_map>
#include <cstring>
#include <string>
#include <thread>
#include <assert.h>
#include "../CTP_API/inc/ThostFtdcMdApi.h"
#include "DepthMarketDataGenerator.h"
#include "../OnePunchMdSpi.h"

namespace sail
{
namespace onepunch
{
namespace mock
{

class MockMdApi final : public CThostFtdcMdApi
{
private:
    ctp::OnePunchMdSpi *g_pMdUserSpi;
    char gMdFrontAddr[63];
    std::vector<std::string> instrumentIDs;
    sail::onepunch::mock::DepthMarketDataGenerator *dmdg;
    std::thread MdApiThread;
    int interval_time;

    void MdApiInit();

public:
    void setDepthMarketDataGenerator(std::unordered_map<std::string, std::vector<CThostFtdcDepthMarketDataField>> DepthMarketDataHash,const std::string &instrumentId, int marketDataRandomSeed);
    void setIntervalTime(int interval) { this->interval_time = interval; }

    ///创建MdApi
    ///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
    ///@return 创建出的UserApi
    ///modify for udp marketdata
    static MockMdApi *CreateMockMdApi();

    ///删除接口对象本身
    ///@remark 不再使用本接口对象时,调用该函数删除接口对象
    void Release() { delete dmdg; }

    ///初始化
    ///@remark 初始化运行环境,只有调用后,接口才开始工作
    void Init();

    ///等待接口线程结束运行
    ///@return 线程退出代码
    int Join();

    ///获取当前交易日
    ///@retrun 获取到的交易日
    ///@remark 只有登录成功后,才能得到正确的交易日
    const char *GetTradingDay();

    ///注册前置机网络地址
    ///@param pszFrontAddress：前置机网络地址。
    ///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。
    ///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
    void RegisterFront(char *pszFrontAddress) { memcpy(gMdFrontAddr, pszFrontAddress, 63); };

    ///注册名字服务器网络地址
    ///@param pszNsAddress：名字服务器网络地址。
    ///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。
    ///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
    ///@remark RegisterNameServer优先于RegisterFront
    void RegisterNameServer(char *pszNsAddress){};

    ///注册名字服务器用户信息
    ///@param pFensUserInfo：用户信息。
    void RegisterFensUserInfo(CThostFtdcFensUserInfoField *pFensUserInfo){};

    ///注册回调接口
    ///@param pSpi 派生自回调接口类的实例
    void RegisterSpi(CThostFtdcMdSpi *pSpi) { this->g_pMdUserSpi = (ctp::OnePunchMdSpi *)pSpi; };

    ///订阅行情。
    ///@param ppInstrumentID 合约ID
    ///@param nCount 要订阅/退订行情的合约个数
    ///@remark
    int SubscribeMarketData(char *ppInstrumentID[], int nCount);

    ///退订行情。
    ///@param ppInstrumentID 合约ID
    ///@param nCount 要订阅/退订行情的合约个数
    ///@remark
    int UnSubscribeMarketData(char *ppInstrumentID[], int nCount);

    ///订阅询价。
    ///@param ppInstrumentID 合约ID
    ///@param nCount 要订阅/退订行情的合约个数
    ///@remark
    int SubscribeForQuoteRsp(char *ppInstrumentID[], int nCount) { assert(0); };

    ///退订询价。
    ///@param ppInstrumentID 合约ID
    ///@param nCount 要订阅/退订行情的合约个数
    ///@remark
    int UnSubscribeForQuoteRsp(char *ppInstrumentID[], int nCount) { assert(0); };

    ///用户登录请求
    int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID) { return 0; };

    ///登出请求
    int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID) { return 0; };

    ///请求查询组播合约
    int ReqQryMulticastInstrument(CThostFtdcQryMulticastInstrumentField *pQryMulticastInstrument, int nRequestID) { return 0; };
};

} // namespace mock
} // namespace onepunch
} // namespace sail