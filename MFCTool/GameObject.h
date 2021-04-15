#pragma once

#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

class CMFCToolView;
class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

public:
	virtual HRESULT Ready_Object() PURE;
	virtual int	 Update_Object() PURE;
	virtual void Late_Update_Object() PURE;
	virtual void Render_Object(CMFCToolView* _pView) PURE;
	virtual void Release_Object() PURE;
	virtual void Matrix_Check() PURE;

public:
	void Hitbox_Check();

public:
	const D3DXMATRIX Get_World() { return m_tInfo.matWorld; }

public:
	void Set_Pos(D3DXVECTOR3 vPos);
	void Set_ReSize(D3DXVECTOR3 vSize);
	void Set_RenderHitBox() { m_bRenderHitBox = !m_bRenderHitBox; }


protected:
	UNITINFO	m_tInfo;
	RECT		m_tHitBox;

protected:
	bool	m_bDead;
	bool	m_bRenderHitBox;
};

#endif // !__GAMEOBJECT_H__
