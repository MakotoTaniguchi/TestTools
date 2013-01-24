
// ProxyCmdDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ProxyCmd.h"
#include "ProxyCmdDlg.h"

#include "imagehlp.h"
#pragma comment(lib, "imagehlp.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CProxyCmdDlg ダイアログ




CProxyCmdDlg::CProxyCmdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProxyCmdDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// 初期化
	m_pServiceFrame = CServiceFrame::GetInstance();
	m_pServiceFrame->SetObject( &m_ProxyCmd );
}

void CProxyCmdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_CmdPath);
}

BEGIN_MESSAGE_MAP(CProxyCmdDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_INSTALL, &CProxyCmdDlg::OnBnClickedBtnInstall)
	ON_BN_CLICKED(IDC_BTN_UNINSTALL, &CProxyCmdDlg::OnBnClickedBtnUninstall)
	ON_BN_CLICKED(IDC_BTN_RUN, &CProxyCmdDlg::OnBnClickedBtnRun)
END_MESSAGE_MAP()


// CProxyCmdDlg メッセージ ハンドラ

BOOL CProxyCmdDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CProxyCmdDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CProxyCmdDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CProxyCmdDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// サービスのメイン処理
void CProxyCmdDlg::ServiceMain()
{
	m_pServiceFrame->Run( _T("ProxyCmd") );
}

// サービスのインストール
void CProxyCmdDlg::OnBnClickedBtnInstall()
{
	MakeSureDirectoryPathExists( "C:\\ProxyCmdService\\ProxyCmd.exe" );
	TCHAR DstPath[MAX_PATH] = _T("");
	GetModuleFileName( NULL, DstPath, sizeof(DstPath) );
	CopyFile( DstPath, _T("C:\\ProxyCmdService\\ProxyCmd.exe"), FALSE );

	m_pServiceFrame->Install( _T("ProxyCmd"), _T("ProxyCommand"), _T("C:\\ProxyCmdService\\ProxyCmd.exe /Service"), TRUE );
}

// サービスのアンインストール
void CProxyCmdDlg::OnBnClickedBtnUninstall()
{
	m_pServiceFrame->UnInstall( _T("ProxyCmd") );
}

// コマンドの実行
void CProxyCmdDlg::OnBnClickedBtnRun()
{
	CPipeBase PipBase;
	PipBase.ConnectPipeClientSide();
	TCHAR sExePath[MAX_PATH] = _T("");
	m_CmdPath.GetWindowText( sExePath, MAX_PATH );
	PipBase.WriteClientSide( sExePath );
	PipBase.ClosePipe();
}
