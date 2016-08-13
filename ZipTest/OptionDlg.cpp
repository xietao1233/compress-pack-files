// OptionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ZipTest.h"
#include "OptionDlg.h"
#include "afxdialogex.h"

const TCHAR COptionDlg::szOptionFile[]={_T(".\\Option.dat")};
const TCHAR COptionDlg::szOption[]={_T("OPTION")};
const TCHAR COptionDlg::szPackPath[]={_T("PackPath")};
const TCHAR COptionDlg::szUnpackPath[]={_T("UnpackPath")};
const TCHAR COptionDlg::szPackOpen[]={_T("OpenPackDir")};
const TCHAR COptionDlg::szUnpackOpen[]={_T("OpenUnpackDir")};

// COptionDlg �Ի���

IMPLEMENT_DYNAMIC(COptionDlg, CDialogEx)

COptionDlg::COptionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COptionDlg::IDD, pParent)
{

}

COptionDlg::~COptionDlg()
{
}

void COptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COptionDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &COptionDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// COptionDlg ��Ϣ�������


BOOL COptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (!_ReadAppInfo())
	{
		((CButton*)GetDlgItem(IDC_CHECK_PACK))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_UNPACK))->SetCheck(TRUE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void COptionDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	int i=0;

	GetDlgItem(IDC_EDIT_PACKPATH)->GetWindowText(str);
	WritePrivateProfileString(szOption,szPackPath,str.GetBuffer(),szOptionFile);
	str.ReleaseBuffer();
	GetDlgItem(IDC_EDIT_UNPACKPATH)->GetWindowText(str);
	WritePrivateProfileString(szOption,szUnpackPath,str.GetBuffer(),szOptionFile);
	str.ReleaseBuffer();
	i = ((CButton*)GetDlgItem(IDC_CHECK_PACK))->GetCheck();
	str=(i?_T("1"):_T("0"));
	WritePrivateProfileString(szOption,szPackOpen,str.GetBuffer(),szOptionFile);
	str.ReleaseBuffer();
	i = ((CButton*)GetDlgItem(IDC_CHECK_UNPACK))->GetCheck();
	str=(i?_T("1"):_T("0"));
	WritePrivateProfileString(szOption,szUnpackOpen,str.GetBuffer(),szOptionFile);
	str.ReleaseBuffer();


	CDialogEx::OnOK();
}


BOOL COptionDlg::_ReadAppInfo()
{
	BOOL bResult=FALSE;
	CString str;
	int iData=0;

	GetPrivateProfileString(szOption,szPackPath,_T(""),str.GetBuffer(MAX_PATH),MAX_PATH,szOptionFile);
	str.ReleaseBuffer();
	GetDlgItem(IDC_EDIT_PACKPATH)->SetWindowText(str);
	GetPrivateProfileString(szOption,szUnpackPath,_T(""),str.GetBuffer(MAX_PATH),MAX_PATH,szOptionFile);
	str.ReleaseBuffer();
	GetDlgItem(IDC_EDIT_UNPACKPATH)->SetWindowText(str);
	iData = GetPrivateProfileInt(szOption,szPackOpen,1,szOptionFile);
	((CButton*)GetDlgItem(IDC_CHECK_PACK))->SetCheck(iData);
	iData = GetPrivateProfileInt(szOption,szUnpackOpen,1,szOptionFile);
	((CButton*)GetDlgItem(IDC_CHECK_UNPACK))->SetCheck(iData);

	bResult=TRUE;

	return bResult;
}
