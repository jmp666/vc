// AddUserMessage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Gamelogin.h"
#include "AddUserMessage.h"
#include "afxdialogex.h"


// CAddUserMessage �Ի���

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


// CAddUserMessage ��Ϣ�������


void CAddUserMessage::OnCbnSelchangeComboRegion()
{
	UINT m_cursel = m_Game_Region.GetCurSel();		//��ȡ��ǰѡ�е�
	switch (m_cursel)
	{
	case 0:
		//��ͨһ��
		//�����
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"��������");
		m_Game_Server.AddString(L"��������");
		m_Game_Server.AddString(L"ħ��");
		m_Game_Server.AddString(L"ѩԭ");
		//ѡ��һ��
		m_Game_Server.SetCurSel(0);
		break;
	case 1:	
		//��ͨ����
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"����(�·�)");
		m_Game_Server.AddString(L"�۰�");
		//ѡ��һ��
		m_Game_Server.SetCurSel(0);
		break;
	case 2:
		//��ͨ����
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"�������(�·�)");
		m_Game_Server.AddString(L"�Ƿ��켫");
		//ѡ��һ��
		m_Game_Server.SetCurSel(0);
		break;
	case 3:
		//��ͨ����
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"�̺�");
		m_Game_Server.AddString(L"Х��");
		//ѡ��һ��
		m_Game_Server.SetCurSel(0);
		break;
	case 4:
		//����һ��
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"ս����ȼ(�·�)");
		m_Game_Server.AddString(L"��������");
		m_Game_Server.AddString(L"��Ӱ��·");
		m_Game_Server.AddString(L"����");
		//ѡ��һ��
		m_Game_Server.SetCurSel(0);
		break;
	case 5:
		//���Ŷ���
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"��â��¶");
		m_Game_Server.AddString(L"����");
		//ѡ��һ��
		m_Game_Server.SetCurSel(0);
		break;
	case 6:
		//��������
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"����");
		//ѡ��һ��
		m_Game_Server.SetCurSel(0);
		break;
	case 7:
		//��������
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"��Ӱ");
		m_Game_Server.AddString(L"����");
		//ѡ��һ��
		m_Game_Server.SetCurSel(0);
		break;
	case 8:
		//��������
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"Ⱥ������");
		m_Game_Server.AddString(L"����");
		//ѡ��һ��
		m_Game_Server.SetCurSel(0);
		break;
	case 9:
		//��������
		m_Game_Server.ResetContent();
		m_Game_Server.AddString(L"��ҵ");
		m_Game_Server.AddString(L"����");
		m_Game_Server.AddString(L"��˪");
		//ѡ��һ��
		m_Game_Server.SetCurSel(0);
		break;
	}
}


void CAddUserMessage::OnBnClickedBtnOk()
{
	UpdateData(TRUE);
	CString m_strtmp;
	m_userloginText.m_UserName = m_UserName;		//�˺�
	m_userloginText.m_PassWord = m_PassWord;			//����
	m_Game_Region.GetLBText(m_Game_Region.GetCurSel(), m_strtmp);
	m_userloginText.m_GameRepion.insert(pair<DWORD, CString>(m_Game_Region.GetCurSel(), m_strtmp));		//ѡ��Ĵ���
	m_Game_Server.GetLBText(m_Game_Server.GetCurSel(), m_strtmp);
	m_userloginText.m_GameServer.insert(pair<DWORD, CString>(m_Game_Server.GetCurSel(), m_strtmp));		//ѡ��ķ�����
	m_Game_Server.GetLBText(m_Game_Server.GetCurSel(), m_strtmp);
	m_userloginText.m_GameServer.insert(pair<DWORD, CString>(m_Game_Server.GetCurSel(), m_strtmp));		//ѡ��ķ�����
	m_Game_Line.GetLBText(m_Game_Line.GetCurSel(), m_strtmp);
	m_userloginText.m_GameLine.insert(pair<DWORD, CString>(m_Game_Line.GetCurSel(), m_strtmp));		//ѡ�����·
	m_Game_Role.GetLBText(m_Game_Role.GetCurSel(), m_strtmp);
	m_userloginText.m_GameRole.insert(pair<DWORD, CString>(m_Game_Role.GetCurSel(), m_strtmp));		//ѡ��Ľ�ɫ
	OnOK();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CAddUserMessage::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}


BOOL CAddUserMessage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_Game_Line.SetCurSel(0);
	m_Game_Role.SetCurSel(0);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
