#include "stdafx.h"
#include "Terrain.h"
#include "Texture_Manager.h"
#include "MFCToolView.h"


CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
	Release_Terrain();
}

void CTerrain::Tile_Picking(const D3DXVECTOR3 & vMouse, const BYTE & byDrawID, const BYTE & byOption)
{

	int iIndex = Get_TileIndex(vMouse);
	int iSize = m_vecTile.size();
	if (iSize <= iIndex || 0 > iIndex)
		return;

	m_vecTile[iIndex]->byDrawID = byDrawID;
	m_vecTile[iIndex]->byOption = byOption;
}

int CTerrain::Get_TileIndex(const D3DXVECTOR3 & vPos)
{
	int iSize = m_vecTile.size();
	for (int i = 0; i < iSize; ++i)
	{
		if (Is_Picking(vPos, i))
			return i;
	}
	return -1;
}

bool CTerrain::Is_Picking(const D3DXVECTOR3 & vPos, const int & iIndex)
{
	// 	// 보여줄 방법. 1.과 2가 있다. 선택해라. 
	// 	// 직선의 방정식을 이용한 방법. 
	// 	// 내적을 이용한 방법. 
	// 	// y = ax + b; 
	// 	//a = y/x
	// 	// 챕터 원! 기울기를 구해라! 
	// 	float fa[4] = 
	// 	{
	// 		(TILECY * 0.5f) / (TILECX * 0.5f),
	// 		(-TILECY * 0.5f) / (TILECX * 0.5f),
	// 		(TILECY * 0.5f) / (TILECX * 0.5f),
	// 		(-TILECY * 0.5f) / (TILECX * 0.5f)
	// 	};
	// 
	// 	// 마름모꼴 정점 구할꺼. 
	// 	// 챕터 투!! 마름모꼴 정점을 구해라! 
	// 	D3DXVECTOR3 vVertex[4] =
	// 	{
	// 		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + (TILECY * 0.5f), 0.f}, 
	// 		{ m_vecTile[iIndex]->vPos.x + (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y , 0.f},
	// 		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - (TILECY * 0.5f), 0.f },
	// 		{ m_vecTile[iIndex]->vPos.x - (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y , 0.f }
	// 
	// 	}; 
	// 	/*
	// 	     * 여기 
	// 	   /   \
	//여기*      * 여기
	// 	   \   /
	// 	     * 여기 
	// 	 */
	// 
	// 	// 챕터 쓰리! y절편을 구해라!
	// 	// b= y - ax
	// 	float fb[4] = 
	// 	{
	// 		vVertex[0].y - (fa[0] * vVertex[0].x),
	// 		vVertex[1].y - (fa[1] * vVertex[1].x),
	// 		vVertex[2].y - (fa[2] * vVertex[2].x),
	// 		vVertex[3].y - (fa[3] * vVertex[3].x),
	// 	}; 
	// 
	// 	// 0 = ax + b - y 
	// 	if(0 < (fa[0] * vPos.x) + fb[0] - vPos.y && 
	// 		0 < (fa[1] * vPos.x) + fb[1] - vPos.y &&
	// 		0 > (fa[2] * vPos.x) + fb[2] - vPos.y &&
	// 		0 > (fa[3] * vPos.x) + fb[3] - vPos.y )
	// 		return true;
	// 
	// 	return false; 

		//////////////////////////내적을 이용한 픽킹방법 ////////////////////////////////////////////////
		// 챕터 원! - 마름모꼴 정점을 구해라! 
	D3DXVECTOR3 vVertex[4] =
	{
		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + (TILECY * 0.5f), 0.f},
		{ m_vecTile[iIndex]->vPos.x + (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y , 0.f},
		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - (TILECY * 0.5f), 0.f },
		{ m_vecTile[iIndex]->vPos.x - (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y , 0.f }
	};
	// 챕터 투! 각 정점을 바라보는 방향벡터를 구해라 ! 
	D3DXVECTOR3 vVertexDir[4] = 
	{
		vVertex[1] - vVertex[0],
		vVertex[2] - vVertex[1],
		vVertex[3] - vVertex[2],
		vVertex[0] - vVertex[3],
	}; 

	//챕터 쓰리! 정점을 바라보는 방향벡터의 법선벡터를 구하자!!!!!! 
	D3DXVECTOR3 vNormal[4] = 
	{
		{-vVertexDir[0].y, vVertexDir[0].x, vVertexDir[0].z}, 
		{ -vVertexDir[1].y, vVertexDir[1].x, vVertexDir[0].z },
		{ -vVertexDir[2].y, vVertexDir[2].x, vVertexDir[0].z },
		{ -vVertexDir[3].y, vVertexDir[3].x, vVertexDir[0].z }

	}; 
	//챕터 포! 정점에서 마우스를 바라보는 방향벡터를 구하자!!!! 
	D3DXVECTOR3 vMouseDir[4] = 
	{
		vPos - vVertex[0], 
		vPos - vVertex[1],
		vPos - vVertex[2],
		vPos - vVertex[3]
	}; 

	//챕터 파이브! 두 벡터를 내적했을 때 나오는 결과가 양수냐 음수냐 에 따라 ! 결정이 된다. 
	if (0 < D3DXVec3Dot(&vMouseDir[0], &vNormal[0]) || 0 < D3DXVec3Dot(&vMouseDir[1], &vNormal[1]) || 0 < D3DXVec3Dot(&vMouseDir[2], &vNormal[2]) || 0 < D3DXVec3Dot(&vMouseDir[3], &vNormal[3]))
		return false; 
	return true;
}

void CTerrain::Set_Ratio(D3DXMATRIX * pOut, float RX, float RY)
{
	pOut->_11 *= RX; 
	pOut->_21 *= RX;
	pOut->_31 *= RX;
	pOut->_41 *= RX;

	pOut->_12 *= RY;
	pOut->_22 *= RY;
	pOut->_32 *= RY;
	pOut->_42 *= RY;

	/*
		x	y	z	w
	x	11	12	13	14 ->right
	y	21	22	23	24 ->up
	z	31	32	33	34 ->look
	w	41	42	43	44 ->pos
	*/
}

HRESULT CTerrain::Ready_Terrain()
{
	m_vecTile.reserve(TILEX * TILEY);
	float fX = 0.f, fY = 0.f;
	TILE* pTile = nullptr;
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			pTile = new TILE;
			fX = (TILECX * j) + ((i % 2) *(TILECX >> 1));
			fY = (TILECY * 0.5f) * i;
			pTile->vPos = { fX, fY, 0.f };
			pTile->vSize = { 1.f, 1.f ,0.f };
			pTile->byOption = 0;
			pTile->byDrawID = 9;
			m_vecTile.emplace_back(pTile);
		}
	}
	return S_OK;
}

void CTerrain::Update_Terrain()
{
}

void CTerrain::Render_Terrain()
{
	int iIndex = 0;
	D3DXMATRIX matWorld, matScale, matTrans;
	float fCenterX = 0.f, fCenterY = 0.f;
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			iIndex = j + (TILEX * i);
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", m_vecTile[iIndex]->byDrawID);
			fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
			fCenterY = static_cast<float>(pTexInfo->tImageInfo.Height >> 1);

			D3DXMatrixScaling(&matScale, m_vecTile[iIndex]->vSize.x, m_vecTile[iIndex]->vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->vPos.x - m_pView->GetScrollPos(SB_HORZ), m_vecTile[iIndex]->vPos.y - m_pView->GetScrollPos(SB_VERT), 0.f);
			matWorld = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
	}
}

void CTerrain::MiniRender_Terrain()
{
	int iIndex = 0;
	D3DXMATRIX matWorld, matScale, matTrans, matRatio;
	D3DXMatrixScaling(&matRatio, 0.3f, 0.3f, 0.f);
	float fCenterX = 0.f, fCenterY = 0.f;
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			iIndex = j + (TILEX * i);
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", m_vecTile[iIndex]->byDrawID);
			fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
			fCenterY = static_cast<float>(pTexInfo->tImageInfo.Height >> 1);

			D3DXMatrixScaling(&matScale, m_vecTile[iIndex]->vSize.x, m_vecTile[iIndex]->vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->vPos.x - m_pView->GetScrollPos(SB_HORZ), m_vecTile[iIndex]->vPos.y - m_pView->GetScrollPos(SB_VERT), 0.f);
			matWorld = matScale * matTrans;
			//Set_Ratio(&matWorld, 0.3f, 0.3f); 
			matWorld *= matRatio; 
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
	}
}

void CTerrain::Release_Terrain()
{
	for (auto& pTile : m_vecTile)
	{
		Safe_Delete(pTile);
	}
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}
