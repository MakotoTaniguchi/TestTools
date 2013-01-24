
// ProxyCmd.cpp : アプリケーションのクラス動作を定義します。
//

#include "stdafx.h"
#include "ProxyCmd.h"
#include "ProxyCmdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProxyCmdApp

BEGIN_MESSAGE_MAP(CProxyCmdApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CProxyCmdApp コンストラクション

CProxyCmdApp::CProxyCmdApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}


// 唯一の CProxyCmdApp オブジェクトです。

CProxyCmdApp theApp;


// CProxyCmdApp 初期化

BOOL CProxyCmdApp::InitInstance()
{
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
	SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));

	CProxyCmdDlg dlg;
	m_pMainWnd = &dlg;
	
	// コマンドラインのオプションにより処理を分ける
	if( NULL == _tcsstr( this->m_lpCmdLine, _T("/Service") ) )
	{
		dlg.DoModal();
	}
	else
	{
		dlg.ServiceMain();
	}

	// ダイアログは閉じられました。アプリケーションのメッセージ ポンプを開始しないで
	//  アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}
