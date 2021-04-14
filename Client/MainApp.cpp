#include "stdafx.h"
#include "MainApp.h"
#include "Player.h"


CMainApp::CMainApp()
	:m_pPlayer(nullptr)
{
}


CMainApp::~CMainApp()
{
}

void CMainApp::Ready_MainApp()
{
	m_hDC = GetDC(g_hWND); 
	if (nullptr == m_pPlayer)
		m_pPlayer = new CPlayer;
	if (FAILED(m_pPlayer->Ready_Player()))
	{
		MessageBox(nullptr, L"Player Create Failed", L"System Error", MB_OK); 
		if (m_pPlayer)
		{
			delete m_pPlayer;
			m_pPlayer = nullptr; 
		}
		return; 
	}

}

void CMainApp::Update_MainApp()
{
	m_pPlayer->Update_Player(); 
}

void CMainApp::Render_MainApp()
{
	Rectangle(m_hDC, 0, 0, 800, 600); 
	m_pPlayer->Render_Player(m_hDC); 
}

void CMainApp::Release_MainApp()
{
	ReleaseDC(g_hWND, m_hDC); 
	if (m_pPlayer)
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}
}
