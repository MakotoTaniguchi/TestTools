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

// ���C������
void CProxyCmdService::ServiceMain()
{
	CProxyCmdThread ProxyCmdThread;
	
	ProxyCmdThread.SetCancelHandle( m_hStop );
	
	ProxyCmdThread.CreateThread();

	::WaitForSingleObject( ProxyCmdThread.GetThreadHandle(), INFINITE );
}

// �㏈�����ɂȂ�
void CProxyCmdService::ServiceStop()
{
}

// �ꎞ��~�������o���Ȃ��悤�ɂ��Ă���ׁA���ɂȂ�
void CProxyCmdService::ServicePause(){}

// �ċN�����������Ă����ɂȂ�
void CProxyCmdService::ServiceContinue(){}