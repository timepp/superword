// CompositeTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "SuperWord.h"
#include "CompositeTreeCtrl.h"
#include "CompositeCreator.h"
#include "RootComposite.h"

#include <fstream>
#include <memory>
#include ".\compositetreectrl.h"

using namespace compdlg;
using namespace std;

#define ID_ADD_COMPOSITE_BEGIN	            0x400
#define ID_ADD_COMPOSITE_END	            0x4ff
#define ID_CHG_COMPOSITE_BEGIN	            0x500
#define ID_CHG_COMPOSITE_END	            0x5ff
#define ID_DEL_COMPOSITE                    0x601
#define ID_SAVE_COMPOSITE                   0x602
#define ID_SET_COMPOSITE                    0x603
#define ID_ADD_COMPOSITE_FROM_FILE          0x604
#define ID_CHG_COMPOSITE_FROM_FILE          0x605
#define ID_EXPAND_COMPOSITE                 0x606
#define ID_COLLAPSE_COMPOSITE               0x607

#define IDT_EXPAND_ITEM                     1000

void CompInfo::Set(const std::string& compName, UINT idIcon, CCSRootDlg *pDlg)
{
	this->compName = compName;
	this->idIcon = idIcon;
	this->pDlg = pDlg;
}
CompInfo::CompInfo()
{
	Set("", 0, NULL);
}
CompInfo::CompInfo(const std::string& compName, UINT idIcon, CCSRootDlg * pDlg /* = NULL */)
{
	Set(compName, idIcon, pDlg);
}
CompInfo::CompInfo(const CompInfo& ci)
{
	Set(ci.compName, ci.idIcon, ci.pDlg);
}

// CCompositeTreeCtrl

IMPLEMENT_DYNAMIC(CCompositeTreeCtrl, CTreeCtrl)
CCompositeTreeCtrl::CCompositeTreeCtrl()
{
    m_pvCi = NULL;
    m_pRootComp = NULL;
    m_bDragging = FALSE;
    m_bMoveOnDrop = TRUE;
	m_bItemConstructing = FALSE;
}

CCompositeTreeCtrl::~CCompositeTreeCtrl()
{
}

size_t CCompositeTreeCtrl::GetCompositeIndex(const std::string& compName) const
{
	size_t i;
	for (i = 0; i < m_pvCi->size(); i++)
	{
		if ((*m_pvCi)[i].compName == compName)
			return i;
	}

	return 0;
}

BOOL CCompositeTreeCtrl::IsSubItemof(HTREEITEM hTree, HTREEITEM hTest) const
{
    do {
        hTree = GetParentItem(hTree);
        if (hTest == hTree) return TRUE;
    } while (hTree != TVI_ROOT && hTree != NULL);

    return FALSE;
}

void CCompositeTreeCtrl::ExpandSubItem(HTREEITEM hTree, UINT nCode)
{
    Expand(hTree, nCode);

    HTREEITEM hChildItem = GetChildItem(hTree);
    while (hChildItem != NULL)
    {
        ExpandSubItem(hChildItem, nCode);
        hChildItem = GetNextItem(hChildItem, TVGN_NEXT);
    }
}

void CCompositeTreeCtrl::DeleteSubItem(HTREEITEM hTree)
{
    HTREEITEM hNextItem;
    HTREEITEM hChildItem = GetChildItem(hTree);
    while (hChildItem != NULL)
    {
        hNextItem = GetNextItem(hChildItem, TVGN_NEXT);
        DeleteItem(hChildItem);
        hChildItem = hNextItem;
    }
}

BOOL CCompositeTreeCtrl::SyncItemDescription(HTREEITEM hItem)
{
    while (hItem != NULL && hItem != TVI_ROOT)
    {
        SetTreeItem(hItem, GetComposite(hItem));
        hItem = GetParentItem(hItem);
    }
    return TRUE;
}

CCompositeTreeCtrl::ItemValidState
CCompositeTreeCtrl::GetItemValidState(HTREEITEM hItem) const
{
	Composite * pComp = GetComposite(hItem);
	if (pComp == NULL || !pComp->CheckValid())
	{
		return invalid;
	}

	HTREEITEM hChildItem = GetChildItem(hItem);
	while (hChildItem != NULL)
	{
		if (GetItemValidState(hChildItem) != valid)
		{
			return partly_valid;
		}

		hChildItem = GetNextItem(hChildItem, TVGN_NEXT);
	}

	return valid;
}

Composite * CCompositeTreeCtrl::GetComposite(HTREEITEM hTree) const
{
	if (hTree == TVI_ROOT || hTree == NULL)
	{
		return m_pRootComp;
	}
	else
	{
		return (Composite *)GetItemData(hTree);
	}
}

void CCompositeTreeCtrl::DeleteSubComposite(HTREEITEM hTree)
{
	Composite * pComp = GetComposite(hTree);
    DeleteSubItem(hTree);
    pComp->ClearAll();
    SyncItemDescription(hTree);
}

BOOL CCompositeTreeCtrl::SetTreeItem(HTREEITEM hTree, Composite *pComp)
{
    if (hTree != TVI_ROOT && hTree != NULL)
    {
        int index = static_cast<int>(GetCompositeIndex(pComp->GetName()));
		string strDesc = pComp->GetDescription();
        SetItem(hTree,
            TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT,
            strDesc.c_str(), index, index, 0, 0, 0);
    }

    SetItemData(hTree, (DWORD_PTR)pComp);

	return TRUE;
}

BOOL CCompositeTreeCtrl::MoveTreeItem(HTREEITEM hTree, HTREEITEM hMoveTo)
{
    // Common Check
    if (hTree == NULL || hMoveTo == NULL) return FALSE;
    if (hTree == TVI_ROOT || hMoveTo == TVI_ROOT) return FALSE;
    if (hTree == hMoveTo) return FALSE;
    // Check if hTree and hMoveTo have proper relation
    if (IsSubItemof(hMoveTo, hTree))
    {
        return FALSE;
    }
    // Do Move!
    Composite * pComp = GetComposite(hTree);
    Composite * pNewComp;
    Composite * pCompMoveTo = GetComposite(hMoveTo);
    if (pCompMoveTo->HaveRoom() && pCompMoveTo->CanAddChild(pComp))
    {
        pNewComp = pComp->Clone();

        // If It's not copy, Remove old
        if (m_bMoveOnDrop)
        {
            HTREEITEM hParentItem = GetParentItem(hTree);
            Composite * pParentComp = GetComposite(hParentItem);
            pParentComp->DelChild(pComp);
            DeleteItem(hTree);
            SyncItemDescription(hParentItem);
        }

        // Insert new
        pCompMoveTo->AddChild(pNewComp);
        HTREEITEM hNewTree = InsertItem("", hMoveTo);
        ConstructTree(hNewTree, pNewComp);
        SyncItemDescription(hMoveTo);

        return TRUE;
    }

    return FALSE;
}

// 根据CompInfoVector的信息把需要用到的图标加载到imagelist中
BOOL CCompositeTreeCtrl::LoadImages()
{
	m_imgList.Create(16, 16, ILC_COLOR16 | ILC_MASK, 16, 16);
	m_imgList.SetBkColor(CLR_NONE);

	CompInfoVector::const_iterator ci;
	for (ci = m_pvCi->begin(); ci != m_pvCi->end(); ++ci)
	{
		m_imgList.Add(AfxGetApp()->LoadIcon(ci->idIcon));
	}
	
	return TRUE;
}

BOOL CCompositeTreeCtrl::InitTree(const CompInfoVector * pvCi, Composite * pComp, 
                                  const char * dftFile, const char * dftExt)
{
    m_pvCi = pvCi;
	m_pRootComp = pComp;
	m_strDefaultExt = dftExt;
	m_strDefaultFile = dftFile;

    LoadImages();
    SetImageList(&m_imgList, TVSIL_NORMAL);

	DeleteAllItems();
	ConstructTree(TVI_ROOT, m_pRootComp);

	return TRUE;
}

BOOL CCompositeTreeCtrl::ConstructTree(HTREEITEM hTree, Composite * pComp)
{
	m_bItemConstructing = TRUE;

    if (hTree != TVI_ROOT && hTree != NULL)
    {
        Composite * pOldComp = GetComposite(hTree);
        if (pOldComp != NULL)
        {
            HTREEITEM hParentTree = GetParentItem(hTree);
            Composite * pParentComp = GetComposite(hParentTree);
            pParentComp->ChgChild(pOldComp, pComp);
        }
    }

	DeleteSubItem(hTree);
	SetTreeItem(hTree, pComp);

    Composite * pSubComp;
    pComp->BeginEnumChild();
	while ((pSubComp = pComp->GetNextChild()) != NULL)
	{
		ConstructTree(InsertItem(_T(""), hTree), pSubComp);
	}

	m_bItemConstructing = FALSE;
	return TRUE;
}

BOOL CCompositeTreeCtrl::LoadComposite(LPCTSTR pszFilename)
{
	std::ifstream ifs(pszFilename);
	if (ifs)
	{
		DeleteSubComposite(TVI_ROOT);
		m_pRootComp->Read(ifs);
		if (Refresh())
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CCompositeTreeCtrl::Refresh()
{
	ConstructTree(TVI_ROOT, m_pRootComp);
	return TRUE;
}

BOOL CCompositeTreeCtrl::SaveComposite(LPCTSTR pszFilename)
{
    std::ofstream ofs(pszFilename);
    if (ofs)
    {
        m_pRootComp->Save(ofs);
        return TRUE;
    }

    return FALSE;
}

void CCompositeTreeCtrl::AddMenu(CMenu& mu, UINT nFlags, UINT_PTR nIDNewItem, 
                                 LPCTSTR lpszNewItem, BOOL bAdd, BOOL& bAdded) const
{
    if (bAdd)
    {
        if (mu.AppendMenu(nFlags, nIDNewItem, lpszNewItem))
        {
            bAdded = !(nFlags & MF_SEPARATOR);
        }
    }
}

BOOL CCompositeTreeCtrl::CreateCommonCompositeMenu(CMenu& mu, 
                                                   const Composite * pComp, 
                                                   BOOL bAdd) const
{
    BOOL bAdded = FALSE;
    Composite * pNewComp;
    UINT nIDStart = bAdd ? ID_ADD_COMPOSITE_BEGIN : ID_CHG_COMPOSITE_BEGIN;

    for (size_t i = 0; i < m_pvCi->size(); i++)
    {
        if ((*m_pvCi)[i].compName.empty())
        {
            mu.AppendMenu(MF_SEPARATOR);
        }
        else
        {
            const std::string& name = (*m_pvCi)[i].compName;
            pNewComp = CompositeCreator::Instance()->CreateComposite((*m_pvCi)[i].compName);

            if (bAdd && pComp->CanAddChild(pNewComp) ||
                !bAdd && GetCompositeType(pComp) == GetCompositeType(pNewComp))
            {
                bAdded = TRUE;
                mu.AppendMenu(MF_STRING, nIDStart + i, name.c_str());
            }

            delete pNewComp;
        }
    }

    return bAdded;
}

void CCompositeTreeCtrl::RunContextMenu()
{

    CPoint pt;
    GetCursorPos(&pt);
    HTREEITEM hTree = GetSelectedItem();
    Composite * pComp = GetComposite(hTree);

    CMenu mu, muAdd, muChg;
    mu.CreatePopupMenu();

    // Menu flags
    BOOL bCanAddSubChild = pComp->HaveRoom();
    BOOL bCanChgItem = (pComp != m_pRootComp);
    BOOL bCanDelItem = (pComp != m_pRootComp);
    BOOL bCanSetComp = ((*m_pvCi)[GetCompositeIndex(pComp->GetName())].pDlg != NULL);
    BOOL bHasChildren = ItemHasChildren(hTree);
    BOOL bHasMenu = FALSE;

    if (bCanAddSubChild)
    {
        muAdd.CreatePopupMenu();
        CreateCommonCompositeMenu(muAdd, pComp, TRUE);
        muAdd.AppendMenu(MF_SEPARATOR);
        muAdd.AppendMenu(MF_STRING, ID_ADD_COMPOSITE_FROM_FILE, "从文件导入...");
        AddMenu(mu, MF_POPUP, (UINT_PTR)muAdd.m_hMenu, "添加子项", TRUE, bHasMenu);
    }

    if (bCanChgItem)
    {
        muChg.CreatePopupMenu();
        CreateCommonCompositeMenu(muChg, pComp, FALSE);
        muChg.AppendMenu(MF_SEPARATOR);
        muChg.AppendMenu(MF_STRING, ID_CHG_COMPOSITE_FROM_FILE, "从文件导入...");
        AddMenu(mu, MF_POPUP, (UINT_PTR)muChg.m_hMenu, "切换为", TRUE, bHasMenu);
    }

    AddMenu(mu, MF_SEPARATOR, 0, NULL, bHasMenu, bHasMenu);

    AddMenu(mu, MF_STRING, ID_EXPAND_COMPOSITE, "展开全部", bHasChildren, bHasMenu);
    AddMenu(mu, MF_STRING, ID_COLLAPSE_COMPOSITE, "折叠全部", bHasChildren, bHasMenu);

    AddMenu(mu, MF_SEPARATOR, 0, NULL, bHasMenu, bHasMenu);

    AddMenu(mu, MF_STRING, ID_SET_COMPOSITE, "配置...", bCanSetComp, bHasMenu);
    AddMenu(mu, MF_STRING, ID_SAVE_COMPOSITE, "另存为...", TRUE, bHasMenu);

    if (bCanDelItem)
    {
        AddMenu(mu, MF_SEPARATOR, 0, NULL, bHasMenu, bHasMenu);
        AddMenu(mu, MF_STRING, ID_DEL_COMPOSITE, "删除", bCanDelItem, bHasMenu);
    }

    mu.TrackPopupMenu(0, pt.x, pt.y, this);
}

BEGIN_MESSAGE_MAP(CCompositeTreeCtrl, CTreeCtrl)
ON_NOTIFY_REFLECT(NM_RCLICK, OnNMRclick)
ON_COMMAND_RANGE(ID_ADD_COMPOSITE_BEGIN, ID_ADD_COMPOSITE_END, OnAddComposite)
ON_COMMAND_RANGE(ID_CHG_COMPOSITE_BEGIN, ID_CHG_COMPOSITE_END, OnChgComposite)
ON_COMMAND(ID_ADD_COMPOSITE_FROM_FILE, OnAddCompositeFromFile)
ON_COMMAND(ID_CHG_COMPOSITE_FROM_FILE, OnChgCompositeFromFile)
ON_COMMAND(ID_DEL_COMPOSITE, OnDelComposite)
ON_COMMAND(ID_SAVE_COMPOSITE, OnSaveComposite)
ON_COMMAND(ID_SET_COMPOSITE, OnSetComposite)
ON_COMMAND(ID_EXPAND_COMPOSITE, OnExpandComposite)
ON_COMMAND(ID_COLLAPSE_COMPOSITE, OnCollapseComposite)
//ON_NOTIFY_REFLECT(NM_DBLCLK, OnNMDblclk)
ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnTvnItemexpanded)
ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnTvnBegindrag)
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONUP()
ON_WM_TIMER()
ON_WM_KEYDOWN()
ON_WM_KEYUP()
ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnNMCustomdraw)
//ON_WM_CONTEXTMENU()
ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CCompositeTreeCtrl Message handler

void CCompositeTreeCtrl::OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_bDragging)
	{
		*pResult = 1;
		return;
	}

	CPoint pt;
    ::GetCursorPos(&pt);
    ScreenToClient(&pt);
    HTREEITEM hTree = HitTest(pt);
    SelectItem(hTree);

    RunContextMenu();

	*pResult = 0;
}


void CCompositeTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	HTREEITEM hItem = HitTest(point);
	if (!ItemHasChildren(hItem))
	{
		OnSetComposite();
	}

	CTreeCtrl::OnLButtonDblClk(nFlags, point);
}

void CCompositeTreeCtrl::OnSetComposite()
{
    HTREEITEM hItem = GetSelectedItem();
    Composite * pComp = GetComposite(hItem);

    size_t index = GetCompositeIndex(pComp->GetName());
    if ((*m_pvCi)[index].pDlg != NULL)
    {
		CCSRootDlg * pDlg = (*m_pvCi)[index].pDlg;
        pDlg->m_pComp = pComp;
        pDlg->DoModal();

        SetTreeItem(hItem, pComp);
        SyncItemDescription(hItem);
    }
}

BOOL CCompositeTreeCtrl::AddChildOnSelectedItem(Composite * pNewComp)
{
    HTREEITEM hItem = GetSelectedItem();
    HTREEITEM hSubItem;
    Composite * pComp = GetComposite(hItem);

	if (pComp->CanAddChild(pNewComp) && pComp->AddChild(pNewComp))
    {
        hSubItem = InsertItem("", hItem);
        ConstructTree(hSubItem, pNewComp);
        Expand(hItem, TVE_EXPAND);
        SyncItemDescription(hItem);
        return TRUE;
    }
    
    return FALSE;
}

void CCompositeTreeCtrl::OnAddComposite(UINT nID)
{
    std::string compName = (*m_pvCi)[nID - ID_ADD_COMPOSITE_BEGIN].compName;
    Composite * pNewComp = CompositeCreator::Instance()->CreateComposite(compName);

    if (!AddChildOnSelectedItem(pNewComp))
    {
        delete pNewComp;
    }
}

void CCompositeTreeCtrl::OnAddCompositeFromFile()
{
    Composite * pNewComp = NULL;
    Composite * pSubComp;
    RootComposite rcomp(unknown);

    CFileDialog dlg(TRUE, m_strDefaultExt.c_str(), m_strDefaultFile.c_str(), OFN_FILEMUSTEXIST);
    if (dlg.DoModal() == IDOK)
    {
        std::ifstream ifs((LPCTSTR)dlg.GetPathName());
        rcomp.Read(ifs);
        rcomp.BeginEnumChild();
        while ((pSubComp = rcomp.GetNextChild()) != NULL)
        {
            pNewComp = pSubComp->Clone();
            if (!AddChildOnSelectedItem(pNewComp))
            {
                delete pNewComp;
            }
        }

        rcomp.ClearAll();
    }
}

void CCompositeTreeCtrl::OnChgCompositeFromFile()
{
    Composite * pSubComp;
    RootComposite rcomp(unknown);

    CFileDialog dlg(TRUE, m_strDefaultExt.c_str(), m_strDefaultFile.c_str(), OFN_FILEMUSTEXIST);
    if (dlg.DoModal() == IDOK)
    {
        std::ifstream ifs((LPCTSTR)dlg.GetPathName());
        rcomp.Read(ifs);
        rcomp.BeginEnumChild();
        while ((pSubComp = rcomp.GetNextChild()) != NULL)
        {
            ConstructTree(GetSelectedItem(), pSubComp->Clone());
        }

        SyncItemDescription(GetSelectedItem());

        rcomp.ClearAll();
    }
}

void CCompositeTreeCtrl::OnChgComposite(UINT nID)
{
    HTREEITEM hItem = GetSelectedItem();
    Composite * pComp = GetComposite(hItem);
    Composite * pAddComp;

    std::string compName = (*m_pvCi)[nID - ID_CHG_COMPOSITE_BEGIN].compName;
    Composite * pNewComp = CompositeCreator::Instance()->CreateComposite(compName);

    pComp->BeginEnumChild();
    while (pNewComp->HaveRoom() && (pAddComp = pComp->GetNextChild()) != NULL)
    {
        pNewComp->AddChild(pAddComp->Clone());
    }

    ConstructTree(hItem, pNewComp);
    SyncItemDescription(hItem);
}

void CCompositeTreeCtrl::OnDelComposite()
{
    HTREEITEM hItem = GetSelectedItem();
    HTREEITEM hParentItem = GetParentItem(hItem);
    Composite * pComp = GetComposite(hItem);
    Composite * pParentComp = GetComposite(hParentItem);
    pParentComp->DelChild(pComp);
    DeleteItem(hItem);
    SyncItemDescription(hParentItem);
}

void CCompositeTreeCtrl::OnSaveComposite()
{
    Composite * pComp = GetComposite(GetSelectedItem());
    CFileDialog dlg(FALSE, m_strDefaultExt.c_str(), m_strDefaultFile.c_str(), OFN_OVERWRITEPROMPT);
    if (dlg.DoModal() == IDOK)
    {
        std::ofstream ofs((LPCTSTR)dlg.GetPathName());
        pComp->Save(ofs);
    }
}

void CCompositeTreeCtrl::OnExpandComposite()
{
    ExpandSubItem(GetSelectedItem(), TVE_EXPAND);
}

void CCompositeTreeCtrl::OnCollapseComposite()
{
    ExpandSubItem(GetSelectedItem(), TVE_COLLAPSE);
}


void CCompositeTreeCtrl::OnTvnItemexpanded(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    // Pretend the recursive call
    static BOOL bAnotherCall = FALSE;
    if (!bAnotherCall && (GetKeyState(VK_SHIFT) & 0x8000))
    {
        bAnotherCall = TRUE;
        ExpandSubItem(pNMTreeView->itemNew.hItem, pNMTreeView->action);
        EnsureVisible(pNMTreeView->itemNew.hItem);
    }
    bAnotherCall = FALSE;
    *pResult = 0;
}

void CCompositeTreeCtrl::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    m_hItemToMove = pNMTreeView->itemNew.hItem;
    std::auto_ptr<CImageList> pList(CreateDragImage(m_hItemToMove));
    
    ImageList_BeginDrag(pList->m_hImageList, 0, 0, 0);
    ImageList_DragEnter(m_hWnd, pNMTreeView->ptDrag.x, pNMTreeView->ptDrag.y);
    SetCapture();
    SwitchCursor(m_bMoveOnDrop? IDC_CURSOR_MOVE : IDC_CURSOR_COPY);

    m_bDragging = TRUE;
    *pResult = 0;
}

void CCompositeTreeCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_bDragging)
    {
        ImageList_DragMove(point.x, point.y);
		ImageList_DragShowNolock(FALSE);

        HTREEITEM hItem = HitTest(point);
        if (hItem != NULL && hItem != TVI_ROOT)
        {
            SelectDropTarget(hItem);
            KillTimer(IDT_EXPAND_ITEM);
            if (ItemHasChildren(hItem) && 
                !(GetItemState(hItem, TVIF_STATE) & TVIS_EXPANDED))
            {
                // If mouse still hover on this item 1 second later, we will 
                // expand the item.
                SetTimer(IDT_EXPAND_ITEM, 1000, NULL);
            }
            EnsureVisible(GetPrevVisibleItem(hItem));
            EnsureVisible(hItem);
        }
        ImageList_DragShowNolock(TRUE);
    }

    CTreeCtrl::OnMouseMove(nFlags, point);
}

void CCompositeTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
    CTreeCtrl::OnLButtonUp(nFlags, point);
    if (m_bDragging)
    {
        ImageList_DragLeave(m_hWnd);
        ImageList_EndDrag();

        HTREEITEM hItemTarget = HitTest(point);
        if (MoveTreeItem(m_hItemToMove, hItemTarget))
        {
            SelectItem(hItemTarget);
            Expand(hItemTarget, TVE_EXPAND);
            EnsureVisible(hItemTarget);
        }

		ReleaseCapture();
		m_bDragging = FALSE;
		SelectDropTarget(NULL);
		RedrawWindow();
    }
}

void CCompositeTreeCtrl::OnTimer(UINT nIDEvent)
{
    if (nIDEvent == IDT_EXPAND_ITEM)
    {
        KillTimer(nIDEvent);
        ImageList_DragShowNolock(FALSE);

        Expand(GetDropHilightItem(), TVE_EXPAND);

        ImageList_DragShowNolock(TRUE);
    }
    
    CTreeCtrl::OnTimer(nIDEvent);
}

void CCompositeTreeCtrl::SwitchCursor(UINT nIDCursor)
{
    ::SetCursor(::LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(nIDCursor)));
}

void CCompositeTreeCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (nChar == VK_CONTROL)
    {
        m_bMoveOnDrop = FALSE;
        if (m_bDragging)
        {
            SwitchCursor(IDC_CURSOR_COPY);
        }
    }

    CTreeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCompositeTreeCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_CONTROL:
		m_bMoveOnDrop = TRUE;
		if (m_bDragging)
		{
			SwitchCursor(IDC_CURSOR_MOVE);
		}
		break;
	case VK_DELETE:
		OnDelComposite();
		break;    
	default:
		break;
    }

    CTreeCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CCompositeTreeCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	COLORREF crInvalid = RGB(255, 0, 0);
	COLORREF crPartlyInvalid = RGB(192, 0, 0);
	ItemValidState state;

	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	switch (pNMCD->dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_ITEMPREPAINT:
		if (!(pNMCD->uItemState & CDIS_FOCUS))
		{
			// TODO 很奇怪，有一些情况下dwItemSpec并不存在于树视图中！
			// 检查是否有一个item的handle是"dwItemSpec",这样做都不行
			// 重现：在有些单词命令全部展开时加载另一背诵方案
			if (!m_bItemConstructing)
			{
				state = GetItemValidState((HTREEITEM)pNMCD->dwItemSpec);
				if (state == invalid)
				{
					::SetTextColor(pNMCD->hdc, crInvalid);
				}
				else if (state == partly_valid)
				{
					::SetTextColor(pNMCD->hdc, crPartlyInvalid);
				}
			}

			*pResult = CDRF_DODEFAULT;
		}
		break;
	default:
		*pResult = CDRF_DODEFAULT;
	}
}


