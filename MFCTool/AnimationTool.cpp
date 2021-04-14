// AnimationTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "AnimationTool.h"
#include "afxdialogex.h"
#include "Texture_Manager.h"
#include "MFCToolView.h"

// CAnimationTool ��ȭ �����Դϴ�.

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


// CAnimationTool �޽��� ó�����Դϴ�.



void CAnimationTool::OnBnClickedPrev() // ���� ��ư
{
	// ���� �̹��� ������
}


void CAnimationTool::OnBnClickedNext() // ���� ��ư
{
	// ���� �̹��� ������
	int iA = 0;
}


void CAnimationTool::OnBnClickedPlay() // ��� ��ư
{
	// �̹��� ó������ ������ ���
}


void CAnimationTool::OnBnClickedStop() // ���� ��ư
{
	// Ư�� �̹����� ���
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
	// Object Key ��
	m_CObjectComboBox.InsertString(0, _T("Player"));
	m_CObjectComboBox.InsertString(0, _T("Monster"));
	m_CObjectComboBox.SetCurSel(0);
	//State Key ��
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
	// listbox�� ������ �ִ� �۾� �ʿ�.
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
