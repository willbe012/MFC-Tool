#pragma once


// CMyUnitTool ��ȭ �����Դϴ�.

class CMyUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CMyUnitTool)

public:
	CMyUnitTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMyUnitTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYUNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()



public:
	PICKINGID::PICKINGMODE	m_ePicking;
	CButton		m_ePickingButton[PICKINGID::END];
	D3DXVECTOR3 m_iSize;
	
public:

	afx_msg void OnBnClickedPickPinky();
	afx_msg void OnBnClickedPickRaff();
	afx_msg void OnBnClickedPickBiu();
	afx_msg void OnBnClickedPickTile();
	afx_msg void OnBnClickedRenderHitBox();
	afx_msg void OnBnClickedDeleteObject();
	afx_msg void OnBnClickedDeleteAll();
	afx_msg void OnBnClickedResizing();
	afx_msg void OnBnClickedDeleteLastPick();
};
