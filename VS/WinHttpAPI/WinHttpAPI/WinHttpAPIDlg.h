
// WinHttpAPIDlg.h : ͷ�ļ�
//

#pragma once


// CWinHttpAPIDlg �Ի���
class CWinHttpAPIDlg : public CDialogEx
{
// ����
public:
	CWinHttpAPIDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WINHTTPAPI_DIALOG };
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
	afx_msg void OnBnClickedBtn11();
	afx_msg void OnBnClickedBtn12();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtn14();
	afx_msg void OnBnClickedBtn15();
};
