#pragma once
#include "afxwin.h"


// CUnitTool ��ȭ �����Դϴ�.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUnitTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// ��ȣ ����ȣ!
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
