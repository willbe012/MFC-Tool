#pragma once
#include "afxwin.h"


// CUnitTool 대화 상자입니다.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUnitTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 건호 무야호!
	CString m_strOriginal;
	CString m_strCopy;
	afx_msg void OnBnClickedCopy();
	// UnitData
	CString m_strName;
	int m_iAtt;
	int m_iDef;
	CListBox m_ListBox;
	afx_msg void OnBnClickedAdd();
	map<CString, UNITINFO*> m_mapUnitInfo; 
	afx_msg void OnLbnSelchangeFindName();
	CButton m_Radio[3];
	CButton m_CheckBox[3];
	afx_msg void OnEnChangeEdit3();
};
