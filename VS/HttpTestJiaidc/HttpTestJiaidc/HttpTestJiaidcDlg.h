
// HttpTestJiaidcDlg.h : ͷ�ļ�
//

#pragma once
#import "C:\\Windows\\System32\\winhttpcom.dll"	no_namespace

// CHttpTestJiaidcDlg �Ի���
class CHttpTestJiaidcDlg : public CDialogEx
{
// ����
public:
	CHttpTestJiaidcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HTTPTESTJIAIDC_DIALOG };
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
	afx_msg void OnBnClickedBtnGetvcode();
	//�������ָ��
	IWinHttpRequestPtr	LPhttp;
	// ��������ͼƬ��CImage����
	BOOL LodcomImage(LPVOID PmemIm, ULONG dwLen, CImage& ImgObj);
	afx_msg void OnBnClickedBtnLogin();
};
