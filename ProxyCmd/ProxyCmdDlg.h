
// ProxyCmdDlg.h : ヘッダー ファイル
//

#pragma once

#include "Lib/ServiceFrame.h"
#include "Lib/PipeBase.h"
#include "ProxyCmdService.h"
#include "afxwin.h"

// CProxyCmdDlg ダイアログ
class CProxyCmdDlg : public CDialog
{
// コンストラクション
public:
	CProxyCmdDlg(CWnd* pParent = NULL);	// 標準コンストラクタ

// ダイアログ データ
	enum { IDD = IDD_PROXYCMD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	// インターフェースを継承したイベントクラス
	CProxyCmdService m_ProxyCmd;

	// サービスクラス
	CServiceFrame* m_pServiceFrame;

public:

	// サービス処理
	void ServiceMain();
	CEdit m_CmdPath;
	afx_msg void OnBnClickedBtnInstall();
	afx_msg void OnBnClickedBtnUninstall();
	afx_msg void OnBnClickedBtnRun();
};
