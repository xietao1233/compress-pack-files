#pragma once


// COptionDlg 对话框

class COptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COptionDlg)

public:
	COptionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COptionDlg();
	const static TCHAR szOptionFile[];
	const static TCHAR szOption[];
	const static TCHAR szPackPath[];
	const static TCHAR szUnpackPath[];
	const static TCHAR szPackOpen[];
	const static TCHAR szUnpackOpen[];

// 对话框数据
	enum { IDD = IDD_DLG_OPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	BOOL _ReadAppInfo(void);
};
