
// HttptestIDC816Dlg.h : ͷ�ļ�
//

#pragma once

#import "C:\\Windows\\System32\\winhttpcom.dll"	no_namespace
// CHttptestIDC816Dlg �Ի���
class CHttptestIDC816Dlg : public CDialogEx
{
// ����
public:
	CHttptestIDC816Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HTTPTESTIDC816_DIALOG };
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
	IWinHttpRequestPtr Phttp;
	afx_msg void OnBnClickedButton1();
	// ����cookie������
	CString DisposeCookie(CString StringText);
};
