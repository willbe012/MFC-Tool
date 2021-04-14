#pragma once
class CPlayer; 
class CMainApp
{
public:
	CMainApp();
	~CMainApp();

public:
	void Ready_MainApp(); 
	void Update_MainApp(); 
	void Render_MainApp(); 
	void Release_MainApp(); 
private:
	HDC m_hDC; 
	CPlayer* m_pPlayer; 
};

