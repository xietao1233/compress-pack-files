
// ZipTestDlg.h : ͷ�ļ�
//

#pragma once
#include "afxshelltreectrl.h"
#include "afxeditbrowsectrl.h"


// CZipTestDlg �Ի���
class CZipTestDlg : public CDialogEx
{
// ����
public:
	CZipTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ZIPTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CMFCShellTreeCtrl m_wndPath;
	CMFCEditBrowseCtrl m_wndZip;
	BOOL _ZipPack(CString& strPath);
	afx_msg void OnCmdAbout();
	afx_msg void OnCmdQuit();
	afx_msg void OnCmdSet();
	afx_msg void OnTvnSelchangedMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL _ReadAppInfo(void);
	BOOL _GetPackPath(CString& strPath);
	BOOL _IsExistentFile(CString strFilePath);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnUnpack();
	BOOL _GetUnpackPath(CString& strPath);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	BOOL _SetIniInfo(LPCTSTR pKey, CString& strVaule);
};
