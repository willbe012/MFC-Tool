#include "stdafx.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "MFCToolView.h"

CObjectManager* CObjectManager::m_pInstance = nullptr;
CObjectManager::CObjectManager()
{
}


CObjectManager::~CObjectManager()
{
	Release();
}

void CObjectManager::Add_Object(CGameObject * _pObj, OBJID::ID _eID)
{
	m_listObj[_eID].emplace_back(_pObj);
}

void CObjectManager::Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		auto iter = m_listObj[i].begin();
		for (; iter != m_listObj[i].end();) {
			int iEvent = (*iter)->Update_Object();

			if (OBJ_DEAD == iEvent) {
				SAFE_DELETE(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else ++iter;
		}
	}
}

void CObjectManager::Late_Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
		{
			pObj->Late_Update_Object();
		}
	}
}

void CObjectManager::Render(CMFCToolView * _pView)
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
		{
			pObj->Render_Object(_pView);
		}
	}
}

void CObjectManager::Release()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for_each(m_listObj[i].begin(), m_listObj[i].end(), Safe_Delete<CGameObject*>);
		m_listObj[i].clear();
	}
}

void CObjectManager::Set_RenderHitBox()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
		{
			pObj->Set_RenderHitBox();
		}
	}
}

void CObjectManager::Selete_Delete(OBJID::ID _Id)
{
	for_each(m_listObj[_Id].begin(), m_listObj[_Id].end(), Safe_Delete<CGameObject*>);
	m_listObj[_Id].clear();
}

void CObjectManager::Delete_Last_Picking_Object(OBJID::ID _Id)
{
	if (m_listObj[_Id].empty())
		return;
	
	auto iter = m_listObj[_Id].end();

	--iter;
	
	iter = m_listObj[_Id].erase(iter);
}
