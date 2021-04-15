#pragma once



// CForm �� ���Դϴ�.
#include "UnitTool.h"
#include "AnimationTool.h"
#include "MyUnitTool.h"
class CForm : public CFormView
{
	DECLARE_DYNCREATE(CForm)

protected:
	CForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CUnitTool m_tUnitTool;

	afx_msg void OnBnClickedAnimationButton();
	CAnimationTool m_tAnimationTool;







	//��ȣ
	afx_msg void OnBnClickedButtonmyunittool();
	CMyUnitTool m_tMyUnitTool;
};


