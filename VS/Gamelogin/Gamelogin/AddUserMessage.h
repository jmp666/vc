#pragma once
#include "afxwin.h"
#include "Global.h"

// CAddUserMessage 对话框

class CAddUserMessage : public CDialogEx
{
	DECLARE_DYNAMIC(CAddUserMessage)

public:
	CAddUserMessage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddUserMessage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 用户名
	CString m_UserName;
	// 用户密码
	CString m_PassWord;
	// 游戏大区
	CComboBox m_Game_Region;
	// 服务器
	CComboBox m_Game_Server;
	// 游戏线路
	CComboBox m_Game_Line;
	// 游戏角色
	CComboBox m_Game_Role;
	USERLONGINMESSAGE m_userloginText;
	afx_msg void OnCbnSelchangeComboRegion();
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
};
