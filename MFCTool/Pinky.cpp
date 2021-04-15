#include "stdafx.h"
#include "Pinky.h"
#include "Texture_Manager.h"
#include "MFCToolView.h"

CPinky::CPinky()
{

}


CPinky::~CPinky()
{
	Release_Object();
}

HRESULT CPinky::Ready_Object()
{
	m_tInfo.vSize = { 40.f, 70.f, 0.f };


	return S_OK;
}

int CPinky::Update_Object()
{
	if (m_bDead)
		return OBJ_DEAD;

	//Matrix_Check();

	return 0;
}

void CPinky::Late_Update_Object()
{
}

void CPinky::Render_Object(CMFCToolView* _pView)
{
	// 좌표 계산
	Matrix_Check();
	Hitbox_Check();

	// 이미지 렌더
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Pinky");

	float fCenterX = pTexInfo->tImageInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImageInfo.Height * 0.5f;

	D3DXVECTOR3 vCenter = { fCenterX, fCenterY, 0.f };

	m_tInfo.matWorld._41 -= _pView->GetScrollPos(SB_HORZ);
	m_tInfo.matWorld._42 -= _pView->GetScrollPos(SB_VERT);

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr/*&rc*/
		, &vCenter, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));



	// 히트박스 렌더
	if (m_bRenderHitBox)
	{

	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"HitBox");
	float fCenterX2 = m_tInfo.vSize.x * 0.5f;
	float fCenterY2 = m_tInfo.vSize.y * 0.5f;
	D3DXVECTOR3 vCenter2 = { fCenterX2, fCenterY2, 0.f };
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, &m_tHitBox
		, &vCenter2, nullptr
		, D3DCOLOR_ARGB(200, 255, 255, 255));

	}
	int i = 0;
}

void CPinky::Release_Object()
{
}

void CPinky::Matrix_Check()
{
	// 최소한의 기능
	D3DXMATRIX matScale, matTransform;
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matTransform);

	D3DXMatrixScaling(&matScale, m_tInfo.vScale.x, m_tInfo.vScale.y, m_tInfo.vScale.z);

	D3DXMatrixTranslation(&matTransform, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTransform;
}
