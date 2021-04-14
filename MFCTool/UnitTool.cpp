// UnitTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool ��ȭ �����Դϴ�.

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


// CUnitTool �޽��� ó�����Դϴ�.


void CUnitTool::OnBnClickedCopy()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// UpdateData- DoDataExchange��� �Լ��� ȣ���ϴ� �뵵�� ���Ǵ� �Լ�. 
	// true��� control�� �����͸� ������ ������ �ϸ� false�ϰ�� control �� �����͸� �������� ������ �Ѵ�. 
	UpdateData(TRUE);
	m_strCopy = m_strOriginal;
	UpdateData(FALSE); 
}


void CUnitTool::OnBnClickedAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		pUnitInfo->byItem |= ���Ȼ��; 
	if (m_CheckBox[1].GetCheck())
		pUnitInfo->byItem |= û������;
	if (m_CheckBox[2].GetCheck())
		pUnitInfo->byItem |= �ڿ��ְ�;

	m_mapUnitInfo.insert(map<CString, UNITINFO*>::value_type(m_strName, pUnitInfo)); 
	m_ListBox.AddString(m_strName); 
	UpdateData(FALSE); 
}


void CUnitTool::OnLbnSelchangeFindName()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// ����ó�� �ϻ�. 
	if (iter_Find->second->byJop > 3)
		return;

	m_Radio[iter_Find->second->byJop].SetCheck(TRUE); 

	if (iter_Find->second->byItem & ���Ȼ��)
		m_CheckBox[0].SetCheck(TRUE); 
	if (iter_Find->second->byItem & û������)
		m_CheckBox[1].SetCheck(TRUE);
	if (iter_Find->second->byItem & �ڿ��ְ�)
		m_CheckBox[2].SetCheck(TRUE);

	

	UpdateData(FALSE); 
}


void CUnitTool::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
