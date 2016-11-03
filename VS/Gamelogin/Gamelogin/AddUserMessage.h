#pragma once
#include "afxwin.h"
#include "Global.h"

// CAddUserMessage �Ի���

class CAddUserMessage : public CDialogEx
{
	DECLARE_DYNAMIC(CAddUserMessage)

public:
	CAddUserMessage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddUserMessage();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �û���
	CString m_UserName;
	// �û�����
	CString m_PassWord;
	// ��Ϸ����
	CComboBox m_Game_Region;
	// ������
	CComboBox m_Game_Server;
	// ��Ϸ��·
	CComboBox m_Game_Line;
	// ��Ϸ��ɫ
	CComboBox m_Game_Role;
	USERLONGINMESSAGE m_userloginText;
	afx_msg void OnCbnSelchangeComboRegion();
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
};
