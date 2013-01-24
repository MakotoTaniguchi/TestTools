
// ProxyCmdDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ProxyCmd.h"
#include "ProxyCmdDlg.h"

#include "imagehlp.h"
#pragma comment(lib, "imagehlp.lib")

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


// CProxyCmdDlg �_�C�A���O




CProxyCmdDlg::CProxyCmdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProxyCmdDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// ������
	m_pServiceFrame = CServiceFrame::GetInstance();
	m_pServiceFrame->SetObject( &m_ProxyCmd );
}

void CProxyCmdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_CmdPath);
}

BEGIN_MESSAGE_MAP(CProxyCmdDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_INSTALL, &CProxyCmdDlg::OnBnClickedBtnInstall)
	ON_BN_CLICKED(IDC_BTN_UNINSTALL, &CProxyCmdDlg::OnBnClickedBtnUninstall)
	ON_BN_CLICKED(IDC_BTN_RUN, &CProxyCmdDlg::OnBnClickedBtnRun)
END_MESSAGE_MAP()


// CProxyCmdDlg ���b�Z�[�W �n���h��

BOOL CProxyCmdDlg::OnInitDialog()
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

	// TODO: �������������ɒǉ����܂��B

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

void CProxyCmdDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CProxyCmdDlg::OnPaint()
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
HCURSOR CProxyCmdDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// �T�[�r�X�̃��C������
void CProxyCmdDlg::ServiceMain()
{
	m_pServiceFrame->Run( _T("ProxyCmd") );
}

// �T�[�r�X�̃C���X�g�[��
void CProxyCmdDlg::OnBnClickedBtnInstall()
{
	MakeSureDirectoryPathExists( "C:\\ProxyCmdService\\ProxyCmd.exe" );
	TCHAR DstPath[MAX_PATH] = _T("");
	GetModuleFileName( NULL, DstPath, sizeof(DstPath) );
	CopyFile( DstPath, _T("C:\\ProxyCmdService\\ProxyCmd.exe"), FALSE );

	m_pServiceFrame->Install( _T("ProxyCmd"), _T("ProxyCommand"), _T("C:\\ProxyCmdService\\ProxyCmd.exe /Service"), TRUE );
}

// �T�[�r�X�̃A���C���X�g�[��
void CProxyCmdDlg::OnBnClickedBtnUninstall()
{
	m_pServiceFrame->UnInstall( _T("ProxyCmd") );
}

// �R�}���h�̎��s
void CProxyCmdDlg::OnBnClickedBtnRun()
{
	CPipeBase PipBase;
	PipBase.ConnectPipeClientSide();
	TCHAR sExePath[MAX_PATH] = _T("");
	m_CmdPath.GetWindowText( sExePath, MAX_PATH );
	PipBase.WriteClientSide( sExePath );
	PipBase.ClosePipe();
}
