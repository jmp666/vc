#pragma once


// Cmydialogbox 对话框

class Cmydialogbox : public CDialogEx
{
	DECLARE_DYNAMIC(Cmydialogbox)

public:
	Cmydialogbox(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Cmydialogbox();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
