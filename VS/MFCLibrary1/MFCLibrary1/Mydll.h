#pragma once
#include "afxwin.h"


// CMydll 对话框

class CMydll : public CDialogEx
{
	DECLARE_DYNAMIC(CMydll)

public:
	CMydll(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMydll();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CEdit m_Edit;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
