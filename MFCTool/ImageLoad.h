#pragma once
#include "afxwin.h"


// CImageLoad ��ȭ �����Դϴ�.

class CImageLoad : public CDialog
{
	DECLARE_DYNAMIC(CImageLoad)

public:
	CImageLoad(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CImageLoad();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANIMATIONTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP();


};
