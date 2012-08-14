
// PacketRecDlg.h : �w�b�_�[ �t�@�C��
//
#include "WinpcapCtrl.h"
#include "CaptureThread.h"

#pragma once

// CPacketRecDlg �_�C�A���O
class CPacketRecDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CPacketRecDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_PACKETMONITOR_DIALOG };
	CButton		m_BtnCaptureStart;
	CButton		m_BtnCaptureStop;
	CComboBox	m_CombAdopter;

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
	// �t�@�C���p�X
	CString m_strFilePath;

	// �A�_�v�^���X�g
	VEC_DEVICEDATA m_vecDeviceData;

	// �L���v�`���X���b�h
	std::map<CString, CCaptureThread*> m_mapCaptureThread;
	//CCaptureThread m_CaptureThread;

public:
	/*******************
	// �L���v�`���J�n
	*******************/
	afx_msg void OnBnClickedCaptureStart();

	/*******************
	// �L���v�`����~
	*******************/
	afx_msg void OnBnClickedCaptureStop();

	/*******************
	// �t�B���^�ݒ�
	*******************/
	afx_msg void OnBnClickedFilterSet();
};
