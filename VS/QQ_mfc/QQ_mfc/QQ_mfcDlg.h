
// QQ_mfcDlg.h : ͷ�ļ�
//

#pragma once
#include "afxext.h"


// CQQ_mfcDlg �Ի���
class CQQ_mfcDlg : public CDialogEx
{
// ����
public:
	CQQ_mfcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QQ_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLogin();
public:
	CString m_StrUser;
	CString m_StrPass;
	BOOL ����״̬��();
	CStatusBar m_״̬��;
	
	void ����״̬���ı�(PTCHAR strbuf, UINT ID=0);
	bool ���ÿؼ�����(bool Flog);
};
