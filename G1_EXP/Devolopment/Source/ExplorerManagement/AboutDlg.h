
#pragma once
#include "resource.h"
#include "afxwin.h"

class CAboutDlg : public CDialog{
	DECLARE_DYNAMIC(CAboutDlg);

public:
	CAboutDlg(CWnd* pParent = NULL);
	virtual ~CAboutDlg();

	//Dialog data
	enum {IDD = IDD_ABOUTBOX};

protected:
	DECLARE_MESSAGE_MAP()
};