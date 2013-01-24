
// ProxyCmdDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once

#include "Lib/ServiceFrame.h"
#include "Lib/PipeBase.h"
#include "ProxyCmdService.h"
#include "afxwin.h"

// CProxyCmdDlg �_�C�A���O
class CProxyCmdDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CProxyCmdDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_PROXYCMD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	// �C���^�[�t�F�[�X���p�������C�x���g�N���X
	CProxyCmdService m_ProxyCmd;

	// �T�[�r�X�N���X
	CServiceFrame* m_pServiceFrame;

public:

	// �T�[�r�X����
	void ServiceMain();
	CEdit m_CmdPath;
	afx_msg void OnBnClickedBtnInstall();
	afx_msg void OnBnClickedBtnUninstall();
	afx_msg void OnBnClickedBtnRun();
};
