// MiniView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "MiniView.h"
#include "MainFrm.h"
#include "MFCToolView.h"
#include "Terrain.h"


// CMiniView

IMPLEMENT_DYNCREATE(CMiniView, CView)

CMiniView::CMiniView()
{

}

CMiniView::~CMiniView()
{
}

BEGIN_MESSAGE_MAP(CMiniView, CView)
END_MESSAGE_MAP()


// CMiniView �׸����Դϴ�.

void CMiniView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// �ֻ��� - WinApp -> MainFrame->m_MainSplitterWnd -> View -> Terrain ; 
	CMainFrame* pMain = (CMainFrame*)(AfxGetApp()->GetMainWnd());
	//CMainFrame* pMain = static_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	// ���̰� ���� �ݵ�� ����϶�. 
	
	if (nullptr == pMain)
		return; 
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_tMainSplitterWnd.GetPane(0, 0));
	

	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
	CGraphic_Device::Get_Instance()->Render_Begin(); 
	pView->m_pTerrain->MiniRender_Terrain();
	CGraphic_Device::Get_Instance()->Render_End(m_hWnd); 
}


// CMiniView �����Դϴ�.

#ifdef _DEBUG
void CMiniView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniView �޽��� ó�����Դϴ�.
