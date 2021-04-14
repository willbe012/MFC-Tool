#pragma once
class CMFCToolView; 
class CTerrain final 
{
public:
	explicit CTerrain();
	~CTerrain();
public:
	void Set_View(CMFCToolView* pView) { m_pView = pView; }
public:
	void Tile_Picking(const D3DXVECTOR3& vMouse, const BYTE& byDrawID, const BYTE& byOption = 0);
	int Get_TileIndex(const D3DXVECTOR3& vPos); 
	bool Is_Picking(const D3DXVECTOR3& vPos,const int& iIndex); 
	void Set_Ratio(D3DXMATRIX* pOut, float RX, float RY);
public:
	HRESULT Ready_Terrain(); 
	void	Update_Terrain(); 
	void	Render_Terrain();
	void	MiniRender_Terrain(); 
	void	Release_Terrain(); 

private:
	CMFCToolView* m_pView; 
	vector<TILE*> m_vecTile; 
};

