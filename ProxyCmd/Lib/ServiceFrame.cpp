#include "stdafx.h"
#include "ServiceFrame.h"
#include "PipeBase.h"

// ���Ԃ̎擾
CServiceFrame* CServiceFrame::GetInstance()
{
	static CServiceFrame ServiceFrame;
	return &ServiceFrame;
}

// �R���X�g���N�^
CServiceFrame::CServiceFrame()
{
	m_hServiceMgr = ::OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );
	m_strServiceName = _T("");
	m_pServiceHelper = NULL;
	m_hService = NULL;
	m_hCancel = NULL;
	m_hCancel = ::CreateEvent( NULL, FALSE, FALSE, _T("ServiceFrame") );
}

// �f�X�g���N�^
CServiceFrame::~CServiceFrame()
{
	if( m_hServiceMgr )
	{
		::CloseServiceHandle( m_hServiceMgr );
		m_hService = NULL;
	}
	if( m_hService )
	{
		::CloseServiceHandle( m_hService );
		m_hService = NULL;
	}

	if( m_hCancel )
	{
		::CloseHandle( m_hCancel );
		m_hService = NULL;
	}
}

// �T�[�r�X�쐬
BOOL CServiceFrame::Install( LPTSTR lpsServiceName, LPTSTR lpsServiceDispName, LPTSTR lpsCmdLine, BOOL bStart/* = FALSE*/ )
{
	BOOL bRet = TRUE;

	if( 0 == _tcscmp( _T(""), lpsServiceName ) )
	{
		::MessageBox( NULL, _T("�T�[�r�X�������͂���Ă��܂���"), _T("�G���["),MB_OK );
		return false;
	}

	if( 0 == _tcscmp( _T(""), lpsServiceDispName ) )
	{
		::MessageBox( NULL, _T("�T�[�r�X�\���������͂���Ă��܂���"), _T("�G���["),MB_OK );
		return false;
	}

	if( 0 == _tcscmp( _T(""), lpsCmdLine ) )
	{
		::MessageBox( NULL, _T("�R�}���h���C�������͂���Ă��܂���"), _T("�G���["),MB_OK );
		return false;
	}

	// �T�[�r�X�쐬
	m_hService = ::CreateService( 
		m_hServiceMgr,												// SCM �f�[�^�x�[�X�̃n���h��
		lpsServiceName,												// �J�n�������T�[�r�X�̖��O
		lpsServiceDispName,											// �\����
		SERVICE_ALL_ACCESS,											// �T�[�r�X�̃A�N�Z�X���̃^�C�v
		SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,	// �T�[�r�X�̃^�C�v
		SERVICE_AUTO_START,											// �T�[�r�X���J�n���鎞��
		SERVICE_ERROR_NORMAL,										// �T�[�r�X�Ɏ��s�����Ƃ��̐[����
		lpsCmdLine,													// �o�C�i���t�@�C����
		NULL,														// �^�O���ʎq
		NULL,														// ���[�h���������肷��O���[�v��
		NULL,														// �����̈ˑ�������Ȃ�z��
		NULL,														// �A�J�E���g��
		NULL );														// �A�J�E���g�̃p�X���[�h

	m_SvSt.dwServiceType = SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS;
	m_SvSt.dwCurrentState = SERVICE_START_PENDING;
	m_SvSt.dwControlsAccepted = SERVICE_ACCEPT_STOP;

	// �T�[�r�X�쐬�Ɏ��s�����ꍇ
	if( !m_hService )
	{
		if (GetLastError() == ERROR_SERVICE_EXISTS)
		{
			::MessageBox(NULL, _T("���ɃT�[�r�X�̓C���X�g�[������Ă��܂��B"), NULL, MB_ICONWARNING);
		}
		else
		{
			::MessageBox(NULL, _T("�T�[�r�X�̃C���X�g�[���Ɏ��s���܂����B"), NULL, MB_ICONWARNING);
		}
		return FALSE;
	}

	m_strServiceName = lpsServiceName;

	::MessageBox(NULL, _T("�T�[�r�X�̃C���X�g�[���ɐ������܂���"), _T("SUCCESS"), MB_OK);

	if( bStart )
	{
		ServiceControl( TRUE, lpsServiceName );
	}

	return bRet;
}

// �T�[�r�X�폜
BOOL CServiceFrame::UnInstall( LPTSTR lpsServiceName )
{
	BOOL bRet = TRUE;

	if( 0 == _tcscmp( _T(""), lpsServiceName ) )
	{
		::MessageBox( NULL, _T("�T�[�r�X�������͂���Ă��܂���"), _T("�G���["),MB_OK );
		return false;
	}

	// �T�[�r�X��~
	ServiceControl( FALSE, lpsServiceName );

	// �T�[�r�X�����łɊJ���Ă��邩
	m_hService = ::OpenService( m_hServiceMgr, lpsServiceName, DELETE );
	if( !m_hService )
	{
		::MessageBox( NULL, _T("�T�[�r�X�̃I�[�v���Ɏ��s"), _T("�G���["),MB_OK );
		return false;
	}

	bRet = ::DeleteService( m_hService );

	if( !bRet )
	{
		::MessageBox(NULL, _T("�T�[�r�X�̃A���C���X�g�[���Ɏ��s���܂���"), _T("�G���["), MB_OK);
		return bRet;
	}

	::MessageBox(NULL, _T("�T�[�r�X�̃A���C���X�g�[���ɐ������܂���"), _T("SUCCESS"), MB_OK);

	return bRet;
}

// �T�[�r�X����
BOOL CServiceFrame::Run( LPTSTR lpsServiceName )
{
	// �T�[�r�X���m�F
	if( 0 == _tcscmp( _T(""), lpsServiceName ) )
	{
		return FALSE;
	}

	m_strServiceName = lpsServiceName;

	// �T�[�r�X��SCM����̃��b�Z�[�W���f�B�X�p�b�`
	SERVICE_TABLE_ENTRY stServiceTable[] = { { lpsServiceName, _ServiceMain }, { NULL, NULL } };
	BOOL bRet = StartServiceCtrlDispatcher( stServiceTable );

	return TRUE;
}

// �T�[�r�X�̃��C������
void WINAPI CServiceFrame::_ServiceMain( DWORD dwArgc, PTSTR* pszArgv)
{
	// Initialize Variables for Service Control
	CServiceFrame* lpCServiceFrame = CServiceFrame::GetInstance();

	// �f�B�X�p�b�`���ꂽ���b�Z�[�W�ƃn���h�����֘A�t����
	lpCServiceFrame->m_hServiceStatus = ::RegisterServiceCtrlHandlerEx( lpCServiceFrame->m_strServiceName.c_str(), _ServiceCtrlHandler, NULL );

	// �֘A�t�����f
	if( 0 == lpCServiceFrame->m_hServiceStatus )
	{
		::MessageBox( NULL, _T("�֘A�t�����s"), _T("�x��"), MB_OK );
	}

	// �T�[�r�X������Ԃ̐ݒ�
	lpCServiceFrame->m_SvSt.dwServiceType = SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS;
	lpCServiceFrame->m_SvSt.dwWin32ExitCode = NO_ERROR;
	lpCServiceFrame->m_SvSt.dwServiceSpecificExitCode = 0;
	lpCServiceFrame->m_SvSt.dwCheckPoint = 1;
	lpCServiceFrame->m_SvSt.dwWaitHint = 3000;
	lpCServiceFrame->m_SvSt.dwControlsAccepted = /*SERVICE_ACCEPT_PAUSE_CONTINUE |*/ SERVICE_ACCEPT_STOP;
	lpCServiceFrame->m_SvSt.dwCurrentState = SERVICE_START_PENDING;

	::SetServiceStatus( lpCServiceFrame->m_hServiceStatus, &lpCServiceFrame->m_SvSt );

	// �T�[�r�X���C�������Ɉڍs
	// ����~���������Ȃ��悤�ɂ��Ă���
	lpCServiceFrame->m_SvSt.dwCurrentState = SERVICE_RUNNING;
	lpCServiceFrame->m_SvSt.dwCheckPoint = 0;
	lpCServiceFrame->m_SvSt.dwWaitHint = 0;
	lpCServiceFrame->m_SvSt.dwControlsAccepted = /*SERVICE_ACCEPT_PAUSE_CONTINUE |*/ SERVICE_ACCEPT_STOP;
	// �ꎞ��~�͂����Ȃ�

	::SetServiceStatus( lpCServiceFrame->m_hServiceStatus, &lpCServiceFrame->m_SvSt );
	
	// �L�����Z���C�x���g��ݒ�
	lpCServiceFrame->m_pServiceHelper->ServiceOpen( lpCServiceFrame->m_hCancel );

	// �T�[�r�X�̃��C���������J��Ԃ�
	while( SERVICE_RUNNING == lpCServiceFrame->m_SvSt.dwCurrentState )
	{
		// �N���e�B�J���Z�N�V����
		lpCServiceFrame->m_CriticalSectionHelper.Rock();
		lpCServiceFrame->m_pServiceHelper->ServiceMain();
		lpCServiceFrame->m_CriticalSectionHelper.Release();
	}
	lpCServiceFrame->m_pServiceHelper->ServiceClose();
}

// �T�[�r�X�̃n���h��
DWORD WINAPI CServiceFrame::_ServiceCtrlHandler( DWORD dwControl, DWORD dwEventType, PVOID pvEventData, PVOID pvContext )
{
	CServiceFrame* lpCServiceFrame = CServiceFrame::GetInstance();

	switch( dwControl )
	{
		// ��~
		case SERVICE_CONTROL_STOP:
			::SetEvent( lpCServiceFrame->m_hCancel );
			lpCServiceFrame->m_CriticalSectionHelper.Rock();
			lpCServiceFrame->m_pServiceHelper->ServiceStop();
			lpCServiceFrame->m_SvSt.dwCurrentState = SERVICE_STOPPED;
			lpCServiceFrame->m_SvSt.dwCheckPoint = 0;
			lpCServiceFrame->m_SvSt.dwWaitHint = 0;
			break;
		// �ꎞ��~
		case SERVICE_CONTROL_PAUSE:
			lpCServiceFrame->m_pServiceHelper->ServicePause();
			lpCServiceFrame->m_SvSt.dwCurrentState = SERVICE_PAUSED;
			lpCServiceFrame->m_SvSt.dwCheckPoint = 0;
			lpCServiceFrame->m_SvSt.dwWaitHint = 0;
			break;
		// �ċN��
		case SERVICE_CONTROL_CONTINUE:
			lpCServiceFrame->m_pServiceHelper->ServiceContinue();
			lpCServiceFrame->m_SvSt.dwCurrentState = SERVICE_RUNNING;
			lpCServiceFrame->m_SvSt.dwCheckPoint = 0;
			lpCServiceFrame->m_SvSt.dwWaitHint = 0;
			break;
		default:
			return ERROR_CALL_NOT_IMPLEMENTED;
	}

	::SetServiceStatus( lpCServiceFrame->m_hServiceStatus, &lpCServiceFrame->m_SvSt );

	lpCServiceFrame->m_CriticalSectionHelper.Release();

	return NO_ERROR;
}

void CServiceFrame::ServiceControl( BOOL bType, LPTSTR lpzServiceName )
{
	std::basic_string<TCHAR> strCommand = _T("");

	if( bType )
	{
		strCommand = _T("SC START ");
	}
	else
	{
		strCommand = _T("SC STOP ");
	}

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&si,sizeof(si));
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	si.cb=sizeof(si);

	// �R�}���h�쐬
	strCommand.append( lpzServiceName );
	int nLen = strCommand.length() + 1;
	LPTSTR lpzCmd = new TCHAR[nLen];
	::ZeroMemory( lpzCmd, nLen );
	_tcscpy(lpzCmd, strCommand.c_str());
	::CreateProcess( NULL, lpzCmd, NULL, NULL, NULL, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi );
	delete lpzCmd;
}