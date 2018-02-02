

#include "./v1.0_20160628_api_tradeapi_linux64/ThostFtdcMdApi.h"
#include "./md/MdSpi.h"
#include <iostream>
#pragma comment(lib, "thostmduserapi")
#pragma comment(lib, "thosttraderapi")
// UserApi对象
CThostFtdcMdApi* md_pUserApi;

// 配置参数
char MD_FRONT_ADDR[] = "tcp://116.246.40.193:61823";		// 前置地址
TThostFtdcBrokerIDType	BROKER_ID = "2000";				// 经纪公司代码
TThostFtdcInvestorIDType INVESTOR_ID = "496";			// 投资者代码
TThostFtdcPasswordType  PASSWORD = "496";			// 用户密码
char *md_ppInstrumentID[] = { const_cast<char*>("600000"), const_cast<char*>("10001218"), const_cast<char*>("10001217"), };			// 行情订阅列表
int md_iInstrumentID = 3;									// 行情订阅数量

// 请求编号
int md_iRequestID = 0;

int main(void)
{
    // 初始化UserApi
    md_pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();			// 创建UserApi
    CThostFtdcMdSpi* md_pUserSpi = new CMdSpi();
    md_pUserApi->RegisterSpi(md_pUserSpi);						// 注册事件类
    md_pUserApi->RegisterFront(MD_FRONT_ADDR);					// connect
    md_pUserApi->Init();

    md_pUserApi->Join();
    //	md_pUserApi->Release();
    return 0;
}