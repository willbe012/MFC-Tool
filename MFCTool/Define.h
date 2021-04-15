#pragma once

#ifndef _AFX
#define ERR_MSG(Msg) MessageBox(nullptr, L"systemError", Msg, MB_OK)
#else
#define ERR_MSG(Msg) AfxMessageBox(Msg)
#endif

#define TILECX	130
#define TILECY	68
#define TILEX	20
#define TILEY	30
#define ÀåÆÈ»ç¸ð		0x01
#define Ã»·æ¾ð¿ùµµ	0x02 
#define ÀÚ¿õ½Ö°Ë		0x04
#define DECLARE_SINGLETON(clssName)							\
public:														\
	static clssName* Get_Instance()							\
	{														\
		if (nullptr == m_pInstance)							\
			m_pInstance = new clssName;						\
		return m_pInstance;									\
															\
	}														\
	static void Destroy_Instance()							\
	{														\
		if (m_pInstance)									\
		{													\
			delete m_pInstance;								\
			m_pInstance = nullptr;							\
		}													\
	}														\
private:													\
	static clssName* m_pInstance;					
															
#define IMPLEMENT_SINGLETON(className)						\
className* className::m_pInstance = nullptr; 	

#define OBJ_DEAD 1
#define OBJ_NOEVENT 0
#define SAFE_DELETE(p) if(p) {delete p, p = nullptr;}