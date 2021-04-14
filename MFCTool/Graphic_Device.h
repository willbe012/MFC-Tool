#pragma once
class CGraphic_Device
{
public:
	static CGraphic_Device* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CGraphic_Device; 
		return m_pInstance; 
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance; 
			m_pInstance = nullptr; 
		}
	}
private:
	CGraphic_Device();
	~CGraphic_Device();
public:
	LPDIRECT3DDEVICE9 Get_Device() { return m_pDevice;  }
	LPD3DXSPRITE Get_Sprite() { return m_pSprite; }
public:
	void Render_Begin(); 
	void Render_End(HWND hWnd =nullptr); 

public:
	HRESULT Ready_Graphic_Device(); 
	void Release_Graphic_Device(); 

private:
	static CGraphic_Device* m_pInstance; 

	// com 
	// ��ġ�� �ʱ�ȭ �ϴ� ���� 
	// ��ġ�� ������ �����ϱ� ���� �İ�ü ����. 
	// ��ġ�� ���� ������ ����. 
	// ������ ������ �������� ��ġ�� �����ϴ� �İ�ü ����. 
	LPDIRECT3D9 m_pSDK; 
	LPDIRECT3DDEVICE9 m_pDevice; 
	LPD3DXSPRITE m_pSprite; 
	// com ��ü�� ���״�� ��ǰ�̶�� �����ϸ� �ȴ�. 
	// �츮�� �� �İ�ü�� �̿��Ͽ� ��ġ ���� �����ϵ� ���α׷��� �ϼ��� ������ �Ѵ�. 

};

