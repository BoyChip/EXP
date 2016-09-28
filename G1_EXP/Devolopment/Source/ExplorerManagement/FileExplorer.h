
/******************************************************************************
**********
* ++
* Author : 
* Module Name : FileExplorer.h
* Decsription : Định nghĩa lớp gồm các biến, các hàm.
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
* Mod. History : 26.06.2015 - Nguyễn Khánh Duy
*
*				CR# Explorer
*--
*******************************************************************************
**********/


class CFileExplorer : public CObject{
private:
	CComPtr<IExplorerBrowser> m_pIExplorerBrowser;

public:
	void CreateCOM();
	void HienThi(EXPLORER_BROWSER_OPTIONS dwOption);
	void KhoiTaoGiaoDien(HWND hWndParent, const CRect& rc, 
		UINT nViewMode, UINT nFlags);
	void ViTriCuaSo (const CRect& rc);
	void HienThiThuMuc(LPCTSTR pszPath);
	void SmallIcons ();
	void LargeIcons ();
	void MediumIcons ();
	void Details ();
	void OnBack();
	void OnForward();

	void Delete(CString pszPath);
	void Copy(LPCTSTR pszResource, LPCTSTR pszDest);
	void Rename(LPCTSTR pszResource, LPCTSTR pszDest);
};