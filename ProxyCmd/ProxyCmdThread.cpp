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

// ���C������
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
		//�\���̂̃T�C�Y�����߂�dwOSVersionInfoSize�Ɋi�[
		osVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		::GetVersionEx( &osVer );

		// MajorVer��5�ȉ���XP�Ȃ̂�Session0�͊֌W�Ȃ��̂�CreateProcess�ŋN������
		if( 6 > osVer.dwMajorVersion )
		{
			::CreateProcess( NULL, lpzExePath, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
		}

		// ���̃v���Z�X�̃g�[�N���擾
		HANDLE hProcessToken = NULL;
		BOOL bRet = ::OpenProcessToken( ::GetCurrentProcess(), 
											(TOKEN_QUERY|TOKEN_DUPLICATE|TOKEN_ADJUST_SESSIONID), 
											&hProcessToken);
		if(!bRet)
		{
			::MessageBox( NULL, _T("���[�U�g�[�N���̃I�[�v���Ɏ��s"), _T("Error"), MB_OK );
			ASSERT(0);
		}

		// �g�[�N���̕���
		HANDLE hCamouflage = NULL;
		bRet = ::DuplicateTokenEx( hProcessToken, MAXIMUM_ALLOWED, NULL, SecurityImpersonation, TokenPrimary, &hCamouflage );
		if(!bRet)
		{
			::MessageBox( NULL, _T("�g�[�N�������Ɏ��s"), _T("Error"), MB_OK );
			ASSERT(0);
		}
		
		
		// ���O�I�����Ă��郆�[�U�̃g�[�N���擾
		HANDLE hLogOnUserToken = NULL;
		DWORD dwSessionID = WTSQueryUserToken( WTSGetActiveConsoleSessionId(), &hLogOnUserToken );

		::SetTokenInformation( hCamouflage, TokenSessionId, &dwSessionID, sizeof(dwSessionID) );
		if(!bRet)
		{
			::MessageBox( NULL, _T("SessionID���ݒ�Ɏ��s"), _T("Error"), MB_OK );
			ASSERT(0);
		}

		LPVOID lpEnvironment = NULL;
		bRet = ::CreateEnvironmentBlock( &lpEnvironment, hLogOnUserToken, FALSE );
		if(!bRet)
		{
			::MessageBox( NULL, _T("���ϐ��ݒ莸�s"), _T("Error"), MB_OK );
			ASSERT(0);
		}

		::CreateProcessAsUser( hCamouflage, NULL, lpzExePath, NULL, NULL, TRUE, 
								NORMAL_PRIORITY_CLASS | CREATE_UNICODE_ENVIRONMENT, lpEnvironment, NULL, &si, &pi);
		DestroyEnvironmentBlock(lpEnvironment);

		return TRUE;
	}

	return FALSE;
}
