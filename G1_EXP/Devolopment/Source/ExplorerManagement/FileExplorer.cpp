/******************************************************************************
**********
* ++
* Author : 
* Module Name : FileExplorer.cpp
* Decsription : Khởi tạo và thiết lập các chế độ hiển thị và hiển thị danh sách các item 
				chỉ định (path) lên giao diện.
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
* Mod. History : 26.06.2015 - Full Name
*							  FileExplorer.h
*
*				CR# Explorer
*--
*******************************************************************************
**********/


#include "stdafx.h"
#include "FileExplorer.h"


/****************************************************************************** 
* ++
* Method name : CFileExplorer::CreateCOM()
* Description : Dùng để khởi tạo đôi tượng COM
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
* 
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
* Parameters : 
*			Input : none
*			Output : None
*
* Global Variables
* Accessed : m_pIExplorerBrowser
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

void CFileExplorer::CreateCOM(){
	ATLASSERT(NULL == m_pIExplorerBrowser);
	HRESULT hr = CoCreateInstance(CLSID_ExplorerBrowser, NULL,
		CLSCTX_INPROC, IID_PPV_ARGS(&m_pIExplorerBrowser));

	ATLENSURE_SUCCEEDED(hr); 
}

/****************************************************************************** 
* ++
* Method name : CFileExplorer::HienThi()
* Description : Thiết lập chê độ hiển thị lên giao diện hiện tại,
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
* 
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
* Parameters : 
*			Input : dwOptions dùng nhận giá trị từ người dùng.
*			Output : None
*
* Global Variables
* Accessed : m_pIExplorerBrowser
* Modified : none
*
* Return values : none
*
* Modifications : 26.06.2015 - Nguyễn Minh Hiền
* Function first created : CFileExplorer:: CreateCOM();
* CR/PN# - Explorer
* Description 
* * -- 
*****************************************************************************/

void CFileExplorer::HienThi(EXPLORER_BROWSER_OPTIONS dwOptions)
{
	ATLASSERT(NULL != m_pIExplorerBrowser);
	HRESULT hr = m_pIExplorerBrowser->SetOptions(dwOptions);
	ATLENSURE_SUCCEEDED(hr); 
}

/***************************************************************************
* ++
* Method name : CFileExplorer :: KhoiTaoGiaoDien()
* Description : Khởi tạo vị trí và chế độ hiển thị các Folder lên cửa sổ cha.
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
* Paramaters : 
*			Input : hWndParent : Chỉ định cửa số cha để khởi tạo.
*					rc : Vị trí cửa sổ tra khi ứng dụng chạy đầu tiên
*					nViewMode : Chế độ hiển thị các Folder và File.
*			Output : none
* Global Variables
* Accessed : m_pIExplorerBrowser
* Modified : none
*
* Return values : none
*
* Modifycation : 26.06.2015 - Nguyễn Khánh Duy
* Function first created : CFileExplorer:: CreateCOM();
* CR/PN# - Explorer
* Description
* --
****************************************************************************/
void CFileExplorer::KhoiTaoGiaoDien(HWND hWndParent, const CRect &rc,
	UINT nViewMode, UINT flags){
	ATLENSURE(NULL != m_pIExplorerBrowser);
	FOLDERSETTINGS folderSettings = { 0 };
	folderSettings.ViewMode = nViewMode;
	folderSettings.fFlags = flags;
	HRESULT hr = m_pIExplorerBrowser->Initialize(hWndParent, rc, &folderSettings);
	ATLENSURE_SUCCEEDED(hr);
}

/***************************************************************************
* ++
* Method name : CFileExplorer :: ViTriCuaSo()
* Description : Thiết lập vị trí hiển thị của sổ.
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
* Paramaters : 
*			Input : rc là Vị trí cửa sổ khi ứng dụng chạy đầu tiên
*			Output : none
* Global Variables
* Accessed : m_pIExplorerBrowser
* Modified : none
*
* Return values : none
*
* Modifycation : 26.06.2015 - Trần Nhật Nguyên
* Function first created : CFileExplorer:: CreateCOM();
* CR/PN# - Explorer
* Description
* --
****************************************************************************/
void CFileExplorer::ViTriCuaSo(const CRect& rc){
	ATLASSERT(NULL != m_pIExplorerBrowser);
	m_pIExplorerBrowser->SetRect(NULL, rc);
}

/***************************************************************************
* ++
* Method name : CFileExplorer :: HienThiThuMuc()
* Description : Hàm này dùng để hiển thị danh sách các folder và file theo đường dẫn chỉ định.
*				Khi ứng dụng được khởi chạy thì ứng dụng sễ hiển thị danh sách ổ đĩa và Folder có trong
*				hệ thống theo đường dẫn chỉ định.
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
* Paramaters : 
*			Input : pszPath là một biến con trỏ dùng để trỏ đến đường dẫn thư mục cần trỏ đến.
*			Output : none
* Global Variables
* Accessed : m_pIExplorerBrowser
* Modified : none
*
* Return values : none
*
* Modifycation : 26.06.2015 - Nguyễn Khánh Duy
* Function first created : CFileExplorer:: CreateCOM();
* CR/PN# - Explorer
* Description
* --
****************************************************************************/
void CFileExplorer::HienThiThuMuc(LPCTSTR pszPath){
	ATLENSURE(NULL != m_pIExplorerBrowser); //no vaild IExplorer instance

	//get PIDL from path name
	CStringW strPath(pszPath);
	LPITEMIDLIST pidl = NULL;
	/*Hiển thỉ danh sách các danh mục chỉ dịnh
	kết quả trả về thuộc tính của đối tượng*/
	HRESULT hr = ::SHParseDisplayName(strPath, NULL, &pidl, 0, NULL);
	ATLENSURE_SUCCEEDED(hr); //throw exception in case of failure
	//browser to PIDL
	hr = m_pIExplorerBrowser->BrowseToIDList(pidl, SBSP_ABSOLUTE);
	//Nếu thất bại, giải phóng bộ nhớ danh sách các pidl
	if (FAILED(hr)){
		::ILFree(pidl);
		AtlThrow(hr);
	}
	::ILFree(pidl);
}

/***************************************************************************
* ++
* Method name : CFileExplorer :: SmallIcons(), :: LargeIcons(),
*				:: MediumIcons(), :: Details()
* Description : Tất cả các hàm là các tùy chọn dùng để thiết lập chế độ hiển
*				giao diện.
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
* Paramaters : 
*			Input : none
*			Output : none
* Global Variables
* Accessed : m_pIExplorerBrowser
* Modified : none
*
* Return values : none
*
* Modifycation : 26.06.2015 - Nguyễn Minh Hiền
* Function first created : CFileExplorer:: Create();
* CR/PN# - Explorer
* Description
* --
****************************************************************************/

void CFileExplorer :: SmallIcons(){
	UINT mode;
	mode = FVM_SMALLICON;
	FOLDERSETTINGS fd = {mode, 0};
	m_pIExplorerBrowser -> SetFolderSettings(&fd);
}

void CFileExplorer :: LargeIcons(){
	UINT mode;
	mode = FVM_TILE;
	FOLDERSETTINGS fd = {mode, 0};
	m_pIExplorerBrowser -> SetFolderSettings(&fd);
}

void CFileExplorer :: MediumIcons(){
	UINT mode;
	mode = FVM_ICON;
	FOLDERSETTINGS fd = {mode, 0};
	m_pIExplorerBrowser -> SetFolderSettings(&fd);
}

void CFileExplorer :: Details(){
	UINT mode;
	mode = FVM_DETAILS;
	FOLDERSETTINGS fd = {mode, 0};
	m_pIExplorerBrowser -> SetFolderSettings(&fd);
}

/***************************************************************************
* ++
* Method name : OnBack()
* Description : Trở về cửa số trước đó
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
* Paramaters : 
*			Input : none
*			Output : none
* Global Variables
* Accessed : m_pIExplorerBrowser
* Modified : none
*
* Return values : none
*
* Modifycation : 26.06.2015 - Trần Nhật Nguyên
* Function first created : CFileExplorer:: CreateCOM();
* CR/PN# - Explorer
* Description
* --
****************************************************************************/
void CFileExplorer::OnBack(){
	m_pIExplorerBrowser->BrowseToIDList(NULL, SBSP_NAVIGATEBACK);
}

/***************************************************************************
* ++
* Method name : OnForward()
* Description : Trở về cửa sau đó.
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
* Paramaters : 
*			Input : none
*			Output : none
* Global Variables
* Accessed : m_pIExplorerBrowser
* Modified : none
*
* Return values : none
*
* Modifycation : 26.06.2015 - Trần Nhật Nguyên
* Function first created : CFileExplorer:: CreateCOM();
* CR/PN# - Explorer
* Description
* --
****************************************************************************/
void CFileExplorer::OnForward(){
	m_pIExplorerBrowser->BrowseToIDList(NULL, SBSP_NAVIGATEFORWARD);
}
