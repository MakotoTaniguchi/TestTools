#include "StdAfx.h"
#include "CaptureThread.h"

/*******************
// �R���X�g���N�^
*******************/
CCaptureThread::CCaptureThread(void) : m_lpzFilePath(NULL)
{
	m_strAdopterName = _T("");
	if( NULL == m_lpzFilePath )
	{
		m_lpzFilePath = new TCHAR[MAX_PATH];
	}
}

/*******************
// �f�X�g���N�^
*******************/
CCaptureThread::~CCaptureThread(void)
{
	if( NULL != m_lpzFilePath )
	{
		delete m_lpzFilePath;
	}
}

/*******************
// �X���b�h������
*******************/
void CCaptureThread::Initialize()
{
	m_WinCapCtrl.Initialize( (LPTSTR)m_strAdopterName.c_str() );
}

/*****************
// �X���b�h�J�n
*****************/
UINT CCaptureThread::ThreadMain()
{
	LOGBASE( NORMAL, _T("�L���v�`���[�X���b�h�J�n �X���b�hID:%d"), m_uThreadID );

	// �J�����g�p�X
	::GetModuleFileName( NULL, m_lpzFilePath, MAX_PATH );
	::PathRemoveFileSpec( m_lpzFilePath );

	// pcap�t�@�C���̃t�@�C�����쐬
	TCHAR szFileName[MAX_PATH];
	SYSTEMTIME sysTime;
	::GetLocalTime( &sysTime );
	_stprintf( szFileName, _T("%04d%02d%02d_%02d%02d%03d.pcap"), 
								sysTime.wYear, sysTime.wMonth, sysTime.wDay,
								sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds );

	::PathAppend( m_lpzFilePath, szFileName );
	LOGBASE( NORMAL, _T("�t�@�C���p�X�̐ݒ� %s"), m_lpzFilePath );
	
	m_WinCapCtrl.CaptureStart( m_lpzFilePath );

	return 0;
}

/*****************
// �X���b�h��~
*****************/
BOOL CCaptureThread::StopThread( DWORD dwTimeOut /*= INFINITE*/ )
{
	m_WinCapCtrl.CaptureStop();

	LOGBASE( NORMAL, _T("�L���v�`���[�X���b�h��~ �X���b�hID:%d"), m_uThreadID );

	return TRUE;
}