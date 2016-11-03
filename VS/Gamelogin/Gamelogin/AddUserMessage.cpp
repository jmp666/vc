// AddUserMessage.cpp : 实现文件
//

#include "stdafx.h"
#include "Gamelogin.h"
#include "AddUserMessage.h"
#include "afxdialogex.h"


// CAddUserMessage 对话框

IMPLEMENT_DYNAMIC(CAddUserMessage, CDialogEx)

CAddUserMessage::CAddUserMessage(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_UserName(_T(""))
	, m_PassWord(_T(""))
{
	m_userloginText = {0};
}

CAddUserMessage::~CAddUserMessage()
{
}

void CAddUserMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_UserName);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_PassWord);
	DDX_Control(pDX, IDC_COMBO_REGION, m_Game_Region);
	DDX_Control(pDX, IDC_COMBO_SERVER, m_Game_Server);
	DDX_Control(pDX, IDC_COMBO_LINE, m_Game_Line);
	DDX_Control(pDX, IDC_COMBO_ROLE, m_Game_Role);
}


BEGIN_MESSAGE_MAP(CAddUserMessage, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_REGION, &CAddUserMessage::OnCbnSelchangeComboRegion)
	ON_BN_CLICKED(IDC_BTN_OK, &CAddUserMessage::OnBnClickedBtnOk)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CAddUserMessage 消息处理程序


void CAddUserMessage::OnCbnSelchangeComboRegion()
{
	UINT m_cursel = m_Game_Region.GetCurSel();		//获取当前选中的
	switch (m_cursel)
	{
	case 0:
		//网通一区
		//先清空
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"王者争霸");
		m_Game_Server.AddString(L"龙争虎斗");
		m_Game_Server.AddString(L"魔神");
		m_Game_Server.AddString(L"雪原");
		//选中一项
		m_Game_Server.SetCurSel(0);
		break;
	case 1:	
		//网通二区
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"花灵(新服)");
		m_Game_Server.AddString(L"雄霸");
		//选中一项
		m_Game_Server.SetCurSel(0);
		break;
	case 2:
		//网通三区
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"威震九天(新服)");
		m_Game_Server.AddString(L"登封造极");
		//选中一项
		m_Game_Server.SetCurSel(0);
		break;
	case 3:
		//网通四区
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"碧海");
		m_Game_Server.AddString(L"啸天");
		//选中一项
		m_Game_Server.SetCurSel(0);
		break;
	case 4:
		//电信一区
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"战火重燃(新服)");
		m_Game_Server.AddString(L"狂龙降天");
		m_Game_Server.AddString(L"幻影密路");
		m_Game_Server.AddString(L"长空");
		//选中一项
		m_Game_Server.SetCurSel(0);
		break;
	case 5:
		//电信二区
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"锋芒毕露");
		m_Game_Server.AddString(L"东岳");
		//选中一项
		m_Game_Server.SetCurSel(0);
		break;
	case 6:
		//电信三区
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"玄湖");
		//选中一项
		m_Game_Server.SetCurSel(0);
		break;
	case 7:
		//电信四区
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"魅影");
		m_Game_Server.AddString(L"紫月");
		//选中一项
		m_Game_Server.SetCurSel(0);
		break;
	case 8:
		//电信五区
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"群雄争霸");
		m_Game_Server.AddString(L"沉香");
		//选中一项
		m_Game_Server.SetCurSel(0);
		break;
	case 9:
		//电信六区
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"霸业");
		m_Game_Server.AddString(L"苍月");
		m_Game_Server.AddString(L"星霜");
		//选中一项
		m_Game_Server.SetCurSel(0);
		break;
	}
}


void CAddUserMessage::OnBnClickedBtnOk()
{
	UpdateData(TRUE);
	CString m_strtmp;
	m_userloginText.m_UserName = m_UserName;		//账号
	m_userloginText.m_PassWord = m_PassWord;			//密码
	m_Game_Region.GetLBText(m_Game_Region.GetCurSel(), m_strtmp);
	m_userloginText.m_GameRepion.insert(pair<DWORD, CString>(m_Game_Region.GetCurSel(), m_strtmp));		//选择的大区
	m_Game_Server.GetLBText(m_Game_Server.GetCurSel(), m_strtmp);
	m_userloginText.m_GameServer.insert(pair<DWORD, CString>(m_Game_Server.GetCurSel(), m_strtmp));		//选择的服务器
	m_Game_Server.GetLBText(m_Game_Server.GetCurSel(), m_strtmp);
	m_userloginText.m_GameServer.insert(pair<DWORD, CString>(m_Game_Server.GetCurSel(), m_strtmp));		//选择的服务器
	m_Game_Line.GetLBText(m_Game_Line.GetCurSel(), m_strtmp);
	m_userloginText.m_GameLine.insert(pair<DWORD, CString>(m_Game_Line.GetCurSel(), m_strtmp));		//选择的线路
	m_Game_Role.GetLBText(m_Game_Role.GetCurSel(), m_strtmp);
	m_userloginText.m_GameRole.insert(pair<DWORD, CString>(m_Game_Role.GetCurSel(), m_strtmp));		//选择的角色
	OnOK();
	// TODO: 在此添加控件通知处理程序代码
}


void CAddUserMessage::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}


BOOL CAddUserMessage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_Game_Line.SetCurSel(0);
	m_Game_Role.SetCurSel(0);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
