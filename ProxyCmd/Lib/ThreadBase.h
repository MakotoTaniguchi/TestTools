#ifndef __THREAD_BASE_H__
#define __THREAD_BASE_H__

#include "windows.h"

class CThreadBase
{
public:
	// コンストラクタ
	CThreadBase();
	
	// デストラクタ
	~CThreadBase();

	// スレッド作成
	void CreateThread( BOOL bStart = TRUE );

	// スレッド破棄
	BOOL Destroy( DWORD dwTimeOut = INFINITE );

	// スレッドメイン処理
	virtual UINT ThreadMain();

	// ハンドル取得
	HANDLE GetThreadHandle(){ return m_hThread; }

	// キャンセルハンドル設定
	void SetCancelHandle( HANDLE hCancel ){ m_hCancel = hCancel; }

protected:

	// スレッドのエントリポイント
	static UINT __stdcall ThreadEntry( void* pParam );
	
private:
	
	// スレッドハンドル
	HANDLE m_hThread;
	
	// スレッドID
	UINT m_uThreadID;

protected:

	// キャンセルハンドル
	HANDLE m_hCancel;

};

#endif