
// ZipTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ZipTest.h"
#include "ZipTestDlg.h"
#include "afxdialogex.h"
#include "ZipImplement.h"
#include "OptionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

TCHAR szOutputFileNameFmt[]={_T("\\%s.g")};
TCHAR szShellPath[]={_T("ShellPath")};
TCHAR szUnpackHistory[]={_T("UnpackRecord")};

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CZipTestDlg 对话框




CZipTestDlg::CZipTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZipTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZipTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCSHELLTREE1, m_wndPath);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_wndZip);
}

BEGIN_MESSAGE_MAP(CZipTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CZipTestDlg::OnBnClickedOk)
	ON_COMMAND(ID_CMD_ABOUT, &CZipTestDlg::OnCmdAbout)
	ON_COMMAND(ID_CMD_QUIT, &CZipTestDlg::OnCmdQuit)
	ON_COMMAND(ID_CMD_SET, &CZipTestDlg::OnCmdSet)
	ON_NOTIFY(TVN_SELCHANGED, IDC_MFCSHELLTREE1, &CZipTestDlg::OnTvnSelchangedMfcshelltree1)
	ON_BN_CLICKED(IDCANCEL, &CZipTestDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_UNPACK, &CZipTestDlg::OnBnClickedBtnUnpack)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CZipTestDlg 消息处理程序

BOOL CZipTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_wndPath.ModifyStyle(m_wndPath.GetSafeHwnd(),NULL,TVS_SHOWSELALWAYS,NULL);		//一直显示选中项

	CString str,strPath;
	int iIndex=0;
	GetModuleFileName(GetModuleHandle(NULL),str.GetBuffer(MAX_PATH),MAX_PATH);
	str.ReleaseBuffer();
	iIndex=str.ReverseFind('\\');
	if (iIndex==-1)
		str.Empty();
	else
		str.Delete(iIndex+1,str.GetLength());
	GetPrivateProfileString(COptionDlg::szOption,szShellPath,str.GetBuffer(),strPath.GetBuffer(MAX_PATH),MAX_PATH,COptionDlg::szOptionFile);
	str.ReleaseBuffer();
	strPath.ReleaseBuffer();
	if (strPath.IsEmpty())
		strPath=str;
	m_wndPath.SelectPath(strPath.GetBuffer());
	strPath.ReleaseBuffer();

	GetPrivateProfileString(COptionDlg::szOption,szUnpackHistory,_T(""),str.GetBuffer(MAX_PATH),MAX_PATH,COptionDlg::szOptionFile);
	str.ReleaseBuffer();
	m_wndZip.SetWindowText(str);

	m_wndZip.EnableFileBrowseButton(_T("*.g"),_T("已打包文件 (*.g)|*.g|全部文件 (*.*)|*.*||"));
		
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CZipTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CZipTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CZipTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CZipTestDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;

	m_wndPath.GetItemPath(str);
	_SetIniInfo(szShellPath,str);
	_ZipPack(str);
	
}


BOOL CZipTestDlg::_ZipPack(CString& strPath)
{
	BOOL bResult=FALSE;
	CZipImplement myZip;
	CString strOut,str=strPath;
	int iIndex=0;

	if (str.IsEmpty())
		return bResult;
	if ((str.GetAt(str.GetLength()-1)=='\\'))
		str.Delete(str.GetLength()-1);
	iIndex=str.ReverseFind('\\');
	if (iIndex==-1)
	{
		AfxMessageBox(_T("输出路径错误! "));
		return bResult;
	}

	if (!_GetPackPath(strOut))
	{
		AfxMessageBox(_T("请先设置打包输出目录! "));
		return bResult;
	}

	if (_IsExistentFile(strOut))
	{
		if (AfxMessageBox(_T("目标文件已存在, 是否覆盖! "),MB_YESNO)==IDNO)
			return bResult;
	}

	if (myZip.Zip_PackFiles(str,strOut))
	{
		AfxMessageBox(_T("压缩成功! "));
		iIndex=GetPrivateProfileInt(COptionDlg::szOption,COptionDlg::szPackOpen,1,COptionDlg::szOptionFile);
		if (iIndex)
		{
			str=_T(" /select,");
			ShellExecute(m_hWnd,_T("open"),_T("Explorer.exe"),str+strOut,NULL,SW_SHOWNORMAL);
		}
		bResult=TRUE;
	}
	else
	{
		AfxMessageBox(_T("压缩失败! "));
	}

	return bResult;
}


void CZipTestDlg::OnCmdAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlg;
	dlg.DoModal();
}


void CZipTestDlg::OnCmdQuit()
{
	// TODO: 在此添加命令处理程序代码
	SendMessage(WM_CLOSE,NULL,NULL);
}


void CZipTestDlg::OnCmdSet()
{
	// TODO: 在此添加命令处理程序代码
	COptionDlg dlg;
	dlg.DoModal();
}


void CZipTestDlg::OnTvnSelchangedMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	int iIndex=0;

	m_wndPath.GetItemPath(str,pNMTreeView->itemNew.hItem);
	iIndex=str.ReverseFind('\\');
	if (iIndex==-1)
		return;
	str.Delete(0,iIndex+1);
	GetDlgItem(IDC_EDIT_OUT)->SetWindowText(str+_T(".g"));
	*pResult = 0;
}


BOOL CZipTestDlg::_ReadAppInfo()
{
	BOOL bResult=FALSE;



	return bResult;
}


BOOL CZipTestDlg::_GetPackPath(CString& strOut)
{
	BOOL bResult = FALSE;
	CString str,strPath;
	int iIndex=0;

	GetModuleFileName(GetModuleHandle(NULL),strPath.GetBuffer(MAX_PATH),MAX_PATH);
	strPath.ReleaseBuffer();
	iIndex = strPath.ReverseFind('\\');
	if (iIndex==-1)
		return bResult;
	strPath.Delete(iIndex,strPath.GetLength());
	GetPrivateProfileString(COptionDlg::szOption,COptionDlg::szPackPath,strPath.GetBuffer(),str.GetBuffer(MAX_PATH),MAX_PATH,COptionDlg::szOptionFile);
	strPath.ReleaseBuffer();
	str.ReleaseBuffer();
	GetDlgItem(IDC_EDIT_OUT)->GetWindowText(strPath);
	if (strPath.IsEmpty())
		return bResult;
	if (str.IsEmpty())
		return bResult;
	if (str.GetAt(str.GetLength() - 1) != '\\')
		str += _T("\\");
	strOut=str+strPath;
	bResult = TRUE;

	return bResult;
}


BOOL CZipTestDlg::_IsExistentFile(CString strFilePath)
{
	BOOL bResult=FALSE;
	HANDLE hFile=INVALID_HANDLE_VALUE;

	hFile=CreateFile(strFilePath.GetBuffer(),GENERIC_READ,FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	strFilePath.ReleaseBuffer();
	if (hFile!=INVALID_HANDLE_VALUE || GetLastError()!=2)
		bResult=TRUE;
	CloseHandle(hFile);

	return bResult;
}


void CZipTestDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码

	CDialogEx::OnCancel();
}


void CZipTestDlg::OnBnClickedBtnUnpack()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str,strOut;
	CZipImplement myZip;
	int iData=0;

	m_wndZip.GetWindowText(str);
	if (!_GetUnpackPath(strOut) || str.IsEmpty())
	{
		AfxMessageBox(_T("路径设置错误! "));
		return ;
	}

	_SetIniInfo(szUnpackHistory,str);

	if (myZip.Zip_UnPackFiles(str,strOut))
	{
		AfxMessageBox(_T("解压缩成功! "));
		iData=GetPrivateProfileInt(COptionDlg::szOption,COptionDlg::szUnpackOpen,1,COptionDlg::szOptionFile);
		if (iData)
		{
			iData=str.ReverseFind('\\');
			if (iData==-1)
				return;
			str.Delete(0,iData);
			iData=str.ReverseFind('.');
			if (iData==-1)
				return;
			str.Delete(iData,str.GetLength());
			strOut+=str;
			str=_T(" /select,");
			ShellExecute(m_hWnd,_T("open"),_T("Explorer.exe"),str+strOut,NULL,SW_SHOWNORMAL);
		}
	}
	else
	{
		AfxMessageBox(_T("解压缩失败! "));
	}
}


BOOL CZipTestDlg::_GetUnpackPath(CString& strOut)
{
	BOOL bResult=FALSE;
	CString str,strPath;
	int iIndex=0;

	GetModuleFileName(GetModuleHandle(NULL),str.GetBuffer(MAX_PATH),MAX_PATH);
	str.ReleaseBuffer();
	iIndex=str.ReverseFind('\\');
	if (iIndex==-1)
		return bResult;
	str.Delete(iIndex,str.GetLength());
	GetPrivateProfileString(COptionDlg::szOption,COptionDlg::szUnpackPath,str.GetBuffer(),strPath.GetBuffer(MAX_PATH),MAX_PATH,COptionDlg::szOptionFile);
	str.ReleaseBuffer();
	strPath.ReleaseBuffer();
	if (strPath.IsEmpty())
		strOut=str;
	else
		strOut=strPath;

	bResult=TRUE;

	return bResult;
}


void CZipTestDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	LPWSTR pBuff=new wchar_t[MAX_PATH];
	CString str;
	int iData=0,iCount=0;

	iCount =DragQueryFile(hDropInfo,-1,NULL,NULL);
	for (int i=0;i<iCount;i++)
	{
		iData=DragQueryFile(hDropInfo,i,pBuff,MAX_PATH);
		str=pBuff;
		if (str.Right(2)==_T(".g"))
			m_wndZip.SetWindowText(str);
		else
		{
			if (PathIsDirectory(pBuff))
				m_wndPath.SelectPath(pBuff);
		}
	}

	delete pBuff;
	CDialogEx::OnDropFiles(hDropInfo);
}


BOOL CZipTestDlg::_SetIniInfo(LPCTSTR pKey, CString& strVaule)
{
	BOOL bResult=FALSE;
	CString strPath,str;
	int iIndex=0;

	GetModuleFileName(GetModuleHandle(NULL),strPath.GetBuffer(MAX_PATH),MAX_PATH);
	strPath.ReleaseBuffer();
	iIndex=strPath.ReverseFind('\\');
	if (iIndex!=-1)
	{
		strPath.Delete(iIndex,strPath.GetLength());
		str=COptionDlg::szOptionFile;
		str.Delete(0);
		strPath+=str;
		WritePrivateProfileString(COptionDlg::szOption,pKey,strVaule.GetBuffer(),strPath.GetBuffer());
		strVaule.ReleaseBuffer();
		bResult=TRUE;
	}

	return bResult;
}
