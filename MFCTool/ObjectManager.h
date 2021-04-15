#pragma once

#ifndef __OBJECTMANAGER_H__
#define __OBJECTMANAGER_H__

class CMFCToolView;
class CObjectManager
{
public:
	static CObjectManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CObjectManager;
		return m_pInstance;

	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	CObjectManager();
	~CObjectManager();

public:
	void Add_Object(CGameObject* _pObj, OBJID::ID _eID);
	void Update();
	void Late_Update();
	void Render(CMFCToolView* _pview);
	void Release();

public:
	void Set_RenderHitBox();

public:
	void Selete_Delete(OBJID::ID _Id);
	void Delete_Last_Picking_Object(OBJID::ID _Id);

private:
	list<CGameObject*> m_listObj[OBJID::END];
	static CObjectManager* m_pInstance;
};

#endif // !__OBJECTMANAGER_H__
