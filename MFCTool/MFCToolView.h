
// MFCToolView.h : CMFCToolView Ŭ������ �������̽�
//

#pragma once
class CTerrain; 
class CMFCToolDoc; 
class CMFCToolView : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	CMFCToolView();
	DECLARE_DYNCREATE(CMFCToolView)

// Ư���Դϴ�.
public:
	CMFCToolDoc* GetDocument() const;
// �۾��Դϴ�.
public:
	CTerrain* m_pTerrain; 
	RECT m_tRc; 
// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMFCToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	///////////////////����ȣ
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
	///////////////////// ����ȣ
};

#ifndef _DEBUG  // MFCToolView.cpp�� ����� ����
inline CMFCToolDoc* CMFCToolView::GetDocument() const
   { return reinterpret_cast<CMFCToolDoc*>(m_pDocument); }
#endif

