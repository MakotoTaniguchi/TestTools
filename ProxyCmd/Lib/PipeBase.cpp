#include "stdafx.h"
#include <windows.h>
#include "PipeBase.h"


CPipeBase::CPipeBase()
{
	m_hPipeServer = INVALID_HANDLE_VALUE;
	m_hPipeClient = INVALID_HANDLE_VALUE;
	m_hEvent = NULL;
}

CPipeBase::~CPipeBase()
{
}

void CPipeBase::CreatePipeServerSide( LPTSTR lpsConnectName )
{
    m_hPipeServer = CreateNamedPipe( lpsConnectName, PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, 
                                  PIPE_TYPE_BYTE | PIPE_WAIT, 1, 0, 0, (1000 * 10), 0 );
    if(m_hPipeServer == INVALID_HANDLE_VALUE)
	{
		return;
	}
}

void CPipeBase::WritePipeServerSide( LPTSTR lpsPath )
{
	if( NULL == lpsPath )
	{
		return;
	}

    if (m_hPipeServer != INVALID_HANDLE_VALUE)
    {
        TCHAR buff[MAX_PATH] = _T("");
		_tcscpy( buff, lpsPath );
        DWORD    nBytes;
        WriteFile(m_hPipeServer, buff, _tcslen(buff), &nBytes, NULL);
    }
}

void CPipeBase::ReadPipeServerSide( LPTSTR lpsPath )
{
	OVERLAPPED ov; 
	ZeroMemory(&ov, sizeof(OVERLAPPED));
	HANDLE hConnect = NULL;
	hConnect = ::CreateEvent( NULL, FALSE, FALSE, _T("PipeConnect") );
	HANDLE hEventHandles[2] = { hConnect, m_hEvent };
	ov.hEvent = hConnect;

	::ConnectNamedPipe(m_hPipeServer, &ov);
	DWORD dwEventRet = ::WaitForMultipleObjects( 2, hEventHandles, FALSE, INFINITE);

	// 通信を受信した場合
	if( (WAIT_OBJECT_0 + 0) == dwEventRet )
	{
		if (m_hPipeServer != INVALID_HANDLE_VALUE)
		{
			DWORD    nBytes;
			TCHAR    buff[MAX_PATH];
			memset(buff, NULL, sizeof(buff));
			if (ReadFile(m_hPipeServer, buff, 10, &nBytes, NULL))
			{
				_tcscpy(lpsPath, buff);
			}
		}
	}

	::DisconnectNamedPipe( m_hPipeServer );
	if( hConnect )
	{
		::CloseHandle( hConnect );
		hConnect = NULL;
	}
}

//クライアント側の処理
void CPipeBase::ConnectPipeClientSide( LPTSTR lpsConnectName )
{
    m_hPipeClient = CreateFile( lpsConnectName, 
                  GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0 );
}

void CPipeBase::WriteClientSide(LPTSTR lpsPath)
{
    if (m_hPipeClient != INVALID_HANDLE_VALUE)
    {
        DWORD nBytes;
        TCHAR buff[MAX_PATH] = _T("");
		_tcscpy(buff, lpsPath);
        WriteFile(m_hPipeClient, buff, _tcslen(buff), &nBytes, NULL);
    }
}

void CPipeBase::ReadClientSide( LPTSTR lpsPath )
{
    if (m_hPipeClient != INVALID_HANDLE_VALUE)
    {
        DWORD    nBytes;
        TCHAR    buff[MAX_PATH];
        memset(buff, NULL, sizeof(buff));
        if(ReadFile(m_hPipeClient, buff, 10, &nBytes, NULL))
		{
			_tcscpy( lpsPath, buff );
		}
    }
}

void CPipeBase::ClosePipe()
{
    if (m_hPipeClient != INVALID_HANDLE_VALUE)
    {
		DisconnectNamedPipe( m_hPipeClient );
        CloseHandle(m_hPipeClient);
        m_hPipeClient = INVALID_HANDLE_VALUE;
    }

	if (m_hPipeServer != INVALID_HANDLE_VALUE)
    {
		DisconnectNamedPipe( m_hPipeServer );
        CloseHandle(m_hPipeServer);
        m_hPipeServer = INVALID_HANDLE_VALUE;
    }
}