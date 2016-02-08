#pragma once
#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <time.h>

using namespace std;
#pragma comment(lib, "winmm.lib")

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

//수학용
#include "MathDefines.h"
#include "Vector3D.h"
#include "Matrix.h"

#include "keyManager.h"
#define KEYMANAGER keyManager::getSingleton()

//각종 게임 상태들
#include "GameState.h"
#include "GameState_Test.h"

//관리용 메니저
#include "GameManager.h"


extern GameManager g_GameManager;
