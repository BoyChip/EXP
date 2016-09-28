
// ExplorerManagement.h : main header file for the ExplorerManagement application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CExplorerManagementApp:
// See ExplorerManagement.cpp for the implementation of this class
//

class CExplorerManagementApp : public CWinAppEx
{
public:
	CExplorerManagementApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	BOOL  m_bHiColorIcons;
	UINT m_nAppLook;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CExplorerManagementApp theApp;
