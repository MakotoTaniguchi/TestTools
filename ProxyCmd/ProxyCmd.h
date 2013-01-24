
// ProxyCmd.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CProxyCmdApp:
// このクラスの実装については、ProxyCmd.cpp を参照してください。
//

class CProxyCmdApp : public CWinAppEx
{
public:
	CProxyCmdApp();

// オーバーライド
	public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CProxyCmdApp theApp;