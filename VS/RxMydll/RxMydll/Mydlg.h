#pragma once


// CMydlg �Ի���

class CMydlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMydlg)

public:
	CMydlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMydlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
