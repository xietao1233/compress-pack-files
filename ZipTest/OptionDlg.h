#pragma once


// COptionDlg �Ի���

class COptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COptionDlg)

public:
	COptionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COptionDlg();
	const static TCHAR szOptionFile[];
	const static TCHAR szOption[];
	const static TCHAR szPackPath[];
	const static TCHAR szUnpackPath[];
	const static TCHAR szPackOpen[];
	const static TCHAR szUnpackOpen[];

// �Ի�������
	enum { IDD = IDD_DLG_OPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	BOOL _ReadAppInfo(void);
};
