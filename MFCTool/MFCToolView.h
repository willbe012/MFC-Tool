
// MFCToolView.h : CMFCToolView 클래스의 인터페이스
//

#pragma once
class CTerrain; 
class CMFCToolDoc; 
class CMFCToolView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CMFCToolView();
	DECLARE_DYNCREATE(CMFCToolView)

// 특성입니다.
public:
	CMFCToolDoc* GetDocument() const;
// 작업입니다.
public:
	CTerrain* m_pTerrain; 
	RECT m_tRc; 
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	///////////////////신정호
public:
	void Load_Resource_GameObject();

public:
	OBJID::ID m_ePickingObject;

public:
	void Picking_Check(D3DXVECTOR3 _vMouse, D3DXVECTOR3 _vSize);
	void Picking_Tile(D3DXVECTOR3 _vMouse);
	void Picking_Pinky(D3DXVECTOR3 _vMouse, D3DXVECTOR3 _vSize);
	void Picking_Raff(D3DXVECTOR3 _vMouse, D3DXVECTOR3 _vSize);
	void Picking_Biu(D3DXVECTOR3 _vMouse, D3DXVECTOR3 _vSize);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	///////////////////// 신정호
};

#ifndef _DEBUG  // MFCToolView.cpp의 디버그 버전
inline CMFCToolDoc* CMFCToolView::GetDocument() const
   { return reinterpret_cast<CMFCToolDoc*>(m_pDocument); }
#endif

