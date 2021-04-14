#pragma once
// 0x80004005L
// //1000
class CPlayer
{
public:
	CPlayer();
	~CPlayer();
public:
	HRESULT Ready_Player();
	void Update_Player();
	void Render_Player(HDC hDC);
	void Release_Player();
	void MaxtrixWrite(); 
private:
	INFO m_tInfo;
	RECT m_tRect; 
	D3DXVECTOR3 m_vP[4]; // �ִ� ���� �������� ������ ������. 
	D3DXVECTOR3 m_vQ[4]; // �ִ� ���� ������ ���õ� �� P�� ���� ��Ÿ ��ŭ ������ �� ���� ��� ���� ���� ����. 
	float m_fAngle = 10.f; 
};

