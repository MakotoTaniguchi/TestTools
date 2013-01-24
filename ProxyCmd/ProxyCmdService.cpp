#include "stdafx.h"
#include "ProxyCmdService.h"

#include "ProxyCmdThread.h"

#include "wtsapi32.h"
#pragma comment(lib, "wtsapi32.lib")

#include "userenv.h"
#pragma comment(lib, "userenv.lib")

CProxyCmdService::CProxyCmdService()
{
	m_hStop = NULL;
}

CProxyCmdService::~CProxyCmdService()
{
}

void CProxyCmdService::ServiceOpen( HANDLE hStop )
{
	m_hStop = hStop;
}

void CProxyCmdService::ServiceClose()
{
}

// メイン処理
void CProxyCmdService::ServiceMain()
{
	CProxyCmdThread ProxyCmdThread;
	
	ProxyCmdThread.SetCancelHandle( m_hStop );
	
	ProxyCmdThread.CreateThread();

	::WaitForSingleObject( ProxyCmdThread.GetThreadHandle(), INFINITE );
}

// 後処理特になし
void CProxyCmdService::ServiceStop()
{
}

// 一時停止を押下出来ないようにしている為、特になし
void CProxyCmdService::ServicePause(){}

// 再起動を押下しても特になし
void CProxyCmdService::ServiceContinue(){}