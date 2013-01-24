#ifndef _LOGBASE_H_
#define _LOGBASE_H_

#pragma once

#include "tchar.h"
#include <string>
#include <stdarg.h>

typedef std::basic_string<TCHAR> TSTRING;

/*******************
// ���O�o�͊J�n
*******************/
#define LOGBASE_START	CLogBase(__FILE__, __LINE__).StartLog

/*******************
// ���O�o��
*******************/
#define LOGBASE			CLogBase(__FILE__, __LINE__).Log

/*******************
// ���O�o�͏I��
*******************/
#define LOGBASE_END		CLogBase(__FILE__, __LINE__).EndLog

enum ETYPE
{
	NORMAL = 0,		// ����
	ABNORMAL =1		// �ُ�
};

/***********************
// �t�@�C���p�X�N���X
***********************/
class CLogFilePath
{
public:
	CLogFilePath();
	~CLogFilePath();
	
	void operator =( LPTSTR lpzFilePath );
	
	LPTSTR GetLogFilePath(){ return m_lpzLogFilePath; }
	
private:
	LPTSTR m_lpzLogFilePath;
};

/************
// ���O�N���X
************/
class CLogBase
{
public:
	CLogBase( LPTSTR lpzFilePath = _T(""), DWORD dwLine = 0 );
	~CLogBase();

	void StartLog( LPTSTR lpzLogPath );
	void Log( ETYPE eType, LPTSTR lpzFormat, ... );
	void EndLog();

private:
	// �N����\t�����b\t�t�@�C����\t�s��
	int GetHeaderLog( LPTSTR lpzLogPath );

	// �t�@�C����������
	BOOL WriteLog( LPCTSTR lpzLog );

private:
	// �t�@�C���n���h��
	HANDLE m_hFile;

	// �N���e�B�J���Z�N�V����
	CRITICAL_SECTION m_cs;

	// �t�@�C���p�X
	LPTSTR m_lpzFilePath;

	// ���C��
	DWORD m_dwLine;
};

#endif // _LOGBASE_H_