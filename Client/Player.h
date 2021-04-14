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
	D3DXVECTOR3 m_vP[4]; // 애는 원점 기준으로 세팅할 정점들. 
	D3DXVECTOR3 m_vQ[4]; // 애는 원점 기준을 쎄팅된 점 P를 일정 쎄타 만큼 돌렸을 때 나올 결과 값을 담을 변수. 
	float m_fAngle = 10.f; 
};

