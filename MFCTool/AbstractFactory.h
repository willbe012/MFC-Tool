#pragma once

#ifndef __ABSTRACTFACTORY_H__
#define __ABSTRACTFACTORY_H__


class CGameObject;

template <typename T>
class CAbstractFactory
{
public:
	static CGameObject* Create()
	{
		CGameObject* pObj = new T;
		pObj->Ready_Object();
		return pObj;
	}

	static CGameObject* Create(D3DXVECTOR3 vPos)
	{
		CGameObject* pObj = new T;
		pObj->Ready_Object();
		pObj->Set_Pos(vPos);
		return pObj;
	}







};

#endif // !__ABSTRACTFACTORY_H__
