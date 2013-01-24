#include "stdafx.h"
#include "ProxyCmdThread.h"

#include "wtsapi32.h"
#pragma comment(lib, "wtsapi32.lib")

#include "userenv.h"
#pragma comment(lib, "userenv.lib")

CProxyCmdThread::CProxyCmdThread()
{
	m_hCancel = NULL;
	m_PipeBase.CreatePipeServerSide();
}

CProxyCmdThread::~CProxyCmdThread()
{
	m_PipeBase.ClosePipe();
}

// メイン処理
UINT CProxyCmdThread::ThreadMain()
{
	TCHAR lpzExePath[MAX_PATH] = _T("");
	m_PipeBase.SetEvent( m_hCancel );
	m_PipeBase.ReadPipeServerSide( lpzExePath );

	if ( 0 != _tcsicmp( _T(""), lpzExePath ) )
	{
		PROCESS_INFORMATION pi;
		STARTUPINFO si;
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE;
		si.lpDesktop = _T("winsta0\\default");

		ZeroMemory(&si,sizeof(si));
		si.cb=sizeof(si);

		OSVERSIONINFO osVer;
		//構造体のサイズを求めてdwOSVersionInfoSizeに格納
		osVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		::GetVersionEx( &osVer );

		// MajorVerが5以下はXPなのでSession0は関係ないのでCreateProcessで起動する
		if( 6 > osVer.dwMajorVersion )
		{
			::CreateProcess( NULL, lpzExePath, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
		}

		// このプロセスのトークン取得
		HANDLE hProcessToken = NULL;
		BOOL bRet = ::OpenProcessToken( ::GetCurrentProcess(), 
											(TOKEN_QUERY|TOKEN_DUPLICATE|TOKEN_ADJUST_SESSIONID), 
											&hProcessToken);
		if(!bRet)
		{
			::MessageBox( NULL, _T("ユーザトークンのオープンに失敗"), _T("Error"), MB_OK );
			ASSERT(0);
		}

		// トークンの複製
		HANDLE hCamouflage = NULL;
		bRet = ::DuplicateTokenEx( hProcessToken, MAXIMUM_ALLOWED, NULL, SecurityImpersonation, TokenPrimary, &hCamouflage );
		if(!bRet)
		{
			::MessageBox( NULL, _T("トークン複製に失敗"), _T("Error"), MB_OK );
			ASSERT(0);
		}
		
		
		// ログオンしているユーザのトークン取得
		HANDLE hLogOnUserToken = NULL;
		DWORD dwSessionID = WTSQueryUserToken( WTSGetActiveConsoleSessionId(), &hLogOnUserToken );

		::SetTokenInformation( hCamouflage, TokenSessionId, &dwSessionID, sizeof(dwSessionID) );
		if(!bRet)
		{
			::MessageBox( NULL, _T("SessionID情報設定に失敗"), _T("Error"), MB_OK );
			ASSERT(0);
		}

		LPVOID lpEnvironment = NULL;
		bRet = ::CreateEnvironmentBlock( &lpEnvironment, hLogOnUserToken, FALSE );
		if(!bRet)
		{
			::MessageBox( NULL, _T("環境変数設定失敗"), _T("Error"), MB_OK );
			ASSERT(0);
		}

		::CreateProcessAsUser( hCamouflage, NULL, lpzExePath, NULL, NULL, TRUE, 
								NORMAL_PRIORITY_CLASS | CREATE_UNICODE_ENVIRONMENT, lpEnvironment, NULL, &si, &pi);
		DestroyEnvironmentBlock(lpEnvironment);

		return TRUE;
	}

	return FALSE;
}
