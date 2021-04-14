#include "stdafx.h"
#include "SingleTexture.h"


CSingleTexture::CSingleTexture()
{
	ZeroMemory(&m_tTexInfo, sizeof(TEXINFO)); 
}


CSingleTexture::~CSingleTexture()
{
	Release_Texture(); 
}

HRESULT CSingleTexture::Insert_Texture(const wstring & wstrFilePath,
	const wstring & wstrStateKey /*= L""*/,
	const DWORD & dwCount /*= 0*/)
{
	if (FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &m_tTexInfo.tImageInfo)))
	{
		ERR_MSG(L"Get Image Data Failed"); 
		return E_FAIL; 
	}
	if (FAILED(D3DXCreateTextureFromFileEx(CGraphic_Device::Get_Instance()->Get_Device(), wstrFilePath.c_str(),
		m_tTexInfo.tImageInfo.Width,
		m_tTexInfo.tImageInfo.Height, 
		m_tTexInfo.tImageInfo.MipLevels,
		0,
		m_tTexInfo.tImageInfo.Format, 
		// D3DPOOL - 얻어온 데이터를 어디에 보관할 것인지를 받고 있다. 
		//D3DPOOL_DEFAULT - gpu의 메모리공간만 사용하겠다. 속도상으로는 가장 빠르다. 
		//D3DPOOL_SYSTEMMEM - 시스템 메모리 공간을 사용하겠다. 속도적으로는 느리지만 안정적이다. 
		// D3DPOOL_MANAGED - gpu와 시스템 메모리 두군데 다 사용하겠다. - 안정적이면서 빠르다. 
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT, 
		0,nullptr,nullptr,
		&m_tTexInfo.pTexture)))
	{
		wstring wstrErrMsg = wstrFilePath + L"불러오기 실패. - SingleTeture.cpp"; 
		ERR_MSG(wstrErrMsg.c_str()); 
		return E_FAIL;
	}
}

const TEXINFO * CSingleTexture::Get_Texture(const wstring & wstrStateKey, const DWORD & dwCount) const
{
	return &m_tTexInfo;

}


void CSingleTexture::Release_Texture()
{
	if (m_tTexInfo.pTexture)
		m_tTexInfo.pTexture->Release(); 
}
