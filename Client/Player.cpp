#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
	:m_fAngle(0.f)
{
	ZeroMemory(m_vP, sizeof(D3DXVECTOR3) * 4); 
	ZeroMemory(m_vQ, sizeof(D3DXVECTOR3) * 4); 
}


CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Ready_Player()
{
	m_tInfo.vDir = { -1.f, 0.f, 0.f }; 
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vSize = { 100.f, 100.f, 0.f };

	// �»� - -
	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f }; 
	// ��� + - 
	m_vP[1] = { m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	// ���� ++
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	// ���� - + 
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	return S_OK; 
}

void CPlayer::Update_Player()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_tInfo.vPos.x -= 5.f;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_tInfo.vPos.x += 5.f; 
	if (GetAsyncKeyState(VK_UP))
		m_tInfo.vPos.y -= 5.f; 
	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.vPos.y += 5.f; 
	m_fAngle += 5.f;
	D3DXMATRIX matWorld, matScale, matRotX, matRotY,matRotZ, matTrans, matParent;
	D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 0.f);
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(m_fAngle));
	D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fAngle));
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matParent, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixTranslation(&matTrans, 100.f, 100.f, 0.f);
	//matWorld = matScale * matRotX *  matRotY *matRotZ * matTrans;
	// 1		2			3			4
	matWorld = matScale * matTrans * matRotZ * matParent; 

	int i = 0; 
	for (int i = 0 ; i < 4 ; ++ i)
	{
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld); 
	}
}

void CPlayer::Render_Player(HDC hDC)
{
	MoveToEx(hDC, m_vQ[0].x, m_vQ[0].y, nullptr); 

	for (int i = 1; i < 4; ++i)
		LineTo(hDC, m_vQ[i].x, m_vQ[i].y); 
	LineTo(hDC, m_vQ[0].x, m_vQ[0].y);

	m_tRect.left = LONG(m_tInfo.vPos.x - (10)); 
	m_tRect.right = LONG(m_tInfo.vPos.x + 10);
	m_tRect.top = LONG(m_tInfo.vPos.y - 10);
	m_tRect.bottom = LONG(m_tInfo.vPos.y + 10);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);


	MaxtrixWrite(); 
}

void CPlayer::Release_Player()
{
}

void CPlayer::MaxtrixWrite()
{

	// ��ġ�� 400, 300��ġ�� ������ ũ��� x�����δ� 2������ Ű��� ������ 45���� ������ �������� ���ھ�� 
// 	D3DXMATRIX matWorld, matTrans, matScale, matRotZ; 
// 	D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);
// 	D3DXMatrixScaling(&matScale, 2.f, 1.f, 0.f);
// 	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(45.f));
// 	matWorld = matScale * matRotZ * matTrans; 
	// ����� ������ ��� ������ �ſ� �߿��ϴ�. 
	//  �� �� �� �� �� 
	// ũ	*	��	*	��	*	��	*	�� 
	// ��		��		��		��		��

	// vector�� ��İ��� ������ �������ִ� �� ���� �Լ� 
//	D3DXVec3TransformCoord(); // ���͸� 1X4 �κ�ȯ�� w ���� 1�� ä���� ������ ����. �����-> 1x4
//	D3DXVec3TransformNormal();// ���͸� 1X4 �κ�ȯ�� w ���� 0�� ä���� ������ ����. �����-> 1x4
// 	D3DXMATRIX mat; 
// 	//�׵���ķ� ��ȯ���ִ� �Լ�. 
// 	D3DXMatrixIdentity(&mat); 
// 	/*
// 		1	0	0	0
// 		0	1	0	0
// 		0	0	1	0
// 		0	0	0	1
// 	*/
// 
// 	D3DXMatrixScaling(&mat, 2.f, 3.f, 0.f); 
	// ũ�⸦ �������ִ� �Լ�. 
	// * ��� ���� �Լ����� ��κ� ���� pout �� ���� �׵���ķ� ��ȯ �� ���� �����ϴ� ���·� ����ȴ�. 
	/*
	x	0	0	0
	0	y	0	0
	0	0	z	0
	0	0	0	1
	*/

	// �̵� ���� ��� �Լ�. 
	// * ��� ���� �Լ����� ��κ� ���� pout �� ���� �׵���ķ� ��ȯ �� ���� �����ϴ� ���·� ����ȴ�. 
//	D3DXMatrixTranslation(&mat, 400.f, 300.f, 0.f);
	/*
	1	0	0	0
	0	1	0	0
	0	0	1	0
	x	y	z	1
	*/

	// ȸ�� ���� ��� �Լ� X,Y, Z
	//D3DXMatrixRotationX(&mat, //�����̾�� �Ѵ�)
	/*
	1	0		0		0
	0	cos		sin		0
	0	-sin	cos		0
	0	0		0		1
	*/
	//D3DXMatrixRotationY(&mat, //�����̾�� �Ѵ�)
	/*
	cos		0		-sin	0
	0		1		0		0
	sin		0		cos		0
	0		0		0		1
	*/
	//D3DXMatrixRotationZ(&mat, //�����̾�� �Ѵ�)
	/*
	cos		sin		0		0
	-sin	cos		0		0
	0		0		1		0
	0		0		0		1
	*/
}
