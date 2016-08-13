
// ZipTestDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CZipTestDlg �Ի���




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


// CZipTestDlg ��Ϣ�������

BOOL CZipTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_wndPath.ModifyStyle(m_wndPath.GetSafeHwnd(),NULL,TVS_SHOWSELALWAYS,NULL);		//һֱ��ʾѡ����

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

	m_wndZip.EnableFileBrowseButton(_T("*.g"),_T("�Ѵ���ļ� (*.g)|*.g|ȫ���ļ� (*.*)|*.*||"));
		
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CZipTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CZipTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CZipTestDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		AfxMessageBox(_T("���·������! "));
		return bResult;
	}

	if (!_GetPackPath(strOut))
	{
		AfxMessageBox(_T("�������ô�����Ŀ¼! "));
		return bResult;
	}

	if (_IsExistentFile(strOut))
	{
		if (AfxMessageBox(_T("Ŀ���ļ��Ѵ���, �Ƿ񸲸�! "),MB_YESNO)==IDNO)
			return bResult;
	}

	if (myZip.Zip_PackFiles(str,strOut))
	{
		AfxMessageBox(_T("ѹ���ɹ�! "));
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
		AfxMessageBox(_T("ѹ��ʧ��! "));
	}

	return bResult;
}


void CZipTestDlg::OnCmdAbout()
{
	// TODO: �ڴ���������������
	CAboutDlg dlg;
	dlg.DoModal();
}


void CZipTestDlg::OnCmdQuit()
{
	// TODO: �ڴ���������������
	SendMessage(WM_CLOSE,NULL,NULL);
}


void CZipTestDlg::OnCmdSet()
{
	// TODO: �ڴ���������������
	COptionDlg dlg;
	dlg.DoModal();
}


void CZipTestDlg::OnTvnSelchangedMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CDialogEx::OnCancel();
}


void CZipTestDlg::OnBnClickedBtnUnpack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str,strOut;
	CZipImplement myZip;
	int iData=0;

	m_wndZip.GetWindowText(str);
	if (!_GetUnpackPath(strOut) || str.IsEmpty())
	{
		AfxMessageBox(_T("·�����ô���! "));
		return ;
	}

	_SetIniInfo(szUnpackHistory,str);

	if (myZip.Zip_UnPackFiles(str,strOut))
	{
		AfxMessageBox(_T("��ѹ���ɹ�! "));
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
		AfxMessageBox(_T("��ѹ��ʧ��! "));
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
