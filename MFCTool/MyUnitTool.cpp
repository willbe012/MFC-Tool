// MyUnitTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "MyUnitTool.h"
#include "afxdialogex.h"

#include "MFCToolView.h"
#include "MainFrm.h"
#include "ObjectManager.h"


// CMyUnitTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMyUnitTool, CDialog)

CMyUnitTool::CMyUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MYUNITTOOL, pParent)
{
	m_iSize = { 0.f, 0.f, 0.f };
}

CMyUnitTool::~CMyUnitTool()
{
}

void CMyUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, m_iSize.x);
	DDX_Text(pDX, IDC_EDIT2, m_iSize.y);


}


BEGIN_MESSAGE_MAP(CMyUnitTool, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &CMyUnitTool::OnBnClickedPickPinky)
	ON_BN_CLICKED(IDC_RADIO2, &CMyUnitTool::OnBnClickedPickRaff)
	ON_BN_CLICKED(IDC_RADIO3, &CMyUnitTool::OnBnClickedPickBiu)
	ON_BN_CLICKED(IDC_RADIO4, &CMyUnitTool::OnBnClickedPickTile)
	ON_BN_CLICKED(IDC_CHECK1, &CMyUnitTool::OnBnClickedRenderHitBox)
	ON_BN_CLICKED(IDC_BUTTONDELETETHIS, &CMyUnitTool::OnBnClickedDeleteObject)
	ON_BN_CLICKED(IDC_BUTTONDELETEALL, &CMyUnitTool::OnBnClickedDeleteAll)
	ON_BN_CLICKED(IDC_BUTTONSIZE, &CMyUnitTool::OnBnClickedResizing)
	ON_BN_CLICKED(IDC_BUTTONDELETELAST, &CMyUnitTool::OnBnClickedDeleteLastPick)
END_MESSAGE_MAP()


// CMyUnitTool 메시지 처리기입니다.


void CMyUnitTool::OnBnClickedPickPinky()
{
	UpdateData(TRUE);
	CMainFrame* pMain = (CMainFrame*)(AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_tMainSplitterWnd.GetPane(0, 0));


	pView->m_ePickingObject = OBJID::PINKY;


	pView->Invalidate(FALSE);
	UpdateData(FALSE);
}


void CMyUnitTool::OnBnClickedPickRaff()
{
	UpdateData(TRUE);
	CMainFrame* pMain = (CMainFrame*)(AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_tMainSplitterWnd.GetPane(0, 0));

	pView->m_ePickingObject = OBJID::RAFF;

	pView->Invalidate(FALSE);
	UpdateData(FALSE);
}


void CMyUnitTool::OnBnClickedPickBiu()
{
	UpdateData(TRUE);
	CMainFrame* pMain = (CMainFrame*)(AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_tMainSplitterWnd.GetPane(0, 0));

	pView->m_ePickingObject = OBJID::BIU;

	pView->Invalidate(FALSE);
	UpdateData(FALSE);
}


void CMyUnitTool::OnBnClickedPickTile()
{
	UpdateData(TRUE);
	CMainFrame* pMain = (CMainFrame*)(AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_tMainSplitterWnd.GetPane(0, 0));

	pView->m_ePickingObject = OBJID::TILE;

	pView->Invalidate(FALSE);
	UpdateData(FALSE);
}


void CMyUnitTool::OnBnClickedRenderHitBox()
{
	UpdateData(TRUE);
	CMainFrame* pMain = (CMainFrame*)(AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_tMainSplitterWnd.GetPane(0, 0));

	CObjectManager::Get_Instance()->Set_RenderHitBox();

	pView->Invalidate(FALSE);
	UpdateData(FALSE);
}


void CMyUnitTool::OnBnClickedDeleteObject()
{
	UpdateData(TRUE);
	CMainFrame* pMain = (CMainFrame*)(AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_tMainSplitterWnd.GetPane(0, 0));

	OBJID::ID PickId = pView->m_ePickingObject;

	CObjectManager::Get_Instance()->Selete_Delete(PickId);

	pView->Invalidate(FALSE);
	UpdateData(FALSE);
}


void CMyUnitTool::OnBnClickedDeleteAll()
{
	UpdateData(TRUE);

	CMainFrame* pMain = (CMainFrame*)(AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_tMainSplitterWnd.GetPane(0, 0));

	CObjectManager::Get_Instance()->Release();

	pView->Invalidate(FALSE);
	UpdateData(FALSE);
}


void CMyUnitTool::OnBnClickedResizing()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
}


void CMyUnitTool::OnBnClickedDeleteLastPick()
{
	UpdateData(TRUE);
	CMainFrame* pMain = (CMainFrame*)(AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_tMainSplitterWnd.GetPane(0, 0));

	OBJID::ID PickId = pView->m_ePickingObject;

	CObjectManager::Get_Instance()->Delete_Last_Picking_Object(PickId);

	pView->Invalidate(FALSE);
	UpdateData(FALSE);
}
