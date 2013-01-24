#include "stdafx.h"
#include "ThreadBase.h"

// コンストラクタ
CThreadBase::CThreadBase()
{
	m_hThread = NULL;
	m_hCancel = NULL;
	m_uThreadID = 0;
}

// デストラクタ
CThreadBase::~CThreadBase()
{
	Destroy( (1000 * 10) );
}

BOOL CThreadBase::Destroy( DWORD dwTimeOut /*= INFINITE*/ )
{
	DWORD dwRet = ::WaitForSingleObject( m_hThread, dwTimeOut );
	DWORD dwRetCode = 0;

	BOOL bRet = FALSE;
	switch( dwRet )
	{
		case WAIT_OBJECT_0:
			bRet = TRUE;
			break;
		case WAIT_TIMEOUT:
			TerminateThread( m_hThread, WAIT_TIMEOUT );
			bRet = FALSE;
		break;
		default:
			bRet = FALSE;
		break;
	}

	return bRet;
}

// スレッド作成
void CThreadBase::CreateThread( BOOL bStart /*= TRUE*/ )
{
	m_hThread = (HANDLE) _beginthreadex( NULL, 0, ThreadEntry, (PVOID)this, CREATE_SUSPENDED, &m_uThreadID );
	
	if( NULL != m_hThread && bStart )
	{
		ResumeThread( m_hThread );
	}
}

// スレッドのエントリポイント
UINT __stdcall CThreadBase::ThreadEntry( void* pParam )
{
	CThreadBase* pThis = (CThreadBase*)pParam;

	UINT uRet = pThis->ThreadMain();

	return uRet;
}

// スレッドメイン処理
UINT CThreadBase::ThreadMain()
{
	::WaitForSingleObject( m_hCancel, INFINITE );
	return 0;
}