// Form.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "Form.h"


// CForm

IMPLEMENT_DYNCREATE(CForm, CFormView)

CForm::CForm()
	: CFormView(IDD_FORM)
{

}

CForm::~CForm()
{
}

void CForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CForm::OnBnClickedButton1)

	ON_BN_CLICKED(IDC_BUTTON2, &CForm::OnBnClickedAnimationButton)
END_MESSAGE_MAP()


// CForm 진단입니다.

#ifdef _DEBUG
void CForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CForm 메시지 처리기입니다.


void CForm::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(nullptr == m_tUnitTool.GetSafeHwnd())
		m_tUnitTool.Create(IDD_UNITTOOL); 
	m_tUnitTool.ShowWindow(SW_SHOW);
}



void CForm::OnBnClickedAnimationButton()
{
	if (nullptr == m_tAnimationTool.GetSafeHwnd())
		m_tAnimationTool.Create(IDD_ANIMATIONTOOL);
	m_tAnimationTool.ShowWindow(SW_SHOW);
}
