#pragma once
#include "Texture.h"
class CMultiTexture final:
	public CTexture
{
public:
	explicit CMultiTexture();
	virtual ~CMultiTexture();
public:
	// CTexture��(��) ���� ��ӵ�
	virtual HRESULT Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey = L"", const DWORD & dwCount = 0) override;
	virtual const TEXINFO * Get_Texture(const wstring & wstrStateKey = L"", const DWORD & dwCount = 0) const override;
	void Release_Texture(); 
private:
	map<wstring, vector<TEXINFO*>> m_mapMultiTex; 
};

