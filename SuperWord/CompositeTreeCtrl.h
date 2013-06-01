#pragma once

#include "Composite.h"
#include "Condition.h"
#include "CSRootDlg.h"
#include <vector>
#include <string>

using namespace comp;
using namespace compdlg;

struct CompInfo
{
    std::string compName;
    UINT idIcon;
    CCSRootDlg * pDlg;

    CompInfo();
    CompInfo(const std::string& compName, UINT idIcon, CCSRootDlg * pDlg = NULL);
    CompInfo(const CompInfo& ci);
private:
    void Set(const std::string& compName, UINT idIcon, CCSRootDlg *pDlg);
};

typedef std::vector<CompInfo> CompInfoVector;

class CCompositeTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CCompositeTreeCtrl)
	
public:
	CCompositeTreeCtrl();
	virtual ~CCompositeTreeCtrl();

	BOOL InitTree(const CompInfoVector * pvCi, Composite * pComp, 
		          const char * dftFile, const char * dftExt);

	BOOL LoadComposite(LPCTSTR pszFilename);
	BOOL SaveComposite(LPCTSTR pszFilename);

	BOOL Refresh();

private:
	Composite * m_pRootComp;
	const CompInfoVector* m_pvCi;
	CImageList  m_imgList;
    BOOL m_bDragging;
    BOOL m_bMoveOnDrop;
    HTREEITEM m_hItemToMove;
	std::string m_strDefaultFile;
	std::string m_strDefaultExt;

	// 在通过composite同步tree的过程中，居然也会有NM_CUSTOMDRAW消息到tree.
	// 此时tree还正在构造中，在NM_CUSTOMDRAW消息的响应函数中有代码通过item
	// 的handle来得到item对应的composite，因而得到的是不正确的。
	// 通过下面变量来告诉NM_CUSTOMDRAW消息的响应函数在tree的构造过程中不
	// 要通过item的handle来得到item对应的composite。
	BOOL m_bItemConstructing;

	BOOL LoadImages();
    // get the index of a compName in Composite Info Array
	size_t GetCompositeIndex(const std::string& compName) const;
    void ExpandSubItem(HTREEITEM hTree, UINT nCode);
    void DeleteSubItem(HTREEITEM hTree);
	void DeleteSubComposite(HTREEITEM hTree);
	BOOL SetTreeItem(HTREEITEM hTree, Composite *pComp);
	Composite * GetComposite(HTREEITEM hTree) const;
	BOOL ConstructTree(HTREEITEM hTree, Composite * pComp);
    BOOL AddChildOnSelectedItem(Composite * pNewComp);
    BOOL MoveTreeItem(HTREEITEM hTree, HTREEITEM hMoveTo);
    BOOL IsSubItemof(HTREEITEM hTree, HTREEITEM hTest) const;
    inline void SwitchCursor(UINT nIDCursor);
    void AddMenu(CMenu& mu, UINT nFlags, UINT_PTR nIDNewItem, 
        LPCTSTR lpszNewItem, BOOL bAdd, BOOL& bAdded) const;
    BOOL CreateCommonCompositeMenu(CMenu& mu, const Composite * pComp,
        BOOL bAdd) const;
    void RunContextMenu();
    BOOL SyncItemDescription(HTREEITEM hItem);

	enum ItemValidState{ valid, invalid, partly_valid };
	ItemValidState GetItemValidState(HTREEITEM hItem) const;

    // TODO bad smell
    enum CompositeAttr{leaf, component};
    static inline CompositeAttr GetCompositeAttr(const Composite * pComp)
    {
        return (dynamic_cast<const Leaf *>(pComp) ? leaf : component);
    }
    enum CompositeType{condition, command};
    static inline CompositeType GetCompositeType(const Composite * pComp)
    {
        return (dynamic_cast<const cond::Condition *>(pComp) ? condition : command);
    }

private:
	DECLARE_MESSAGE_MAP()
//	virtual void PreSubclassWindow();

	afx_msg void OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnAddComposite(UINT nID);
    afx_msg void OnChgComposite(UINT nID);
    afx_msg void OnAddCompositeFromFile();
    afx_msg void OnChgCompositeFromFile();
    afx_msg void OnDelComposite();
    afx_msg void OnSaveComposite();
    afx_msg void OnSetComposite();
    afx_msg void OnExpandComposite();
    afx_msg void OnCollapseComposite();
public:
    afx_msg void OnTvnItemexpanded(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
public:
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};


