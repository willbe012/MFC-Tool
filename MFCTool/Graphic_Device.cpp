#include "stdafx.h"
#include "Graphic_Device.h"

CGraphic_Device* CGraphic_Device::m_pInstance = nullptr; 
CGraphic_Device::CGraphic_Device()
	: m_pDevice(nullptr)
	, m_pSDK(nullptr)
{
}


CGraphic_Device::~CGraphic_Device()
{
	Release_Graphic_Device(); 
}

void CGraphic_Device::Render_Begin()
{
	m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 255), 0.f, 0.f);
	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND); 
}

void CGraphic_Device::Render_End(HWND hWnd/*= nullptr*/)
{
	m_pSprite->End(); 
	m_pDevice->EndScene();
	m_pDevice->Present(nullptr, nullptr, hWnd, nullptr);
}

HRESULT CGraphic_Device::Ready_Graphic_Device()
{
	// 	// ��ġ�� �ʱ�ȭ �ϴ� ���� 
	// ��ġ�� ������ �����ϱ� ���� �İ�ü ����. 
	// ��ġ�� ���� ������ ����. 
	// ������ ������ �������� ��ġ�� �����ϴ� �İ�ü ����. 
	D3DCAPS9 caps; 
	ZeroMemory(&caps, sizeof(D3DCAPS9));

	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	//D3DADAPTER_DEFAULT - ���� ���ܵ����� ������ �׷��� ī���� ���� ����ϰڴ�. 
	//D3DDEVTYPE_HAL - HAL�̶�� �߻�������� �����͸� �����ڴ� ��� ��. 
	// ������ ���ڴ� ���� �����͸� �޾ƿ� ����. 
	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		ERR_MSG(L"Get Device Cap Load Failed"); 
		return E_FAIL; 
	}
	DWORD vp = 0; 
	//1000 0000
	//1011 0110

	if (caps.DevCaps &  D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING; 

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS)); 

	d3dpp.BackBufferWidth = g_iWinCX;
	d3dpp.BackBufferHeight = g_iWinCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	// D3DSWAPEFFECT_COPY - �ʳװ� �̶����� ����ϴ� ���� ���۸� ����� ����ϰڴ�. 
	//D3DSWAPEFFECT_DISCARD - ����ü�� ����� ����ϰٴ�. 
	// ����ü���̶�°� ����� �ĸ��� �����ư��� ȭ���� ����ϴ� ���. 
	// �����ϴ� ����� �ƴ϶� ������۸����� ������. 
	// ���� ���ϸ� ������۸��� ���� ȣȯ�̶� �����ϸ� ���ϴ�. 
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	d3dpp.hDeviceWindow = g_hWND;
	d3dpp.Windowed = TRUE;// ��üȭ���� �ϰڴ� ��� FALSE, â����� TRUE
	// ���� ���ۿ� ���ٽ��� ����� ���̳� ��� ���� ���� �ִ�. 
	// ������ 2D�� ���̰� �ʿ� ������ 
	// 2D������ �׷����� �׷��� �� ���̰� �����̰� ���� ������ �׷����� ������ ���ؼ� ����� �Ǵ� �����̱� ������ 
	// ������ ������� �ʴ´� ���ٽǵ� .
	// �׷����� ���� 3D�Ѿ�� ����� ���̱� ������ TRUE�� �־���. �׳� �Ű沨. 

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	

	/* FullScreen_RefreshRateInHz must be zero for Windowed mode */
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
																					//IDirect3DDevice9
	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWND, vp, &d3dpp, &m_pDevice)))
	{
		ERR_MSG(L"m_pDevice's Creation Failed"); 
		return E_FAIL; 
	}
	if(FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		ERR_MSG(L"m_pSprite's Creation Failed");
		return E_FAIL;
	}
	return S_OK;
}

void CGraphic_Device::Release_Graphic_Device()
{
	// �� ���� ����. �� ������� ���� ���� �Ѵ�. 
	if (m_pSprite)
		m_pSprite->Release(); 

	if (m_pDevice)
		m_pDevice->Release(); 

	if (m_pSDK)
		m_pSDK->Release(); 

}
