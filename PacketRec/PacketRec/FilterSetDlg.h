#ifndef	__FILTERSETDLG_H__
#define	__FILTERSETDLG_H__

#pragma once

#include "WinpcapCtrl.h"

// CFilterSetDlg �_�C�A���O

class CFilterSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CFilterSetDlg)

public:
	CFilterSetDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CFilterSetDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_FILTER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

public:
	FILTERDATA GetFilterData(){ return m_stFilterData; }

private:
	CString strSrcHost;	// ���M���R���s���[�^��
	CString strDstHost;	// ��M���R���s���[�^��
	CString strSrcNet;	// ���M��IP
	CString strDstNet;	// ��M��IP
	CString strSrcPort;	// ���M���|�[�g
	CString strDstPort;	// ���M���|�[�g

	FILTERDATA m_stFilterData;
};

#endif