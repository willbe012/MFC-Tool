#pragma once
class CTexture; 
class CTexture_Manager
{
	DECLARE_SINGLETON(CTexture_Manager)
public:
	enum TEXID {SINGLE_TEX, MULTI_TEX};
private:
	CTexture_Manager();
	~CTexture_Manager();
public:
	const TEXINFO* Get_TexInfo(const wstring& wstrObjectKey,
		const wstring& wstrStateKey = L"",
		const DWORD& dwIndex = 0);
	HRESULT Insert_Texture(const TEXID eTexID,
		const wstring& wstrFilePath,
		const wstring& wstrObjectKey,
		const wstring& wstrStateKey = L"",
		const DWORD& dwCount = 0);
	void Release_TextureManager(); 
private:
	// ���⿡���� key���� ObjectKey, value - �̱� Ȥ�� ��Ƽ �ؽ��İ� �� ��. 
	map<wstring, CTexture*> m_mapTexture; 
/*	map < wstring, map<wstring, vector<TEXINFO*>>;*/
};

