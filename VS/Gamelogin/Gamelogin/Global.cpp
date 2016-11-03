#include "stdafx.h"
#include "Global.h"

//获取游戏路径
CString GetGamePathdirectory()
{
	TCHAR szFileDirectoryPath[MAX_PATH];
	ZeroMemory(&szFileDirectoryPath, MAX_PATH);
	TCHAR szDisplayName[MAX_PATH] = { 0 };
	BROWSEINFO bi;
	PIDLIST_ABSOLUTE Pid;
	ZeroMemory(&bi, sizeof BROWSEINFO);
	bi.pszDisplayName = szDisplayName;
	bi.lpszTitle = TEXT("请选择游戏安装目录下的Launcher.exe文件");
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_BROWSEINCLUDEFILES;		//通用对话框的属性
	Pid = ::SHBrowseForFolder(&bi);
	::SHGetPathFromIDList(Pid, szFileDirectoryPath);
	TRACE(L"%s\n", szDisplayName);
	TRACE(L"%s\n", szFileDirectoryPath);
	if (wcscmp(szDisplayName, L"launcher.exe") != 0)
	{
		AfxMessageBox(TEXT("请选择Launcher.exe文件"));
		return NULL;
	}
	PTCHAR szFileDirectroryName = nullptr;
	szFileDirectroryName = wcsstr(szFileDirectoryPath, L"launcher.exe");
	if (nullptr != szFileDirectroryName)
	{
		*szFileDirectroryName = '\0';
		TRACE(L"%s\n", szFileDirectoryPath);
	}
	return szFileDirectoryPath;
}
