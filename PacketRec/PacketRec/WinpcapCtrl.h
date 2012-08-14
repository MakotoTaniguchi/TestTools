// Winpcap��API
#ifndef WINPCAP_H
#define WINPCAP_H

#include "pcap.h"
#include "windows.h"

#define MAX_RECV_SIZE	( 1024 )
#define FREAMSIZE		(18)

// �A�_�v�^���
typedef struct stDeviceData
{
	TSTRING strDeviceName;
	TSTRING strAdopter;
	TSTRING strIPAddress;
} CONNECTDEVICEDATA, *LP_CONNECTDEVICEDATA;

// �A�_�v�^���X�g
typedef std::vector<CONNECTDEVICEDATA> VEC_DEVICEDATA, *LP_VEC_DEVICEDATA;

// �t�B���^�^�C�v
typedef struct FilterData
{
	TSTRING strSrcHost;
	TSTRING strDstHost;
	TSTRING strSrcIP;
	TSTRING strDstIP;
	TSTRING strSrcPort;
	TSTRING strDstPort;

	FilterData()
	{
		strSrcHost	= _T("");
		strDstHost	= _T("");
		strSrcIP	= _T("");
		strDstIP	= _T("");
		strSrcPort	= _T("");
		strDstPort	= _T("");
	}
} FILTERDATA, *LP_FILTERDATA;

// Winpcap��API���g�p����N���X
class CWinpcapCtrl
{
public:
	// �R���X�g���N�^
	CWinpcapCtrl();

	// �f�X�g���N�^
	~CWinpcapCtrl();

	// �A�_�v�^�����W
	static VEC_DEVICEDATA AdopterOpen();

	// �L���v�`���J�n
	void CaptureStart( LPTSTR lpzFilePath );

	// �L���v�`����~
	void CaptureStop( DWORD dwWaite = INFINITE );

	// ������
	void Initialize( LPTSTR lpzAdopterName );

	// �p�P�b�g�t�B���^�����O
	void PacketFiltering( FILTERDATA stFilterData );

private:

	// �p�P�b�g�p������쐬
	LPTSTR MakeFilterChar( TSTRING strSrc, TSTRING strDst, TSTRING strType );

private:
	
	// �A�_�v�^��
	TSTRING m_strSelectAdopter;

	// �I�u�W�F�N�g���ʎq
	pcap_t* m_pPcap;

	// �L�����Z���t���O
	BOOL m_bCancel;

	// �L�����Z���C�x���g
	HANDLE m_hCancel;
};

#endif