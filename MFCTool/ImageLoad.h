#pragma once
#include "afxwin.h"


// CImageLoad 대화 상자입니다.

class CImageLoad : public CDialog
{
	DECLARE_DYNAMIC(CImageLoad)

public:
	CImageLoad(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CImageLoad();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANIMATIONTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP();


};
