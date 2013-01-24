#include "stdafx.h"
#include "WinpcapCtrl.h"

/*******************
// �R���X�g���N�^
*******************/
CWinpcapCtrl::CWinpcapCtrl() : m_pPcap(NULL), m_bCancel(FALSE), m_hCancel(NULL)
{
	m_hCancel = ::CreateEvent( NULL, FALSE, FALSE, NULL );
}

/*******************
// �f�X�g���N�^
*******************/
CWinpcapCtrl::~CWinpcapCtrl()
{
}

/*******************
// �I�[�v���A�_�v�^
*******************/
VEC_DEVICEDATA CWinpcapCtrl::AdopterOpen()
{
	VEC_DEVICEDATA vecDeviceName;
	pcap_if_t *AddDevs = NULL;
	LPTSTR szErrorBuf = NULL;
	if( pcap_findalldevs(&AddDevs, szErrorBuf) != -1 )
	{
		TSTRING strIPAddress;
		pcap_if_t *d = AddDevs;
		while( d )
		{
			// IP�A�h���X�̏�񂪗L���Ȃ��̂������^�[�Q�b�g�ɂ���
			if( d->addresses != NULL ) {
				// sockaddr_in�ɃL���X�g����
				sockaddr_in *sa = (sockaddr_in*)d->addresses->addr;

				// ���ݗL���łȂ��f�o�C�X�́A
				// �A�h���X��0�ɂȂ��Ă���̂Ŕr������
				//if( sa->sin_addr.s_addr != 0 )
				//{ 
					// sa->sin_addr.s_addr ��IP�A�h���X
					// d->name �ɃA�_�v�^��
					// d->description�Ƀh���C�o��
					strIPAddress.append( inet_ntoa( sa->sin_addr ) );
					CONNECTDEVICEDATA DeviceData = { d->description, d->name, strIPAddress };

					vecDeviceName.push_back( DeviceData );
				//}
				d = d->next;
			}
			else
			{
				LOGBASE( ABNORMAL, _T("IP�A�h���X���L���ł͂���܂���") );
				break;
			}
		}
		// �f�o�C�X���̃o�b�t�@���J������
		pcap_freealldevs(AddDevs);
	}
	else
	{
		LOGBASE( ABNORMAL, _T("�A�_�v�^�擾���s %s"), szErrorBuf );
	}

	return vecDeviceName;
}

/*******************
// �L���v�`���J�n
*******************/
void CWinpcapCtrl::CaptureStart( LPTSTR lpzFilePath )
{
	// Pcap�t�@�C���I�[�v��
	pcap_dumper_t* pDF = ::pcap_dump_open( m_pPcap, lpzFilePath );

	// �p�P�b�g�L���v�`��
	if( NULL != pDF )
	{
		while( !m_bCancel )
		{
			const u_char* pData;
			struct pcap_pkthdr* pkt_header;
			int dRet = ::pcap_next_ex( m_pPcap , &pkt_header, &pData );

			if( 0 < dRet )
			{
				LOGBASE( NORMAL, _T("�p�P�b�g��������") );
				::pcap_dump( (u_char*)pDF, pkt_header, pData );
			}
		}
		::pcap_dump_close( pDF );
	}
	else
	{
		LOGBASE( NORMAL, _T("pcap�t�@�C���I�[�v�����s") );
	}

	::SetEvent( m_hCancel );
}

/*******************
// �L���v�`����~
*******************/
void CWinpcapCtrl::CaptureStop( DWORD dwWaite )
{
	if( m_bCancel )
	{
		return;
	}

	m_bCancel = TRUE;

	DWORD dwRet = ::WaitForSingleObject( m_hCancel, dwWaite );

	if( WAIT_OBJECT_0 != dwRet )
	{
		LOGBASE( ABNORMAL, _T("�L���v�`���[��~���s %ld"), dwRet );
	}

	if( NULL == m_pPcap )
	{
		LOGBASE( ABNORMAL, _T("�N���[�Y�����s�v") );
		return;
	}

	::pcap_close( m_pPcap );
}

/***************************
// �p�P�b�g�t�B���^�����O
***************************/
void CWinpcapCtrl::PacketFiltering( FILTERDATA stFilterData )
{
	if( NULL == m_pPcap )
	{
		return;
	}

	// �t�B���^�̕�����쐬
	TSTRING strFilterChar = _T("");
	strFilterChar.append( MakeFilterChar( stFilterData.strSrcHost,	stFilterData.strDstHost,	_T("host") ) );
	strFilterChar.append( MakeFilterChar( stFilterData.strSrcIP,	stFilterData.strDstIP,		_T("net") ) );
	strFilterChar.append( MakeFilterChar( stFilterData.strSrcPort,	stFilterData.strDstPort,	_T("port") ) );

	LOGBASE( ABNORMAL, _T("�t�B���^������F%s\n"), strFilterChar.c_str() );

	char errbuf[PCAP_ERRBUF_SIZE];	/* �G���[���R�i�[�p�����z�� */
	bpf_u_int32 mask;				/* �Ď��f�B�o�C�X�̃l�b�g�}�X�N */
	bpf_u_int32 net;				/* �Ď��f�B�o�C�X��IP�A�h���X */

	// �l�b�g�}�X�N�쐬
	int nRet = ::pcap_lookupnet( m_strSelectAdopter.c_str(), &net, &mask, errbuf );
	if ( -1 == nRet) {
		LOGBASE( ABNORMAL, _T("�f�B�o�C�X�̃l�b�g�}�X�N���擾�ł��܂���ł����F%s\n"), m_strSelectAdopter.c_str() );
		net = 0;
		mask = 0;
	}

	bpf_program stBpfProg;			/* �R���p�C���ς݃t�B���^�p�\���� */
	nRet = ::pcap_compile( m_pPcap, &stBpfProg, strFilterChar.c_str(), 1, net );
	if( -1 == nRet )
	{
		LOGBASE( ABNORMAL, _T("�t�B���^�̃R���p�C���Ɏ��s���܂����B") );
	}

	nRet = ::pcap_setfilter( m_pPcap, &stBpfProg );
	if( -1 == nRet )
	{
		LOGBASE( ABNORMAL, _T("�t�B���^�̐ݒ�Ɏ��s���܂����B") );
	}
}

/***************************
// �p�P�b�g�p������쐬
***************************/
LPTSTR CWinpcapCtrl::MakeFilterChar( TSTRING strSrc, TSTRING strDst, TSTRING strType )
{
	// �t�B���^������
	TSTRING strFilterChar = _T("");

	// ���挳 or ���悪0�����𒴂��Ă����ꍇ
	if( 0 < strSrc.length() || 0 < strDst.length() )
	{
		if( 0 < strSrc.length() )
		{
			strFilterChar.append( _T("src") );
			strFilterChar.append( strType );
			strFilterChar.append( strSrc );
			strFilterChar.append( _T(" ") );
		}

		if( 0 < strDst.length() )
		{
			strFilterChar.append( _T("dst") );
			strFilterChar.append( strType );
			strFilterChar.append( strDst );
			strFilterChar.append( _T(" ") );
		}

		return (LPTSTR)strFilterChar.c_str();
	}

	return NULL;
}


/*****************************
// ���W�ΏۃA�_�v�^���̐ݒ�
*****************************/
void CWinpcapCtrl::Initialize( LPTSTR lpzAdopterName )
{
	// �A�_�v�^�ݒ�
	m_strSelectAdopter = lpzAdopterName;

	if( m_strSelectAdopter.empty() )
	{
		LOGBASE( ABNORMAL, _T("�A�_�v�^���I������Ă��܂���ł����B") );
		return;
	}

	TCHAR szErrorBuf[1024];		// �G���[����
	int nTimeOut = 1000 * 5;	// �^�C���A�E�g�l
	// �v���~�X�L���X���[�h�Ŏ��W
	// 65536byte���܂�܂Ő����Ԃ��Ȃ�
	if( ( m_pPcap = ::pcap_open_live( m_strSelectAdopter.c_str(), 65536, TRUE, nTimeOut, szErrorBuf ) )== NULL )
	{
		LOGBASE( ABNORMAL, _T("�v���~�X�L���X���[�h�ŃC���^�[�t�F�[�X�I�[�v�����s %s"), szErrorBuf);
		return;
	}

	LOGBASE( NORMAL, _T("�v���~�X�L���X���[�h�ŃC���^�[�t�F�[�X�I�[�v�� %s"), m_strSelectAdopter.c_str());
}