// UnitTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UNITTOOL, pParent)
	, m_strOriginal(_T(""))
	, m_strCopy(_T(""))
	, m_strName(_T(""))
	, m_iAtt(0)
	, m_iDef(0)
{

}

CUnitTool::~CUnitTool()
{
	for (auto& rPair : m_mapUnitInfo)
	{
		Safe_Delete(rPair.second); 
	}
	m_mapUnitInfo.clear(); 
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strOriginal);
	DDX_Text(pDX, IDC_EDIT2, m_strCopy);
	DDX_Text(pDX, IDC_EDIT3, m_strName);
	DDX_Text(pDX, IDC_EDIT4, m_iAtt);
	DDX_Text(pDX, IDC_EDIT5, m_iDef);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio[2]);

	DDX_Control(pDX, IDC_CHECK1, m_CheckBox[0]);
	DDX_Control(pDX, IDC_CHECK2, m_CheckBox[1]);
	DDX_Control(pDX, IDC_CHECK3, m_CheckBox[2]);

}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitTool::OnBnClickedCopy)
	ON_BN_CLICKED(IDC_BUTTON2, &CUnitTool::OnBnClickedAdd)
	ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnLbnSelchangeFindName)
	ON_EN_CHANGE(IDC_EDIT3, &CUnitTool::OnEnChangeEdit3)
END_MESSAGE_MAP()


// CUnitTool 메시지 처리기입니다.


void CUnitTool::OnBnClickedCopy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// UpdateData- DoDataExchange라는 함수를 호출하는 용도로 사용되는 함수. 
	// true경우 control에 데이터를 얻어오는 역할을 하며 false일경우 control 에 데이터를 내보내는 역할을 한다. 
	UpdateData(TRUE);
	m_strCopy = m_strOriginal;
	UpdateData(FALSE); 
}


void CUnitTool::OnBnClickedAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE); 
	if (L"" == m_strName)
		return; 
	auto& iter_find = m_mapUnitInfo.find(m_strName);

	if (m_mapUnitInfo.end() != iter_find)
		return; 

	UNITINFO* pUnitInfo = new UNITINFO; 
	pUnitInfo->byJop = 0; 
	pUnitInfo->byItem = 0; 

	pUnitInfo->wstrName = m_strName; 
	pUnitInfo->iAtt = m_iAtt; 
	pUnitInfo->iDef = m_iDef; 
	int i = 0; 
	for (; i < 3; ++i)
	{
		if (m_Radio[i].GetCheck())
			break; 
	}
	pUnitInfo->byJop = i; 

	// 0000 0110
	// 0000 0001 |
	// 0000 0111

	if (m_CheckBox[0].GetCheck())
		pUnitInfo->byItem |= 장팔사모; 
	if (m_CheckBox[1].GetCheck())
		pUnitInfo->byItem |= 청룡언월도;
	if (m_CheckBox[2].GetCheck())
		pUnitInfo->byItem |= 자웅쌍검;

	m_mapUnitInfo.insert(map<CString, UNITINFO*>::value_type(m_strName, pUnitInfo)); 
	m_ListBox.AddString(m_strName); 
	UpdateData(FALSE); 
}


void CUnitTool::OnLbnSelchangeFindName()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE); 
	for (int i = 0; i < 3; ++i)
	{
		m_Radio[i].SetCheck(FALSE);
		m_CheckBox[i].SetCheck(FALSE); 
	}

	int iIndex = m_ListBox.GetCurSel(); 
	CString strFindName = L""; 
	m_ListBox.GetText(iIndex, strFindName);
	map<CString, UNITINFO*>::iterator& iter_Find = m_mapUnitInfo.find(strFindName); 
	if (m_mapUnitInfo.end() == iter_Find)
		return; 
	m_strName = iter_Find->second->wstrName;
	m_iAtt = iter_Find->second->iAtt; 
	m_iDef = iter_Find->second->iDef; 
	// 예외처리 하삼. 
	if (iter_Find->second->byJop > 3)
		return;

	m_Radio[iter_Find->second->byJop].SetCheck(TRUE); 

	if (iter_Find->second->byItem & 장팔사모)
		m_CheckBox[0].SetCheck(TRUE); 
	if (iter_Find->second->byItem & 청룡언월도)
		m_CheckBox[1].SetCheck(TRUE);
	if (iter_Find->second->byItem & 자웅쌍검)
		m_CheckBox[2].SetCheck(TRUE);

	

	UpdateData(FALSE); 
}


void CUnitTool::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
