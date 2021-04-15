#pragma once


// CMyUnitTool 대화 상자입니다.

class CMyUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CMyUnitTool)

public:
	CMyUnitTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMyUnitTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYUNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
