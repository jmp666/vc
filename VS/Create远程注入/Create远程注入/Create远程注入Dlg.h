
// CreateԶ��ע��Dlg.h : ͷ�ļ�
//

#pragma once


// CCreateԶ��ע��Dlg �Ի���
class CCreateԶ��ע��Dlg : public CDialogEx
{
// ����
public:
	CCreateԶ��ע��Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATE_DIALOG };
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
	afx_msg void OnBnClickedButtonZr();
	afx_msg void OnBnClickedButtonCs();
};
