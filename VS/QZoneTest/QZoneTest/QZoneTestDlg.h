
// QZoneTestDlg.h : ͷ�ļ�
//

#pragma once
#include "resource.h"


// CQZoneTestDlg �Ի���
class CQZoneTestDlg : public CDialogEx
{
// ����
public:
	CQZoneTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_QZONETEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLogin();
	CStatusBar m_Statusbar;
	BOOL InitStatusBar();
	void SetStateInfo(LPCTSTR lpszText, UINT posIdx = 0);

	void EnableControl(BOOL bEnable = TRUE);

	CString m_strQQ;
	CString m_strPass;
	afx_msg void OnBnClickedBtnPublic();
};
