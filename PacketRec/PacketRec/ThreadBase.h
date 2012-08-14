#ifndef __THREAD_BASE_H__
#define __THREAD_BASE_H__

#include "windows.h"

class CThreadBase
{
public:
	// �R���X�g���N�^
	CThreadBase();
	
	// �f�X�g���N�^
	~CThreadBase();

	// ������
	virtual void Initialize();

	// �X���b�h�쐬
	void CreateThread( BOOL bStart = TRUE );

	// �X���b�h�j��
	BOOL Destroy( DWORD dwTimeOut = INFINITE );

	// �X���b�h���C������
	virtual UINT ThreadMain() = 0;

	// �n���h���擾
	HANDLE GetThreadHandle(){ return m_hThread; }

	// �X���b�h���s
	void StartThread();

protected:

	// �X���b�h�̃G���g���|�C���g
	static UINT __stdcall ThreadEntry( void* pParam );

protected:
	// �X���b�h�n���h��
	HANDLE m_hThread;
	
	// �X���b�hID
	UINT m_uThreadID;
};

#endif