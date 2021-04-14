// ImageLoad.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "ImageLoad.h"
#include "afxdialogex.h"


// CImageLoad 대화 상자입니다.

IMPLEMENT_DYNAMIC(CImageLoad, CDialog)

CImageLoad::CImageLoad(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ANIMATIONTOOL, pParent)
{

}

CImageLoad::~CImageLoad()
{
}

void CImageLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CImageLoad, CDialog)

END_MESSAGE_MAP()


// CImageLoad 메시지 처리기입니다.

