#pragma once

#ifndef __PINKY_H__
#define __PINKY_H__

#include "GameObject.h"
class CMFCToolView;
class CPinky : public CGameObject
{
public:
	CPinky();
	virtual ~CPinky();

public:
	virtual HRESULT Ready_Object() override;
	virtual int Update_Object() override;
	virtual void Late_Update_Object() override;
	virtual void Render_Object(CMFCToolView* _pView) override;
	virtual void Release_Object() override;
	virtual void Matrix_Check() override;




};

#endif // !__PINKY_H__
