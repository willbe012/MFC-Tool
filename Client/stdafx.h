// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
// 포함 시키려면 기본 속성 들어가서 VC++디렉토리에 포함디렉터리에서 directx9 폴더에 인클루드 폴더 추가. 
// 그 밑에 밑에 보면 라이브러리 디렉터리 에서도 마찬가지로 추가해줘야 한다. 
#include "d3d9.h"
// 이거 없이도 속성 -> 링커->입력 ->추가 종속성에서 추가해줘도 똑같이 제대로 돌아간다. 
//#pragma comment(lib, "d3d9.lib")
#include "d3dx9.h"
//#pragma comment(lib, "d3dx9.lib")

#include "Total.h"