
// ZipTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CZipTestApp:
// �йش����ʵ�֣������ ZipTest.cpp
//

class CZipTestApp : public CWinApp
{
public:
	CZipTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CZipTestApp theApp;