
/******************************************************************************
**********
* ++
* Author : 
* Module Name : FileExplorer.h
* Decsription : Định nghĩa lớp gồm các biến, các hàm và các chức năng.
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
* Mod. History : 26.06.2015 - Trần Nhật Nguyên
*
*				CR# Explorer
*--
*******************************************************************************
**********/
// FileExplorerView.h : interface of the CFileExploreView class
//

#pragma once

#include "FileExplorer.h"

 class CFileExploreView : public CView {

private:
	CFileExplorer m_fileExplorer;
protected: // create from serialization only
	CFileExploreView();
	DECLARE_DYNCREATE(CFileExploreView)

// Attributes
public:
	CExplorerManagementDoc* GetDocument() const;

// Operations
public:

// Overrides
protected:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

// Implementation
public:
	virtual ~CFileExploreView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSmallIcons(); 
	afx_msg void OnLargeIcons();
	afx_msg void Details();
	afx_msg void OnMediumIcons();
	afx_msg void Back();
	afx_msg void Forward();
	afx_msg void Rename();
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int x, int y);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

};

#ifndef _DEBUG  // debug version in FileExplorerView.cpp
inline CExplorerManagementDoc* CFileExploreView::GetDocument() const
   { return reinterpret_cast<CExplorerManagementDoc*>(m_pDocument); }
#endif
