#pragma once


// CAnimationTool 대화 상자입니다.
#include "ImageLoad.h"
#include <atlimage.h>
class CAnimationTool : public CDialog
{
	DECLARE_DYNAMIC(CAnimationTool)
public:
	enum STATE {WALK, END};
public:
	CAnimationTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAnimationTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
