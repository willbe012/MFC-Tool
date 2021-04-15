#pragma once

#ifndef __RAFF_H__
#define __RAFF_H__

#include "GameObject.h"
class CRaff :	public CGameObject
{
public:
	CRaff();
	virtual ~CRaff();

public:
	virtual HRESULT Ready_Object() override;
	virtual int Update_Object() override;
	virtual void Late_Update_Object() override;
	virtual void Render_Object(CMFCToolView * _pView) override;
	virtual void Release_Object() override;
	virtual void Matrix_Check() override;
};

#endif // !__RAFF_H__
