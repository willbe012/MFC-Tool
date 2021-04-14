#pragma once
#include "Texture.h"

class CSingleTexture final :
	public CTexture
{
public:
	CSingleTexture();
	virtual ~CSingleTexture();
public:
	// CTexture��(��) ���� ��ӵ�
	virtual HRESULT Insert_Texture(const wstring & wstrFilePath,
		const wstring & wstrStateKey = L"",
		const DWORD & dwCount = 0) override;
	virtual const TEXINFO*  Get_Texture(const wstring& wstrStateKey = L"",
		const DWORD& dwCount = 0) const;
	void Release_Texture() ;

private:
	TEXINFO m_tTexInfo; 

};

