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

	// �T�[�o�[������
	void CreatePipeServerSide( LPTSTR lpsConnectName = CONNECTNAME );
	virtual void WritePipeServerSide( LPTSTR lpsPath );
	virtual void ReadPipeServerSide( LPTSTR lpsPath );

	// �N���C�A���g������
	void ConnectPipeClientSide( LPTSTR lpsConnectName = CONNECTNAME );
	virtual void WriteClientSide( LPTSTR lpsPath );
	virtual void ReadClientSide( LPTSTR lpsPath );

	// �p�C�v�ʐM�N���[�Y
	void ClosePipe();

	// �C�x���g�ݒ�
	void SetEvent( HANDLE hEvent ){ m_hEvent = hEvent; };

private:
	// �T�[�o�[���̃n���h��
	HANDLE m_hPipeServer;

	// �N���C�A���g���̃n���h��
	HANDLE m_hPipeClient;

	// �L�����Z��
	HANDLE m_hEvent;
};

#endif