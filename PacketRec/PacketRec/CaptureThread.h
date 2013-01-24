#pragma once
#include "Threadbase.h"
#include "WinpcapCtrl.h"

class CCaptureThread :
	public CThreadBase
{
public:
	// �R���X�g���N�^
	CCaptureThread(void);

	// �f�X�g���N�^
	~CCaptureThread(void);

	void Initialize();
	
	// �X���b�h��~
	BOOL StopThread( DWORD dwTimeOut = INFINITE );

	// �X���b�h���C������
	UINT ThreadMain();
	
	// �A�_�v�^���ݒ�
	void SetAdopterName( LPTSTR lpczAdopterName ){ m_strAdopterName = lpczAdopterName; }

	// �t�@�C���p�X�̐ݒ�
	void setFilePath( LPTSTR lpzFilePath ){ m_lpzFilePath = lpzFilePath; }

	// �t�B���^�̐ݒ�
	void SetFilterData( FILTERDATA stFilterData ){ m_WinCapCtrl.PacketFiltering( stFilterData ); }

public:
	// �A�_�v�^��
	TSTRING m_strAdopterName;

	// �t�@�C���p�X
	LPTSTR m_lpzFilePath;

	// �L���v�`���R���g���[��
	CWinpcapCtrl m_WinCapCtrl;
};
