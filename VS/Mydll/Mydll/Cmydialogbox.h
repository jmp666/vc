#pragma once


// Cmydialogbox �Ի���

class Cmydialogbox : public CDialogEx
{
	DECLARE_DYNAMIC(Cmydialogbox)

public:
	Cmydialogbox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cmydialogbox();

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
