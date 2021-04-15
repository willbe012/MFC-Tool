
// MFCToolView.cpp : CMFCToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

////����ȣ.h
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CMFCToolView ����/�Ҹ�

CMFCToolView::CMFCToolView()
	:m_pTerrain(nullptr)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CMFCToolView �׸���

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


// CMFCToolView �μ�

BOOL CMFCToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMFCToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMFCToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMFCToolView ����

#ifdef _DEBUG
void CMFCToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMFCToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCToolDoc* CMFCToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCToolDoc)));
	return (CMFCToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCToolView �޽��� ó����


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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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


