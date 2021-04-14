// AnimationTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "AnimationTool.h"
#include "afxdialogex.h"
#include "Texture_Manager.h"
#include "MFCToolView.h"

// CAnimationTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAnimationTool, CDialog)

CAnimationTool::CAnimationTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ANIMATIONTOOL, pParent)
{
	

}

CAnimationTool::~CAnimationTool()
{
}

void CAnimationTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATE, m_CStateComboBox);
	DDX_Control(pDX, IDC_OBJECT, m_CObjectComboBox);

}


BEGIN_MESSAGE_MAP(CAnimationTool, CDialog)
	
	ON_BN_CLICKED(IDC_PREVBUTTON, &CAnimationTool::OnBnClickedPrev)
	ON_BN_CLICKED(IDC_NEXTBUTTON, &CAnimationTool::OnBnClickedNext)
	ON_BN_CLICKED(IDC_PLAYBUTTON, &CAnimationTool::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_STOPBUTTON, &CAnimationTool::OnBnClickedStop)
	ON_BN_CLICKED(IDC_LOADBUTTON, &CAnimationTool::OnBnClickedLoadImage)

	ON_CBN_SELCHANGE(IDC_STATE, &CAnimationTool::OnCbnSelchangeState)
	ON_CBN_SELCHANGE(IDC_OBJECT, &CAnimationTool::OnCbnSelchangeObject)
END_MESSAGE_MAP()


// CAnimationTool 메시지 처리기입니다.



void CAnimationTool::OnBnClickedPrev() // 이전 버튼
{
	// 이전 이미지 보여줌
}


void CAnimationTool::OnBnClickedNext() // 다음 버튼
{
	// 다음 이미지 보여줌
	int iA = 0;
}


void CAnimationTool::OnBnClickedPlay() // 재생 버튼
{
	// 이미지 처음부터 끝까지 재생
}


void CAnimationTool::OnBnClickedStop() // 정지 버튼
{
	// 특정 이미지만 띄움
}


void CAnimationTool::OnBnClickedLoadImage()
{
	if (nullptr == m_tImageLoad.GetSafeHwnd())
		m_tImageLoad.Create(IDD_IMAGELOAD);
	m_tImageLoad.ShowWindow(SW_SHOW);
}


BOOL CAnimationTool::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Object Key 값
	m_CObjectComboBox.InsertString(0, _T("Player"));
	m_CObjectComboBox.InsertString(0, _T("Monster"));
	m_CObjectComboBox.SetCurSel(0);
	//State Key 값
	m_CStateComboBox.InsertString(0, _T("IDLE"));
	m_CStateComboBox.InsertString(1, _T("WALK"));
	m_CStateComboBox.InsertString(2, _T("DIE"));
	m_CStateComboBox.SetCurSel(0);

	
	return TRUE;
}


void CAnimationTool::OnCbnSelchangeState()
{
	int iSel = m_CStateComboBox.GetCurSel();

	if (!(0 > iSel))
	{
		CString sSel;
		m_CStateComboBox.GetLBText(iSel, sSel);
	}
	// listbox에 데이터 넣는 작업 필요.
}


void CAnimationTool::OnCbnSelchangeObject()
{
	int iSel = m_CObjectComboBox.GetCurSel();

	if (!(0 > iSel))
	{
		CString sSel;
		m_CObjectComboBox.GetLBText(iSel, sSel);
	}
}
