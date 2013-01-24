
// PacketMonitorDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "PacketRec.h"
#include "PacketRecDlg.h"
#include "FilterSetDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPacketRecDlg �_�C�A���O
CPacketRecDlg::CPacketRecDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPacketRecDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPacketRecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CAPTURE_START, m_BtnCaptureStart);
	DDX_Control(pDX, IDC_CAPTURE_STOP, m_BtnCaptureStop);
	DDX_Control(pDX, IDC_COMBO_ADOPTER, m_CombAdopter);
}

BEGIN_MESSAGE_MAP(CPacketRecDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CAPTURE_START, &CPacketRecDlg::OnBnClickedCaptureStart)
	ON_BN_CLICKED(IDC_CAPTURE_STOP, &CPacketRecDlg::OnBnClickedCaptureStop)
END_MESSAGE_MAP()


// CPacketRecDlg ���b�Z�[�W �n���h��

BOOL CPacketRecDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	m_vecDeviceData = CWinpcapCtrl::AdopterOpen();

	VEC_DEVICEDATA::iterator it;
	for( it = m_vecDeviceData.begin(); it != m_vecDeviceData.end(); it++ )
	{
		m_CombAdopter.AddString(it->strDeviceName.c_str());
	}

	LOGBASE( NORMAL, _T("��ʏ���������") );

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

void CPacketRecDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CPacketRecDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CPacketRecDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/****************************************************************//*!
 @brief		�L���v�`���[�J�n����
 @details	�ڍא����i�ȗ��j
 @retval	�Ȃ�
 @exception	��O�o�́i������Ώȗ��j
 @attention ���ӏ����i�ȗ��j
 @note		
 @sa ------------------------------------------------------------
 - $Fnc>	CPacketRecDlg::OnBnClickedCaptureStart
 - $Prg>	0%
 - $Upd>	2012/05/30 �J�� UID �������e
 - $Tst>	2012/05/30 �J�� UID [SA] -- [AV] -- [UT] --
****************************************************************///
void CPacketRecDlg::OnBnClickedCaptureStart()
{
	CString strAdopter;
	m_CombAdopter.GetWindowText( strAdopter );

	VEC_DEVICEDATA::iterator it;
	for( it = m_vecDeviceData.begin(); it != m_vecDeviceData.end(); it++ )
	{
		if( 0 == strAdopter.Compare(it->strDeviceName.c_str()) )
		{
			strAdopter = it->strAdopter.c_str();
			break;
		}
	}

	if( m_mapCaptureThread.end() == m_mapCaptureThread.find( strAdopter ) )
	{
		CCaptureThread* pCaptureThread = new CCaptureThread();
		pCaptureThread->CreateThread(FALSE);

		/*
		CFilterSetDlg dlg;
		INT_PTR nRet = dlg.DoModal();
		if( IDOK == nRet )
		{
			pCaptureThread->SetFilterData( dlg.GetFilterData() );
		}
		*/
		pCaptureThread->SetAdopterName( (LPTSTR)strAdopter.GetString() );
		pCaptureThread->Initialize();
		LOGBASE( NORMAL, _T("�A�_�v�^�̐ݒ� %s"), (LPTSTR)strAdopter.GetString() );

		pCaptureThread->StartThread();
		m_mapCaptureThread[strAdopter] = pCaptureThread;
		LOGBASE( NORMAL, _T("�L���v�`���[���J�n����܂����B") );
	}
}

/****************************************************************//*!
 @brief		�L���b�v�`���[��~����
 @details	�ڍא����i�ȗ��j
 @retval	�Ȃ�
 @exception	��O�o�́i������Ώȗ��j
 @attention ���ӏ����i�ȗ��j
 @note		
 @sa ------------------------------------------------------------
 - $Fnc>	CPacketRecDlg::OnBnClickedCaptureStop
 - $Prg>	0%
 - $Upd>	2012/05/30 �J�� UID �������e
 - $Tst>	2012/05/30 �J�� UID [SA] -- [AV] -- [UT] --
****************************************************************///
void CPacketRecDlg::OnBnClickedCaptureStop()
{
	CString strAdopter;
	m_CombAdopter.GetWindowText( strAdopter );

	VEC_DEVICEDATA::iterator it;
	for( it = m_vecDeviceData.begin(); it != m_vecDeviceData.end(); it++ )
	{
		if( 0 == strAdopter.Compare(it->strDeviceName.c_str()) )
		{
			strAdopter = it->strAdopter.c_str();
			break;
		}
	}

	if( m_mapCaptureThread.end() != m_mapCaptureThread.find( strAdopter ) )
	{
		m_mapCaptureThread[strAdopter]->StopThread();
		m_mapCaptureThread[strAdopter]->Destroy();
		delete m_mapCaptureThread[strAdopter];
		m_mapCaptureThread.erase(strAdopter);
		LOGBASE( NORMAL, _T("�L���v�`���[����~����܂����B") );
		::MessageBox(NULL, _T("�I�����܂��B"), _T("�I��"), MB_OK);
	}
}
