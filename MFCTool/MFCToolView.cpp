
// MFCToolView.cpp : CMFCToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCTool.h"
#endif

#include "MFCToolDoc.h"
#include "MFCToolView.h"
#include "Texture_Manager.h"

#include "SingleTexture.h"
#include "Terrain.h"
#include "MainFrm.h"
#include "MiniView.h"

////신정호.h
#include "ObjectManager.h"
#include "GameObject.h"
#include "Pinky.h"
#include "Form.h"
//#include "MyUnitTool.h"
#include "Raff.h"
#include "Biu.h"


HWND g_hWND; 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCToolView

IMPLEMENT_DYNCREATE(CMFCToolView, CScrollView)

BEGIN_MESSAGE_MAP(CMFCToolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CMFCToolView 생성/소멸

CMFCToolView::CMFCToolView()
	:m_pTerrain(nullptr)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCToolView::~CMFCToolView()
{
	if (m_pTerrain)
		Safe_Delete(m_pTerrain); 
	CTexture_Manager::Destroy_Instance(); 
	CGraphic_Device::Destroy_Instance(); 
	CObjectManager::Destroy_Instance();
}

BOOL CMFCToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CMFCToolView 그리기

void CMFCToolView::OnDraw(CDC* /*pDC*/)
{
	CMFCToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
// 	m_tRc.left += 100; 
// 	m_tRc.right += 100; 
	if (!pDoc)
		return;
	
	CGraphic_Device::Get_Instance()->Render_Begin(); 
	m_pTerrain->Render_Terrain(); 

	CObjectManager::Get_Instance()->Render(this);

	CGraphic_Device::Get_Instance()->Render_End(); 

	
}


// CMFCToolView 인쇄

BOOL CMFCToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCToolView 진단

#ifdef _DEBUG
void CMFCToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMFCToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCToolDoc* CMFCToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCToolDoc)));
	return (CMFCToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCToolView 메시지 처리기


void CMFCToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, (TILECY >> 1) * TILEY)); 
	g_hWND = m_hWnd; 
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd()); 

	RECT rcMain{}; 
	pMain->GetWindowRect(&rcMain); 
	SetRect(&rcMain, 0, 0, rcMain.right - rcMain.left, rcMain.bottom - rcMain.top); 
	
	RECT rcView{}; 
	GetClientRect(&rcView); 
	int iGapX =  (rcMain.right - rcView.right) + 1 ;
	int iGapY = (rcMain.bottom - rcView.bottom) + 1;
	pMain->SetWindowPos(nullptr, 0, 0, g_iWinCX + iGapX, g_iWinCY + iGapY, PM_NOREMOVE);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (FAILED(CGraphic_Device::Get_Instance()->Ready_Graphic_Device()))
	{
		ERR_MSG(L"Create Failed - View OnInitFunction");
		return; 
	}
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(
		CTexture_Manager::MULTI_TEX,
		L"../Texture/Stage/Terrain/Tile/Tile%d.png",
		L"Terrain",
		L"Tile",
		36)))
	{
		ERR_MSG(L"Create Failed - View OnInitFunction");
		return;
	}
	
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(
		CTexture_Manager::SINGLE_TEX,
		L"../Texture/Logo.jpg",
		L"Logo")))
	{
		ERR_MSG(L"Create Failed - View OnInitFunction");
		return;
	}
	if (nullptr == m_pTerrain)
	{
		m_pTerrain = new CTerrain; 
		m_pTerrain->Ready_Terrain(); 
		m_pTerrain->Set_View(this); 
	}

	Load_Resource_GameObject();

}


void CMFCToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMain->m_tSecondSplitterWnd.GetPane(1, 0));
	D3DXVECTOR3 vMouse = { float(point.x + GetScrollPos(SB_HORZ)),float(point.y + GetScrollPos(SB_VERT)), 0.f };
	CForm* pForm = dynamic_cast<CForm*>(pMain->m_tSecondSplitterWnd.GetPane(0, 0));
	//int iDrawID = pMyForm->m_tMapTool.m_dwDrawID;

	m_pTerrain->Tile_Picking(vMouse, 1);
	Invalidate(FALSE);
	pMiniView->Invalidate(FALSE);
	CScrollView::OnLButtonDown(nFlags, point);

}

void CMFCToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMain->m_tSecondSplitterWnd.GetPane(1, 0));
	D3DXVECTOR3 vMouse = { float(point.x + GetScrollPos(SB_HORZ)),float(point.y + GetScrollPos(SB_VERT)), 0.f };
	CForm* pForm = dynamic_cast<CForm*>(pMain->m_tSecondSplitterWnd.GetPane(0, 0));

	D3DXVECTOR3 vSize = { 0.f , 0.f, 0.f };

	if (pForm != nullptr)
		vSize = pForm->m_tMyUnitTool.m_iSize;

	Picking_Check(vMouse, vSize);


	Invalidate(FALSE);
	pMiniView->Invalidate(FALSE);

	CScrollView::OnRButtonDown(nFlags, point);
}

void CMFCToolView::Load_Resource_GameObject()
{
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::SINGLE_TEX, L"../Texture/Test/Raff2.png", L"Raff");
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::SINGLE_TEX, L"../Texture/Test/Pinky2.png", L"Pinky");
	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::SINGLE_TEX, L"../Texture/Test/Biu2.png", L"Biu");

	CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::SINGLE_TEX, L"../Texture/Test/HitBox.png", L"HitBox");
}

void CMFCToolView::Picking_Check(D3DXVECTOR3 _vMouse, D3DXVECTOR3 _vSize)
{
	switch (m_ePickingObject)
	{
	case OBJID::PINKY:
		Picking_Pinky(_vMouse, _vSize);
		break;
	case OBJID::RAFF:
		Picking_Raff(_vMouse, _vSize);
		break;
	case OBJID::BIU:
		Picking_Biu(_vMouse, _vSize);
		break;
	default:
		m_ePickingObject = OBJID::TILE;
		break;
	}
}

void CMFCToolView::Picking_Tile(D3DXVECTOR3 _vMouse)
{
	m_pTerrain->Tile_Picking(_vMouse, 0);
}

void CMFCToolView::Picking_Pinky(D3DXVECTOR3 _vMouse, D3DXVECTOR3 _vSize)
{
	int TileCX = 40;
	int TileCY = 40;

	int ItemTile_X = int(_vMouse.x / TileCX);
	int ItemTile_Y = int(_vMouse.y / TileCY);

	CGameObject* pObj = CAbstractFactory<CPinky>::Create(D3DXVECTOR3((ItemTile_X * TileCX) + (TileCX >> 1), (ItemTile_Y * TileCY) + (TileCY >> 1), 0.f));
	pObj->Set_ReSize(_vSize);
	CObjectManager::Get_Instance()->Add_Object(pObj, OBJID::PINKY);
}

void CMFCToolView::Picking_Raff(D3DXVECTOR3 _vMouse, D3DXVECTOR3 _vSize)
{
	int TileCX = 40;
	int TileCY = 40;

	int ItemTile_X = int(_vMouse.x / TileCX);
	int ItemTile_Y = int(_vMouse.y / TileCY);

	CGameObject* pObj = CAbstractFactory<CRaff>::Create(D3DXVECTOR3((ItemTile_X * TileCX) + (TileCX >> 1), (ItemTile_Y * TileCY) + (TileCY >> 1), 0.f));
	pObj->Set_ReSize(_vSize);
	CObjectManager::Get_Instance()->Add_Object(pObj, OBJID::RAFF);

}

void CMFCToolView::Picking_Biu(D3DXVECTOR3 _vMouse, D3DXVECTOR3 _vSize)
{
	int TileCX = 40;
	int TileCY = 40;

	int ItemTile_X = int(_vMouse.x / TileCX);
	int ItemTile_Y = int(_vMouse.y / TileCY);

	CGameObject* pObj = CAbstractFactory<CBiu>::Create(D3DXVECTOR3((ItemTile_X * TileCX) + (TileCX >> 1), (ItemTile_Y * TileCY) + (TileCY >> 1), 0.f));
	pObj->Set_ReSize(_vSize);
	CObjectManager::Get_Instance()->Add_Object(pObj, OBJID::BIU);
}


