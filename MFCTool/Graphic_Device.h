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
	// 장치를 초기화 하는 과정 
	// 장치의 수준을 조사하기 위한 컴객체 생성. 
	// 장치의 지원 수준을 조사. 
	// 조사한 수준을 바탕으로 장치를 제어하는 컴객체 생성. 
	LPDIRECT3D9 m_pSDK; 
	LPDIRECT3DDEVICE9 m_pDevice; 
	LPD3DXSPRITE m_pSprite; 
	// com 객체는 말그대로 부품이라고 생각하면 된다. 
	// 우리는 이 컴객체를 이용하여 마치 레고 조립하듯 프로그램을 완성해 나가야 한다. 

};

