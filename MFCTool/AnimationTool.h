#pragma once


// CAnimationTool ��ȭ �����Դϴ�.
#include "ImageLoad.h"
#include <atlimage.h>
class CAnimationTool : public CDialog
{
	DECLARE_DYNAMIC(CAnimationTool)
public:
	enum STATE {WALK, END};
public:
	CAnimationTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAnimationTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedPrev();
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedLoadImage();

public:
	CImageLoad	m_tImageLoad;
	CComboBox   m_CObjectComboBox;
	CComboBox	m_CStateComboBox;
	CImage		m_ImgTest;

	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeState();
	afx_msg void OnCbnSelchangeObject();
};
