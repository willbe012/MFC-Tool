#pragma once

typedef struct tagTEXINFO
{
	D3DXIMAGE_INFO tImageInfo;
	LPDIRECT3DTEXTURE9 pTexture; 
}TEXINFO;

typedef struct tagTile
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize; 
	BYTE byDrawID; 
	BYTE byOption; 
}TILE;

typedef struct tagUnitInfo
{
#ifdef _AFX
	//CString wstrName; 
#else 
	//wstring wstrName; 
#endif // _AFX
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	D3DXVECTOR3 vScale;
	D3DXVECTOR3 vRotateAngle;

	D3DXMATRIX matWorld;

	int iAtt;
	int iHp;
	BYTE byJop;
	BYTE byItem;

	BYTE byMonsterIdx;
	//CString wstrName;
	int	iDef;
}UNITINFO;