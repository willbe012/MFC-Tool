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
		// D3DPOOL - ���� �����͸� ��� ������ �������� �ް� �ִ�. 
		//D3DPOOL_DEFAULT - gpu�� �޸𸮰����� ����ϰڴ�. �ӵ������δ� ���� ������. 
		//D3DPOOL_SYSTEMMEM - �ý��� �޸� ������ ����ϰڴ�. �ӵ������δ� �������� �������̴�. 
		// D3DPOOL_MANAGED - gpu�� �ý��� �޸� �α��� �� ����ϰڴ�. - �������̸鼭 ������. 
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT, 
		0,nullptr,nullptr,
		&m_tTexInfo.pTexture)))
	{
		wstring wstrErrMsg = wstrFilePath + L"�ҷ����� ����. - SingleTeture.cpp"; 
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
