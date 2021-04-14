#include "stdafx.h"
#include "Texture_Manager.h"
#include "SingleTexture.h"
#include "MultiTexture.h"
IMPLEMENT_SINGLETON(CTexture_Manager)
CTexture_Manager::CTexture_Manager()
{
}


CTexture_Manager::~CTexture_Manager()
{
	Release_TextureManager(); 
}

const TEXINFO * CTexture_Manager::Get_TexInfo(const wstring & wstrObjectKey, const wstring & wstrStateKey, const DWORD & dwIndex)
{
	auto& iter_Find = m_mapTexture.find(wstrObjectKey);
	if(m_mapTexture.end() == iter_Find)
		return nullptr;

	return iter_Find->second->Get_Texture(wstrStateKey, dwIndex);
}

HRESULT CTexture_Manager::Insert_Texture(const TEXID eTexID, const wstring & wstrFilePath, const wstring & wstrObjectKey, const wstring & wstrStateKey, const DWORD & dwCount)
{
	map<wstring, CTexture*>::iterator& iter_find = m_mapTexture.find(wstrObjectKey); 
	
	// 해당 ObjectKey값에 값이 없다라는 것. 
	CTexture* pTexture = nullptr;
	// 이건 플레이어를 예로 들었을 때의 상황입니다. 절대 절대 착각마세요 .
	// 워링 워링!!! 
	//Player, Attack, 5
	//Player, Die, 5
	if (m_mapTexture.end() == iter_find)
	{
		switch (eTexID)
		{
		case SINGLE_TEX:
			pTexture = new CSingleTexture;
			break;
		case MULTI_TEX:
			pTexture = new CMultiTexture;
			break;
		default:
			return E_FAIL;
		}
		if (FAILED(pTexture->Insert_Texture(wstrFilePath, wstrStateKey, dwCount)))
		{
			ERR_MSG(L"Creating Failed - Texture Manager");
			return E_FAIL;
		}
		//이건 플레이어를 예로 들었을때의 상황입니다. 
		//여기서의 키값은 Player, Multitexture
		m_mapTexture.emplace(wstrObjectKey, pTexture);
	}
	else if (MULTI_TEX == eTexID)
	{
		if (FAILED(m_mapTexture[wstrObjectKey]->Insert_Texture(wstrFilePath, wstrStateKey, dwCount)))
		{
			ERR_MSG(L"MultiTexture Insert Failed - Texture Manager");
			return E_FAIL;
		}
	}
	else
		return E_FAIL;
	
	return S_OK; 
}

void CTexture_Manager::Release_TextureManager()
{
	for (auto& rPair : m_mapTexture)
		Safe_Delete(rPair.second);
	m_mapTexture.clear();
}
