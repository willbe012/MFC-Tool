#include "stdafx.h"
#include "GameObject.h"
#include "MFCToolView.h"


CGameObject::CGameObject()
	: m_bDead(false), m_bRenderHitBox(true)
{
	ZeroMemory(&m_tInfo, sizeof(UNITINFO));
	ZeroMemory(&m_tHitBox, sizeof(RECT));
	m_tInfo.vScale = { 1.f, 1.f, 0.f };
	
}


CGameObject::~CGameObject()
{
}

void CGameObject::Matrix_Check()
{
}

void CGameObject::Hitbox_Check()
{
	D3DXVECTOR3 vPos = { m_tInfo.matWorld._41, m_tInfo.matWorld._42, m_tInfo.matWorld._43 };
	D3DXVECTOR3 vSize = { m_tInfo.vSize.x * m_tInfo.matWorld._11, m_tInfo.vSize.y * m_tInfo.matWorld._22, m_tInfo.vSize.z * m_tInfo.matWorld._33 };

	LONG lLeft = (LONG)(vPos.x - vSize.x * 0.5f);
	LONG lTop = (LONG)(vPos.y - vSize.y * 0.5f);
	LONG lRight = (LONG)(vPos.x + vSize.x * 0.5f);
	LONG lBottom = (LONG)(vPos.y + vSize.y * 0.5f);

	if (lLeft > lRight)
	{
		LONG temp = lLeft;
		lLeft = lRight;
		lRight = lLeft;
	}

	if (lTop > lBottom)
	{
		LONG temp = lTop;
		lTop = lBottom;
		lBottom = lTop;
	}

	m_tHitBox = { lLeft, lTop, lRight, lBottom };
}

void CGameObject::Set_Pos(D3DXVECTOR3 vPos)
{
	m_tInfo.vPos = vPos;
}

void CGameObject::Set_ReSize(D3DXVECTOR3 vSize)
{
	if(vSize.x != 0)
		m_tInfo.vSize.x = vSize.x;

	if (vSize.y != 0)
		m_tInfo.vSize.y = vSize.y;
}

