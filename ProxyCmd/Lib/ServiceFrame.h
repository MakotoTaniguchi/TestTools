#ifndef __SERVICEFRAME_H__
#define __SERVICEFRAME_H__

#pragma once

#include <tchar.h>
#include <string>
#include <windows.h>
#include <winsvc.h>

#include "ServiceHelper.h"
#include "CriticalSectionHelper.h"

//------------------------------------------��`------------------------------------------------
#define LOCAL_SYATEM _T("LocalSystem")
//----------------------------------------------------------------------------------------------

// �T�[�r�X�x�[�X
class CServiceFrame
{
public:

	// ���Ԏ擾
	static CServiceFrame* GetInstance();

	void SetObject( IServiceHelper* pServiceHelper ){ m_pServiceHelper = pServiceHelper; }

	// �C���X�g�[��
	BOOL Install( LPTSTR lpsServiceName, LPTSTR lpsServiceDispName, LPTSTR lpsCmdLine, BOOL bStart = FALSE );

	// �A���C���X�g�[��
	BOOL UnInstall( LPTSTR lpsServiceName );

	// ���s
	BOOL Run( LPTSTR lpsServiceName );

protected:

	// �R���X�g���N�^/�R�s�[�R���X�g���N�^/������֎~����
	CServiceFrame();
	CServiceFrame(const CServiceFrame& rhs);
    CServiceFrame& operator=(const CServiceFrame& rhs);
	~CServiceFrame();

	void ServiceControl( BOOL bType, LPTSTR lpzServiceName );

protected:

	// �T�[�r�X�̃n���h��
	SC_HANDLE m_hService;

	// SCM�̃n���h��
	SC_HANDLE m_hServiceMgr;

	// �T�[�r�X�̏��
	SERVICE_STATUS_HANDLE m_hServiceStatus;

protected:

	//�T�[�r�X���C����SCM�n���h���̎�����
	//API���R�[������ۂɂ�static�֐��łȂ��ƃR�[���ł��Ȃ��̂ňȉ���p��
	static DWORD WINAPI _ServiceCtrlHandler( DWORD dwControl, DWORD dwEventType, PVOID pvEventData, PVOID pvContext );
	static void WINAPI _ServiceMain(DWORD, LPTSTR*);

protected:

	// �T�[�r�X�̏��
	SERVICE_STATUS m_SvSt;

	// �T�[�r�X����
	std::basic_string<TCHAR> m_strServiceName;

	// �C�x���g�����̃C���^�[�t�F�[�X
	IServiceHelper* m_pServiceHelper;

	// �N���e�B�J���Z�N�V����
	CCriticalSectionHelper m_CriticalSectionHelper;

	// �L�����Z���n���h��
	HANDLE m_hCancel;
};

#endif