#include "stdafx.h"
#include "AboutDlg.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CAboutDlg, CDialog)

CAboutDlg::CAboutDlg(CWnd* pParent) : CDialog(CAboutDlg::IDD, pParent){

}

CAboutDlg::~CAboutDlg(){

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()