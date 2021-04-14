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
	// 	// 장치를 초기화 하는 과정 
	// 장치의 수준을 조사하기 위한 컴객체 생성. 
	// 장치의 지원 수준을 조사. 
	// 조사한 수준을 바탕으로 장치를 제어하는 컴객체 생성. 
	D3DCAPS9 caps; 
	ZeroMemory(&caps, sizeof(D3DCAPS9));

	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	//D3DADAPTER_DEFAULT - 현재 진단도구에 나열된 그래픽 카드의 값을 사용하겠다. 
	//D3DDEVTYPE_HAL - HAL이라는 추상계층에서 데이터를 얻어오겠다 라는 뜻. 
	// 마지막 인자는 얻어온 데이터를 받아올 공간. 
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

	// D3DSWAPEFFECT_COPY - 너네가 이때까지 사용하던 더블 버퍼링 방식을 사용하겠다. 
	//D3DSWAPEFFECT_DISCARD - 스왑체인 방식을 사용하겟다. 
	// 스왑체인이라는건 전면과 후면을 번갈아가며 화면을 출력하는 방식. 
	// 복사하는 방식이 아니라 더블버퍼링보다 빠르다. 
	// 쉽게 말하면 더블버퍼링의 상위 호환이라 생각하면 편하다. 
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	d3dpp.hDeviceWindow = g_hWND;
	d3dpp.Windowed = TRUE;// 전체화면을 하겠다 라면 FALSE, 창모드라면 TRUE
	// 깊이 버퍼와 스텐실을 사용할 것이냐 라는 것을 묻고 있다. 
	// 당장은 2D라서 깊이가 필요 없으며 
	// 2D에서는 그려지는 그려야 할 것이고 나발이고 없이 오로지 그려지는 순서에 의해서 출력이 되는 형식이기 때문에 
	// 당장은 사용하지 않는다 스텐실도 .
	// 그렇지만 나중 3D넘어가서 사용할 것이기 때문에 TRUE로 넣어줌. 그냥 신경꺼. 

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
	// 단 순서 주의. 이 순서대로 지워 져야 한다. 
	if (m_pSprite)
		m_pSprite->Release(); 

	if (m_pDevice)
		m_pDevice->Release(); 

	if (m_pSDK)
		m_pSDK->Release(); 

}
