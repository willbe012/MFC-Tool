#include "stdafx.h"
#include "MultiTexture.h"


CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	Release_Texture(); 
}
//..\Texture\Stage\Terrain\Tile\Tile%d.png
HRESULT CMultiTexture::Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey /*= L""*/, const DWORD & dwCount /*= 0*/)
{
	auto& iter_Find = m_mapMultiTex.find(wstrStateKey);
	// 멀티텍스쳐 최초 한번 들어왔을 때. 
	if (m_mapMultiTex.end() == iter_Find)
	{
		TCHAR szFilePath[MAX_PATH] = L"";
		TEXINFO* pTexInfo = nullptr; 
		for (int i = 0; i < dwCount; ++i)
		{
			swprintf_s(szFilePath, wstrFilePath.c_str(), i);
			pTexInfo = new TEXINFO; 
			if (FAILED(D3DXGetImageInfoFromFile(szFilePath, &pTexInfo->tImageInfo)))
			{
				Safe_Delete(pTexInfo); 
				ERR_MSG(L"Get Image Data Failed");
				return E_FAIL;
			}
			if (FAILED(D3DXCreateTextureFromFileEx(CGraphic_Device::Get_Instance()->Get_Device(), szFilePath,
				pTexInfo->tImageInfo.Width,
				pTexInfo->tImageInfo.Height,
				pTexInfo->tImageInfo.MipLevels,
				0,
				pTexInfo->tImageInfo.Format,
				// D3DPOOL - 얻어온 데이터를 어디에 보관할 것인지를 받고 있다. 
				//D3DPOOL_DEFAULT - gpu의 메모리공간만 사용하겠다. 속도상으로는 가장 빠르다. 
				//D3DPOOL_SYSTEMMEM - 시스템 메모리 공간을 사용하겠다. 속도적으로는 느리지만 안정적이다. 
				// D3DPOOL_MANAGED - gpu와 시스템 메모리 두군데 다 사용하겠다. - 안정적이면서 빠르다. 
				D3DPOOL_MANAGED,
				D3DX_DEFAULT,
				D3DX_DEFAULT,
				0, nullptr, nullptr,
				&pTexInfo->pTexture)))
			{
				wstring wstrErrMsg = wstrFilePath + L"불러오기 실패. - SingleTeture.cpp";
				ERR_MSG(wstrErrMsg.c_str());
				Safe_Delete(pTexInfo);
				return E_FAIL;
			}
			// Attack -0,1,2,3,4,5
			// Die - 0,1,2,3,4,5

			m_mapMultiTex[wstrStateKey].emplace_back(pTexInfo); 
		}
		return S_OK;
	}
	return E_FAIL; 
}

const TEXINFO * CMultiTexture::Get_Texture(const wstring & wstrStateKey /*= L""*/, const DWORD & dwCount /*= 0*/) const
{
	auto& iter_Find = m_mapMultiTex.find(wstrStateKey);
	int iSize = iter_Find->second.size();
	if (m_mapMultiTex.end() == iter_Find || iSize <= dwCount)
		return nullptr;

	return iter_Find->second[dwCount];
	//return m_mapMultiTex[wstrStateKey][dwCount];
}

void CMultiTexture::Release_Texture()
{
// 	for (auto& rPair : m_mapMultiTex)
// 	{
// 		for_each(rPair.second.begin(), rPair.second.end(), [](auto& pTexInfo) 
// 		{
// 			Safe_Delete(pTexInfo); 
// 		});
// 		rPair.second.clear(); 
// 		rPair.second.swap(vector<TEXINFO*>()); 
// 	}
// Attack -0,1,2,3,4,5
// Die - 0,1,2,3,4,5
	for (auto& rPair : m_mapMultiTex)
	{
		for_each(rPair.second.begin(), rPair.second.end(),Safe_Delete<TEXINFO*>);
		rPair.second.clear();
		//rPair.second.swap(vector<TEXINFO*>());
		rPair.second.shrink_to_fit();
	}
}
