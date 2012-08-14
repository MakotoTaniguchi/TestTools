#ifndef __SERVICEFRAME_H__
#define __SERVICEFRAME_H__

#pragma once

#include <tchar.h>
#include <string>
#include <windows.h>
#include <winsvc.h>

#include "ServiceHelper.h"
#include "CriticalSectionHelper.h"

//------------------------------------------定義------------------------------------------------
#define LOCAL_SYATEM _T("LocalSystem")
//----------------------------------------------------------------------------------------------

// サービスベース
class CServiceFrame
{
public:

	// 実態取得
	static CServiceFrame* GetInstance();

	void SetObject( IServiceHelper* pServiceHelper ){ m_pServiceHelper = pServiceHelper; }

	// インストール
	BOOL Install( LPTSTR lpsServiceName, LPTSTR lpsServiceDispName, LPTSTR lpsCmdLine, BOOL bStart = FALSE );

	// アンインストール
	BOOL UnInstall( LPTSTR lpsServiceName );

	// 実行
	BOOL Run( LPTSTR lpsServiceName );

protected:

	// コンストラクタ/コピーコンストラクタ/代入を禁止する
	CServiceFrame();
	CServiceFrame(const CServiceFrame& rhs);
    CServiceFrame& operator=(const CServiceFrame& rhs);
	~CServiceFrame();

	void ServiceControl( BOOL bType, LPTSTR lpzServiceName );

protected:

	// サービスのハンドル
	SC_HANDLE m_hService;

	// SCMのハンドル
	SC_HANDLE m_hServiceMgr;

	// サービスの状態
	SERVICE_STATUS_HANDLE m_hServiceStatus;

protected:

	//サービスメインとSCMハンドラの実処理
	//APIをコールする際にはstatic関数でないとコールできないので以下を用意
	static DWORD WINAPI _ServiceCtrlHandler( DWORD dwControl, DWORD dwEventType, PVOID pvEventData, PVOID pvContext );
	static void WINAPI _ServiceMain(DWORD, LPTSTR*);

protected:

	// サービスの状態
	SERVICE_STATUS m_SvSt;

	// サービス名称
	std::basic_string<TCHAR> m_strServiceName;

	// イベント処理のインターフェース
	IServiceHelper* m_pServiceHelper;

	// クリティカルセクション
	CCriticalSectionHelper m_CriticalSectionHelper;

	// キャンセルハンドル
	HANDLE m_hCancel;
};

#endif