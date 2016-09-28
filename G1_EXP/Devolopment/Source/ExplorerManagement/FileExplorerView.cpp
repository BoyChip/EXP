
// FileExplorerView.cpp : implementation of the CFileExploreView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ExplorerManagement.h"
#endif

#include "ExplorerManagementDoc.h"
#include "FileExplorerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileExploreView

IMPLEMENT_DYNCREATE(CFileExploreView, CView)

BEGIN_MESSAGE_MAP(CFileExploreView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFileExploreView::OnFilePrintPreview)
	ON_COMMAND(ID_VIEW_SMALLICONS, &CFileExploreView::OnSmallIcons)
	ON_COMMAND(ID_VIEW_LARGEICONS, &CFileExploreView::OnLargeIcons)
	ON_COMMAND(ID_VIEW_DETAILS, &CFileExploreView::Details)
	ON_COMMAND(ID_VIEW_MEDIUMICONS, &CFileExploreView::OnMediumIcons)
	ON_COMMAND(ID_BACK, &CFileExploreView::Back)
	ON_COMMAND(ID_FORWARD, &CFileExploreView::Forward)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CFileExploreView construction/destruction

CFileExploreView::CFileExploreView()
{
	// TODO: add construction code here

}

CFileExploreView::~CFileExploreView()
{
}

BOOL CFileExploreView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CFileExploreView drawing

void CFileExploreView::OnDraw(CDC* /*pDC*/)
{
	CExplorerManagementDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CFileExploreView printing


void CFileExploreView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFileExploreView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFileExploreView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFileExploreView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CFileExploreView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFileExploreView::OnContextMenu(CWnd* pWnd, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, FALSE);
#endif
}


// CFileExploreView diagnostics

#ifdef _DEBUG
void CFileExploreView::AssertValid() const
{
	CView::AssertValid();
}

void CFileExploreView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExplorerManagementDoc* CFileExploreView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExplorerManagementDoc)));
	return (CExplorerManagementDoc*)m_pDocument;
}
#endif //_DEBUG


// CFileExploreView message handlers


/****************************************************************************** 
* ++
* Method name : CFileExplorer::OnSize()
* Description : Tạo ra cửa sồ Windows
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
* 
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
* Parameters : 
*			Input : lpCreateStruct: Chứa thông tin về các đối tượng CWnd được tạo ra.
*			Output : None
*
* Global Variables
* Accessed : m_fileExplorer
* Modified : none
*
* Return values : none
*
* Modifications : 26.06.2015 - Nguyễn Trọng Phương
* Function first created :
* CR/PN# - Explorer
* Description 
* * -- 
*****************************************************************************/
int CFileExploreView::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if(CView :: OnCreate(lpCreateStruct) == -1){
		return -1;
	}

	try{

		m_fileExplorer.CreateCOM();//Khởi tạo đối tượng COM
		m_fileExplorer.HienThi(EBO_SHOWFRAMES|EBO_ALWAYSNAVIGATE);
		//Khởi tạo vị trí cửa chính, chế độ hiển thị các Folder và File.
		m_fileExplorer.KhoiTaoGiaoDien(m_hWnd, CRect(0, 0, 0, 0), FVM_DETAILS, FWF_NONE);
	}
	catch(COleException* e){
		e->ReportError();
		e->Delete();
		return -1;
	}
	return 0;
}

/****************************************************************************** 
* ++
* Method name : CFileExplorer::OnSize()
* Description : Kích thước của cửa sổ khi ứng dựng được chạy.
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
* 
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
* Parameters : 
*			Input : nType : Quy định các loại kích thước thay đổi theo yêu cầu.
*					x : Tọa độ cửa sổ theo chiều trục ox.
*					y : Tọa độ cửa số theo trục oy.
*			Output : None
*
* Global Variables
* Accessed : m_fileExplorer
* Modified : none
*
* Return values : none
*
* Modifications : 26.06.2015 - Nguyễn Trọng Phương
* Function first created :
* CR/PN# - Explorer
* Description 
* * -- 
*****************************************************************************/
void CFileExploreView::OnSize(UINT nType, int x, int y){
	CView::OnSize(nType, x, y);
	m_fileExplorer.ViTriCuaSo(CRect(0, 0, x, y));
}

/****************************************************************************** 
* ++
* Method name : CFileExplorer::OnUpdate()
* Description : Đây là một hàm ảo dùng để cập nhận và hiển thị lại giao diện mỗi khi có sự thay đổi
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
* 
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
* Parameters : 
*			Input : pSender : Cập nhật lại giao diện khi có sự thay đổi
*					lHint : Chứa thông tin về những thay đổi
*					pHint : Trỏ đến thông tin lưu trữ của đối tượng thay đổi
*			Output : None
*
* Global Variables
* Accessed : m_fileExplorer
* Modified : none
*
* Return values : none
*
* Modifications : 26.06.2015 - Nguyễn Khánh Duy
* Function first created :
* CR/PN# - Explorer
* Description 
* * -- 
*****************************************************************************/
void CFileExploreView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint){
	TCHAR pszDesktopFolder[MAX_PATH] = {0};
	//Dùng để lấy folder chi định
	::SHGetFolderPath(NULL, CSIDL_DESKTOP, NULL, SHGFP_TYPE_CURRENT, pszDesktopFolder);
	m_fileExplorer.HienThiThuMuc(pszDesktopFolder);
}

BOOL CFileExploreView::OnEraseBkgnd(CDC* pDC){
	return FALSE;
}

void CFileExploreView :: OnSmallIcons(){
	m_fileExplorer.SmallIcons();
}

void CFileExploreView :: OnLargeIcons(){
	m_fileExplorer.LargeIcons();
}

void CFileExploreView :: OnMediumIcons(){
	m_fileExplorer.MediumIcons();
}

void CFileExploreView :: Details(){
	m_fileExplorer.Details();
}

void CFileExploreView::Back(){
	m_fileExplorer.OnBack();
}

void CFileExploreView::Forward(){
	m_fileExplorer.OnForward();
}

