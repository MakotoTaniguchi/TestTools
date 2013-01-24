#ifndef __PIPEBASE_H__
#define __PIPEBASE_H__

#include "tchar.h"
#include <windows.h>

#define CONNECTNAME (_T("\\\\.\\pipe\\Base"))

class CPipeBase
{
public:
	CPipeBase();
	~CPipeBase();

	// サーバー側処理
	void CreatePipeServerSide( LPTSTR lpsConnectName = CONNECTNAME );
	virtual void WritePipeServerSide( LPTSTR lpsPath );
	virtual void ReadPipeServerSide( LPTSTR lpsPath );

	// クライアント側処理
	void ConnectPipeClientSide( LPTSTR lpsConnectName = CONNECTNAME );
	virtual void WriteClientSide( LPTSTR lpsPath );
	virtual void ReadClientSide( LPTSTR lpsPath );

	// パイプ通信クローズ
	void ClosePipe();

	// イベント設定
	void SetEvent( HANDLE hEvent ){ m_hEvent = hEvent; };

private:
	// サーバー側のハンドル
	HANDLE m_hPipeServer;

	// クライアント側のハンドル
	HANDLE m_hPipeClient;

	// キャンセル
	HANDLE m_hEvent;
};

#endif