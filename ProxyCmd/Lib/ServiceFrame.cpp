#include "stdafx.h"
#include "ServiceFrame.h"
#include "PipeBase.h"

// 実態の取得
CServiceFrame* CServiceFrame::GetInstance()
{
	static CServiceFrame ServiceFrame;
	return &ServiceFrame;
}

// コンストラクタ
CServiceFrame::CServiceFrame()
{
	m_hServiceMgr = ::OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );
	m_strServiceName = _T("");
	m_pServiceHelper = NULL;
	m_hService = NULL;
	m_hCancel = NULL;
	m_hCancel = ::CreateEvent( NULL, FALSE, FALSE, _T("ServiceFrame") );
}

// デストラクタ
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

// サービス作成
BOOL CServiceFrame::Install( LPTSTR lpsServiceName, LPTSTR lpsServiceDispName, LPTSTR lpsCmdLine, BOOL bStart/* = FALSE*/ )
{
	BOOL bRet = TRUE;

	if( 0 == _tcscmp( _T(""), lpsServiceName ) )
	{
		::MessageBox( NULL, _T("サービス名が入力されていません"), _T("エラー"),MB_OK );
		return false;
	}

	if( 0 == _tcscmp( _T(""), lpsServiceDispName ) )
	{
		::MessageBox( NULL, _T("サービス表示名が入力されていません"), _T("エラー"),MB_OK );
		return false;
	}

	if( 0 == _tcscmp( _T(""), lpsCmdLine ) )
	{
		::MessageBox( NULL, _T("コマンドラインが入力されていません"), _T("エラー"),MB_OK );
		return false;
	}

	// サービス作成
	m_hService = ::CreateService( 
		m_hServiceMgr,												// SCM データベースのハンドル
		lpsServiceName,												// 開始したいサービスの名前
		lpsServiceDispName,											// 表示名
		SERVICE_ALL_ACCESS,											// サービスのアクセス権のタイプ
		SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,	// サービスのタイプ
		SERVICE_AUTO_START,											// サービスを開始する時期
		SERVICE_ERROR_NORMAL,										// サービスに失敗したときの深刻さ
		lpsCmdLine,													// バイナリファイル名
		NULL,														// タグ識別子
		NULL,														// ロード順序を決定するグループ名
		NULL,														// 複数の依存名からなる配列
		NULL,														// アカウント名
		NULL );														// アカウントのパスワード

	m_SvSt.dwServiceType = SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS;
	m_SvSt.dwCurrentState = SERVICE_START_PENDING;
	m_SvSt.dwControlsAccepted = SERVICE_ACCEPT_STOP;

	// サービス作成に失敗した場合
	if( !m_hService )
	{
		if (GetLastError() == ERROR_SERVICE_EXISTS)
		{
			::MessageBox(NULL, _T("既にサービスはインストールされています。"), NULL, MB_ICONWARNING);
		}
		else
		{
			::MessageBox(NULL, _T("サービスのインストールに失敗しました。"), NULL, MB_ICONWARNING);
		}
		return FALSE;
	}

	m_strServiceName = lpsServiceName;

	::MessageBox(NULL, _T("サービスのインストールに成功しました"), _T("SUCCESS"), MB_OK);

	if( bStart )
	{
		ServiceControl( TRUE, lpsServiceName );
	}

	return bRet;
}

// サービス削除
BOOL CServiceFrame::UnInstall( LPTSTR lpsServiceName )
{
	BOOL bRet = TRUE;

	if( 0 == _tcscmp( _T(""), lpsServiceName ) )
	{
		::MessageBox( NULL, _T("サービス名が入力されていません"), _T("エラー"),MB_OK );
		return false;
	}

	// サービス停止
	ServiceControl( FALSE, lpsServiceName );

	// サービスをすでに開いているか
	m_hService = ::OpenService( m_hServiceMgr, lpsServiceName, DELETE );
	if( !m_hService )
	{
		::MessageBox( NULL, _T("サービスのオープンに失敗"), _T("エラー"),MB_OK );
		return false;
	}

	bRet = ::DeleteService( m_hService );

	if( !bRet )
	{
		::MessageBox(NULL, _T("サービスのアンインストールに失敗しました"), _T("エラー"), MB_OK);
		return bRet;
	}

	::MessageBox(NULL, _T("サービスのアンインストールに成功しました"), _T("SUCCESS"), MB_OK);

	return bRet;
}

// サービス処理
BOOL CServiceFrame::Run( LPTSTR lpsServiceName )
{
	// サービス名確認
	if( 0 == _tcscmp( _T(""), lpsServiceName ) )
	{
		return FALSE;
	}

	m_strServiceName = lpsServiceName;

	// サービスにSCMからのメッセージをディスパッチ
	SERVICE_TABLE_ENTRY stServiceTable[] = { { lpsServiceName, _ServiceMain }, { NULL, NULL } };
	BOOL bRet = StartServiceCtrlDispatcher( stServiceTable );

	return TRUE;
}

// サービスのメイン処理
void WINAPI CServiceFrame::_ServiceMain( DWORD dwArgc, PTSTR* pszArgv)
{
	// Initialize Variables for Service Control
	CServiceFrame* lpCServiceFrame = CServiceFrame::GetInstance();

	// ディスパッチされたメッセージとハンドラを関連付ける
	lpCServiceFrame->m_hServiceStatus = ::RegisterServiceCtrlHandlerEx( lpCServiceFrame->m_strServiceName.c_str(), _ServiceCtrlHandler, NULL );

	// 関連付け判断
	if( 0 == lpCServiceFrame->m_hServiceStatus )
	{
		::MessageBox( NULL, _T("関連付け失敗"), _T("警告"), MB_OK );
	}

	// サービス初期状態の設定
	lpCServiceFrame->m_SvSt.dwServiceType = SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS;
	lpCServiceFrame->m_SvSt.dwWin32ExitCode = NO_ERROR;
	lpCServiceFrame->m_SvSt.dwServiceSpecificExitCode = 0;
	lpCServiceFrame->m_SvSt.dwCheckPoint = 1;
	lpCServiceFrame->m_SvSt.dwWaitHint = 3000;
	lpCServiceFrame->m_SvSt.dwControlsAccepted = /*SERVICE_ACCEPT_PAUSE_CONTINUE |*/ SERVICE_ACCEPT_STOP;
	lpCServiceFrame->m_SvSt.dwCurrentState = SERVICE_START_PENDING;

	::SetServiceStatus( lpCServiceFrame->m_hServiceStatus, &lpCServiceFrame->m_SvSt );

	// サービスメイン処理に移行
	// ※停止しか押せないようにしている
	lpCServiceFrame->m_SvSt.dwCurrentState = SERVICE_RUNNING;
	lpCServiceFrame->m_SvSt.dwCheckPoint = 0;
	lpCServiceFrame->m_SvSt.dwWaitHint = 0;
	lpCServiceFrame->m_SvSt.dwControlsAccepted = /*SERVICE_ACCEPT_PAUSE_CONTINUE |*/ SERVICE_ACCEPT_STOP;
	// 一時停止はさせない

	::SetServiceStatus( lpCServiceFrame->m_hServiceStatus, &lpCServiceFrame->m_SvSt );
	
	// キャンセルイベントを設定
	lpCServiceFrame->m_pServiceHelper->ServiceOpen( lpCServiceFrame->m_hCancel );

	// サービスのメイン処理を繰り返す
	while( SERVICE_RUNNING == lpCServiceFrame->m_SvSt.dwCurrentState )
	{
		// クリティカルセクション
		lpCServiceFrame->m_CriticalSectionHelper.Rock();
		lpCServiceFrame->m_pServiceHelper->ServiceMain();
		lpCServiceFrame->m_CriticalSectionHelper.Release();
	}
	lpCServiceFrame->m_pServiceHelper->ServiceClose();
}

// サービスのハンドラ
DWORD WINAPI CServiceFrame::_ServiceCtrlHandler( DWORD dwControl, DWORD dwEventType, PVOID pvEventData, PVOID pvContext )
{
	CServiceFrame* lpCServiceFrame = CServiceFrame::GetInstance();

	switch( dwControl )
	{
		// 停止
		case SERVICE_CONTROL_STOP:
			::SetEvent( lpCServiceFrame->m_hCancel );
			lpCServiceFrame->m_CriticalSectionHelper.Rock();
			lpCServiceFrame->m_pServiceHelper->ServiceStop();
			lpCServiceFrame->m_SvSt.dwCurrentState = SERVICE_STOPPED;
			lpCServiceFrame->m_SvSt.dwCheckPoint = 0;
			lpCServiceFrame->m_SvSt.dwWaitHint = 0;
			break;
		// 一時停止
		case SERVICE_CONTROL_PAUSE:
			lpCServiceFrame->m_pServiceHelper->ServicePause();
			lpCServiceFrame->m_SvSt.dwCurrentState = SERVICE_PAUSED;
			lpCServiceFrame->m_SvSt.dwCheckPoint = 0;
			lpCServiceFrame->m_SvSt.dwWaitHint = 0;
			break;
		// 再起動
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

	// コマンド作成
	strCommand.append( lpzServiceName );
	int nLen = strCommand.length() + 1;
	LPTSTR lpzCmd = new TCHAR[nLen];
	::ZeroMemory( lpzCmd, nLen );
	_tcscpy(lpzCmd, strCommand.c_str());
	::CreateProcess( NULL, lpzCmd, NULL, NULL, NULL, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi );
	delete lpzCmd;
}