#pragma once
#include "ThostFtdcMdApi.h"

class CMdSpi : public CThostFtdcMdSpi
{
public:
	///???????
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo,
		int nRequestID, bool bIsLast);

	///??????????????????????????��????????��???????????????API???????????????????????????
	///@param nReason ???????
	///        0x1001 ????????
	///        0x1002 ????��???
	///        0x2001 ???????????
	///        0x2002 ???????????
	///        0x2003 ?????????
	virtual void OnFrontDisconnected(int nReason);

	///??????????��???????��???????????��????????��?
	///@param nTimeLapse ??????��??????????
	virtual void OnHeartBeatWarning(int nTimeLapse);

	///???????????????????????????????��?????????��????????��?
	virtual void OnFrontConnected();

	///??????????
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///???????????
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///??????????????
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///?????????
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

private:
	void ReqUserLogin();
	void SubscribeMarketData();
	// 
	bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
};