
#include "MdSpi.h"
#include <iostream>
#include <string.h>

#include <stdio.h>
#include <iostream>
#include <thread>

using namespace std;

#include <iostream>
#include <chrono>
#include <ratio>
#include <ctime>
//#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include <unistd.h>
#include <fstream>

using namespace std;

#pragma warning(disable : 4996)

// USER_API????
extern CThostFtdcMdApi *md_pUserApi;

// ???¨°???
extern char MD_FRONT_ADDR[];
extern TThostFtdcBrokerIDType BROKER_ID;
extern TThostFtdcInvestorIDType INVESTOR_ID;
extern TThostFtdcPasswordType PASSWORD;
extern char *md_ppInstrumentID[];
extern int md_iInstrumentID;

// ??????
extern int md_iRequestID;

void CMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo,
                        int nRequestID, bool bIsLast) {
    cerr << "--->>> " << "OnRspError" << endl;
    IsErrorRspInfo(pRspInfo);
}

void CMdSpi::OnFrontDisconnected(int nReason) {
    cerr << "--->>> " << "OnFrontDisconnected" << endl;
    cerr << "--->>> Reason = " << nReason << endl;
}

void CMdSpi::OnHeartBeatWarning(int nTimeLapse) {
    cerr << "--->>> " << "OnHeartBeatWarning" << endl;
    cerr << "--->>> nTimerLapse = " << nTimeLapse << endl;
}

void CMdSpi::OnFrontConnected() {
    cerr << "--->>> " << "OnFrontConnected" << endl;
    ///??????????
    ReqUserLogin();
}

void CMdSpi::ReqUserLogin() {
    CThostFtdcReqUserLoginField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, BROKER_ID);
    strcpy(req.UserID, INVESTOR_ID);
    strcpy(req.Password, PASSWORD);
    int iResult = md_pUserApi->ReqUserLogin(&req, ++md_iRequestID);
    cerr << "--->>> ??????????????: " << ((iResult == 0) ? "???" : "???") << endl;
}

void CMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                            CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    cerr << "--->>> " << "OnRspUserLogin" << endl;
    if (bIsLast && !IsErrorRspInfo(pRspInfo)) {
        ///????????????
        cerr << "--->>> ???????????? = " << md_pUserApi->GetTradingDay() << endl;
        // ??????????
        SubscribeMarketData();
    }
}

void CMdSpi::SubscribeMarketData() {
    int iResult = md_pUserApi->SubscribeMarketData(md_ppInstrumentID, md_iInstrumentID);
    cerr << "--->>> ???????úF??????: " << ((iResult == 0) ? "???" : "???") << endl;
}

void
CMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo,
                           int nRequestID, bool bIsLast) {
    cerr << "OnRspSubMarketData" << endl;
}

void
CMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo,
                             int nRequestID, bool bIsLast) {
    cerr << "OnRspUnSubMarketData" << endl;
}

//struct CThostFtdcDepthMarketDataField
//{
//	///??????
//	TThostFtdcDateType	TradingDay;
//	///???????
//	TThostFtdcInstrumentIDType	InstrumentID;
//	///??????????
//	TThostFtdcExchangeIDType	ExchangeID;
//	///???????????????
//	TThostFtdcExchangeInstIDType	ExchangeInstID;
//	///?????
//	TThostFtdcPriceType	LastPrice;
//	///??¦Í????
//	TThostFtdcPriceType	PreSettlementPrice;
//	///??????
//	TThostFtdcPriceType	PreClosePrice;
//	///??????
//	TThostFtdcLargeVolumeType	PreOpenInterest;
//	///????
//	TThostFtdcPriceType	OpenPrice;
//	///????
//	TThostFtdcPriceType	HighestPrice;
//	///????
//	TThostFtdcPriceType	LowestPrice;
//	///????
//	TThostFtdcVolumeType	Volume;
//	///??????
//	TThostFtdcMoneyType	Turnover;
//	///?????
//	TThostFtdcLargeVolumeType	OpenInterest;
//	///??????
//	TThostFtdcPriceType	ClosePrice;
//	///???¦Í????
//	TThostFtdcPriceType	SettlementPrice;
//	///??????
//	TThostFtdcPriceType	UpperLimitPrice;
//	///??????
//	TThostFtdcPriceType	LowerLimitPrice;
//	///???????
//	TThostFtdcRatioType	PreDelta;
//	///???????
//	TThostFtdcRatioType	CurrDelta;
//	///?????????
//	TThostFtdcTimeType	UpdateTime;
//	///?????????
//	TThostFtdcMillisecType	UpdateMillisec;
//	///??????
//	TThostFtdcPriceType	BidPrice1;
//	///???????
//	TThostFtdcVolumeType	BidVolume1;
//	///???????
//	TThostFtdcPriceType	AskPrice1;
//	///???????
//	TThostFtdcVolumeType	AskVolume1;
//	///??????
//	TThostFtdcPriceType	BidPrice2;
//	///????????
//	TThostFtdcVolumeType	BidVolume2;
//	///???????
//	TThostFtdcPriceType	AskPrice2;
//	///????????
//	TThostFtdcVolumeType	AskVolume2;
//	///???????
//	TThostFtdcPriceType	BidPrice3;
//	///????????
//	TThostFtdcVolumeType	BidVolume3;
//	///????????
//	TThostFtdcPriceType	AskPrice3;
//	///????????
//	TThostFtdcVolumeType	AskVolume3;
//	///???????
//	TThostFtdcPriceType	BidPrice4;
//	///????????
//	TThostFtdcVolumeType	BidVolume4;
//	///????????
//	TThostFtdcPriceType	AskPrice4;
//	///????????
//	TThostFtdcVolumeType	AskVolume4;
//	///???????
//	TThostFtdcPriceType	BidPrice5;
//	///????????
//	TThostFtdcVolumeType	BidVolume5;
//	///????????
//	TThostFtdcPriceType	AskPrice5;
//	///????????
//	TThostFtdcVolumeType	AskVolume5;
//	///???????
//	TThostFtdcPriceType	AveragePrice;
//	///???????
//	TThostFtdcDateType	ActionDay;
//};
long long get_nanosecond_pivot() {
    auto now = chrono::high_resolution_clock::now();

    auto timeMillis = chrono::duration_cast<chrono::nanoseconds>(now.time_since_epoch()).count();
    long long t_nana_secs = timeMillis;
    return t_nana_secs;
}

void wirte_DepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
    auto nano_secs = get_nanosecond_pivot();
//    cerr << "OnRtnDepthMarketData" << endl;
    cout << " nano_secs: " << nano_secs;

    std::ofstream ofs;
//    ofs.open("test.txt", std::ofstream::out | std::ofstream::app);
    bool write_header = false;
    ifstream f("example.csv");
    if(f.good())
    {
        write_header = false;
    } else
    {
        write_header = true;
    }

    ofs.open("example.csv", std::ofstream::out | std::ofstream::app);

    if(write_header)
    {
        ofs << "NanoSeconds" << ", "
            << "TradingDay" << ", "
            << "InstrumentID" << ", "
            << "ExchangeID" << ", "
            << "ExchangeInstID" << ", "
            << "LastPrice" << ", "
            << "PreSettlementPrice" << ", "
            << "PreClosePrice" << ", "
            << "PreOpenInterest" << ", "
            << "OpenPrice" << ", "
            << "HighestPrice" << ", "
            << "LowestPrice" << ", "
            << "Volume" << ", "
            << "Turnover" << ", "
            << "OpenInterest" << ", "
            << "ClosePrice" << ", "
            << "SettlementPrice" << ", "
            << "UpperLimitPrice" << ", "
            << "LowerLimitPrice" << ", "
            << "PreDelta" << ", "
            << "CurrDelta" << ", "
            << "UpdateTime" << ", "
            << "UpdateMillisec" << ", "
            << "BidPrice1" << ", "
            << "BidVolume1" << ", "
            << "AskPrice1" << ", "
            << "AskVolume1" << ", "
            << "BidPrice2" << ", "
            << "BidVolume2" << ", "
            << "AskPrice2" << ", "
            << "AskVolume2" << ", "
            << "BidPrice3" << ", "
            << "BidVolume3" << ", "
            << "AskPrice3" << ", "
            << "AskVolume3" << ", "
            << "BidPrice4" << ", "
            << "BidVolume4" << ", "
            << "AskPrice4" << ", "
            << "AskVolume4" << ", "
            << "BidPrice5" << ", "
            << "BidVolume5" << ", "
            << "AskPrice5" << ", "
            << "AskVolume5" << ", "
            << "AveragePrice" << ", "
            << "ActionDay" << ", "
            << endl;

    }
    ofs << nano_secs << ", "
        << pDepthMarketData->TradingDay << ", "
        << pDepthMarketData->InstrumentID << ", "
        << pDepthMarketData->ExchangeID << ", "
        << pDepthMarketData->ExchangeInstID << ", "
        << pDepthMarketData->LastPrice << ", "
        << pDepthMarketData->PreSettlementPrice << ", "
        << pDepthMarketData->PreClosePrice << ", "
        << pDepthMarketData->PreOpenInterest << ", "
        << pDepthMarketData->OpenPrice << ", "
        << pDepthMarketData->HighestPrice << ", "
        << pDepthMarketData->LowestPrice << ", "
        << pDepthMarketData->Volume << ", "
        << pDepthMarketData->Turnover << ", "
        << pDepthMarketData->OpenInterest << ", "
        << pDepthMarketData->ClosePrice << ", "
        << pDepthMarketData->SettlementPrice << ", "
        << pDepthMarketData->UpperLimitPrice << ", "
        << pDepthMarketData->LowerLimitPrice << ", "
        << pDepthMarketData->PreDelta << ", "
        << pDepthMarketData->CurrDelta << ", "
        << pDepthMarketData->UpdateTime << ", "
        << pDepthMarketData->UpdateMillisec << ", "
        << pDepthMarketData->BidPrice1 << ", "
        << pDepthMarketData->BidVolume1 << ", "
        << pDepthMarketData->AskPrice1 << ", "
        << pDepthMarketData->AskVolume1 << ", "
        << pDepthMarketData->BidPrice2 << ", "
        << pDepthMarketData->BidVolume2 << ", "
        << pDepthMarketData->AskPrice2 << ", "
        << pDepthMarketData->AskVolume2 << ", "
        << pDepthMarketData->BidPrice3 << ", "
        << pDepthMarketData->BidVolume3 << ", "
        << pDepthMarketData->AskPrice3 << ", "
        << pDepthMarketData->AskVolume3 << ", "
        << pDepthMarketData->BidPrice4 << ", "
        << pDepthMarketData->BidVolume4 << ", "
        << pDepthMarketData->AskPrice4 << ", "
        << pDepthMarketData->AskVolume4 << ", "
        << pDepthMarketData->BidPrice5 << ", "
        << pDepthMarketData->BidVolume5 << ", "
        << pDepthMarketData->AskPrice5 << ", "
        << pDepthMarketData->AskVolume5 << ", "
        << pDepthMarketData->AveragePrice << ", "
        << pDepthMarketData->ActionDay << ", "
        << endl;
    ofs.close();
}

void CMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
    wirte_DepthMarketData(pDepthMarketData);
    auto nano_secs = get_nanosecond_pivot();
    cerr << "OnRtnDepthMarketData" << endl;
    cout << " nano_secs: " << nano_secs;
    cout << pDepthMarketData->TradingDay
         << " UpdateTime: " << pDepthMarketData->UpdateTime
         << " UpdateMillisec: " << pDepthMarketData->UpdateMillisec
         << " ActionDay: " << pDepthMarketData->ActionDay
         << " Turnover: " << pDepthMarketData->Turnover
         << " Volume: " << pDepthMarketData->Volume
         << " LastPrice: " << pDepthMarketData->LastPrice
         << " InstrumentID: " << pDepthMarketData->InstrumentID
         //		 << " InstrumentID: " << pDepthMarketData->
         << " InstrumentID: " << pDepthMarketData->InstrumentID << endl;

//    auto nano_secs = get_nanosecond_pivot()


}

bool CMdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo) {
    // ???ErrorID != 0, ???????????????
    bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
    if (bResult)
        cerr << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
    return bResult;
}