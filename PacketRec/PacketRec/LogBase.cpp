#include "stdafx.h"
#include "LogBase.h"

/*******************
// �t�@�C���p�X
*******************/
CLogFilePath gLogFilePath;

/*******************
// �R���X�g���N�^
*******************/
CLogFilePath::CLogFilePath() : m_lpzLogFilePath(NULL)
{
}

/*******************
// �f�X�g���N�^
*******************/
CLogFilePath::~CLogFilePath()
{
	if( NULL != m_lpzLogFilePath )
	{
		delete m_lpzLogFilePath;
	}
}

/*******************
// �t�@�C���p�X���
*******************/
void CLogFilePath::operator =( LPTSTR lpzFilePath )
{
	if( NULL == lpzFilePath )
	{
		return;
	}
	
	if( NULL != m_lpzLogFilePath )
	{
		delete m_lpzLogFilePath;
	}
	
	int nSize = _tcslen( lpzFilePath ) + 1;
	m_lpzLogFilePath = new TCHAR[nSize];
	_tcscpy( m_lpzLogFilePath, lpzFilePath );
}

/******************
// �R���X�g���N�^
******************/
CLogBase::CLogBase( LPTSTR lpzFilePath, DWORD dwLine ) : m_hFile(INVALID_HANDLE_VALUE), m_lpzFilePath(lpzFilePath), m_dwLine(dwLine)
{
	::InitializeCriticalSection(&m_cs);
}

/*****************
// �f�X�g���N�^
*****************/
CLogBase::~CLogBase()
{
	if( m_hFile )
	{
		::CloseHandle( m_hFile );
		m_hFile = INVALID_HANDLE_VALUE;
	}

	::DeleteCriticalSection(&m_cs);
}

/*****************
// �w�b�_�쐬
*****************/
int CLogBase::GetHeaderLog( LPTSTR lpzLog )
{
	if( NULL == lpzLog )
	{
		return -1;
	}

	SYSTEMTIME sysTime;
	::GetLocalTime( &sysTime );
	int nRet = 0;

	nRet = _stprintf( lpzLog, _T("%04d/%02d/%02d\t%02d:%02d:%02d\t%s\t%ld\t%ld\t"), 
								sysTime.wYear, sysTime.wMonth, sysTime.wDay, 
								sysTime.wHour, sysTime.wMinute, sysTime.wSecond,
								m_lpzFilePath, m_dwLine, ::GetCurrentThreadId() );

	return nRet;
}

/*****************
// ���O��������
*****************/
BOOL CLogBase::WriteLog( LPCTSTR lpzLog )
{
	TCHAR szFormatLog[256];
	GetHeaderLog( szFormatLog );

	TSTRING strLog;
	strLog.append( szFormatLog );
	strLog.append( lpzLog );
	strLog.append( _T("\r\n") );

	::EnterCriticalSection(&m_cs);

	// �t�@�C���I�[�v��
	m_hFile = ::CreateFile( gLogFilePath.GetLogFilePath(), (GENERIC_READ|GENERIC_WRITE), FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
	if( INVALID_HANDLE_VALUE == m_hFile )
	{
		return FALSE;
	}
	
	DWORD dwWriteSize = 0;
	::SetFilePointer( m_hFile, 0, NULL, FILE_END );
	::WriteFile( m_hFile, strLog.c_str(), strLog.size(), &dwWriteSize, NULL );
	
	if( INVALID_HANDLE_VALUE != m_hFile )
	{
		::CloseHandle( m_hFile );
		m_hFile = INVALID_HANDLE_VALUE;
	}

	::LeaveCriticalSection(&m_cs);

	return TRUE;
}

/*****************
// �J�n���O�o��
*****************/
void CLogBase::StartLog( LPTSTR lpzLogPath )
{
	gLogFilePath = lpzLogPath;

	Log( NORMAL, _T("==============�J�n==============") );
}

/*****************
// ���O�o��
*****************/
void CLogBase::Log( ETYPE eType, LPTSTR lpzFormat, ... )
{
	if( NULL == gLogFilePath.GetLogFilePath() )
	{
		return;
	}
	
	va_list va;
	va_start( va, lpzFormat );
	TCHAR szLog[100];
	_vstprintf( szLog, lpzFormat, va );
	va_end( va );

	TSTRING strLog;
	switch( eType )
	{
		case NORMAL:
			strLog = _T("..\t");
			break;
		case ABNORMAL:
			strLog = _T("!!\t");
			break;
	}

	strLog.append( szLog );

	WriteLog( strLog.c_str() );
}

/*****************
// �I�����O�o��
*****************/
void CLogBase::EndLog()
{
	if( m_hFile )
	{
		Log( NORMAL, _T("==============�I��==============") );
	}
}