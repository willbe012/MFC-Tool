#pragma once

#ifndef __BIU_H__
#define __BIU_H__

#include "GameObject.h"
class CBiu :
	public CGameObject
{
public:
	CBiu();
	virtual ~CBiu();

public:
	virtual HRESULT Ready_Object() override;
	virtual int Update_Object() override;
	virtual void Late_Update_Object() override;
	virtual void Render_Object(CMFCToolView * _pView) override;
	virtual void Release_Object() override;
	virtual void Matrix_Check() override;
};

#endif // !__BIU_H__
