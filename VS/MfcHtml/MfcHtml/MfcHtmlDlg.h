
// MfcHtmlDlg.h : ͷ�ļ�
//

#pragma once
#include "explorer1.h"
#include "afxwin.h"


// CMfcHtmlDlg �Ի���
class CMfcHtmlDlg : public CDialogEx
{
// ����
public:
	CMfcHtmlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCHTML_DIALOG };
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
	CExplorer1 m_Web;
	CEdit m_Edit;
	CButton m_Button;
	afx_msg void OnBnClickedButton1();
};
