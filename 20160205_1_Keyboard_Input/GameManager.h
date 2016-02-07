#pragma once
#include <Windows.h>
#include <list>
#include "GameState.h"
#include "MathDefines.h"


enum GAME_STATE
{
	TEST = 0,
	NUM_OF_GAME_STATE
};

class GameManager
{
public:
	GameManager();
	~GameManager();

	//윈도우 기본 정보가 될 데이터
	static const int RESOLUTION_X = 1280;
	static const int RESOLUTION_Y = 720;
	static const WCHAR WINDOW_CLASS_NAME[];		
	static const WCHAR WINDOW_TITLE_CAPTION[];	

	void Initialize(HWND handle);
	void Destroy();

	void Loop(double tick);		
	LRESULT GameInputProc(
		HWND hWnd, UINT message, 
		WPARAM wParam, LPARAM lParam);

	void ChangeGameState(GAME_STATE state);
	
	const HWND GetWindowHandle(){ return windowHandle; }
	//inline const Matrix& GetViewMatrix(){ return viewMatrix; }
	//inline const Matrix& GetProjectionMatrix(){ return projectionMatrix; }
	inline const Matrix& GetViewPortMatrix(){ return viewportMatrix; }


private:
	double lastTickTime = 0.0f;

	GAME_STATE currentState = GAME_STATE::TEST;
	GameState* gameStates[GAME_STATE::NUM_OF_GAME_STATE];

	HWND windowHandle = nullptr;
	HDC hMemDC = nullptr;
	HBITMAP hMemBitmap = nullptr;
	HBITMAP hOldBitmap = nullptr;

	//Matrix viewMatrix;
	//Matrix projectionMatrix;
	Matrix viewportMatrix;
	//Vector3D eye = Vector3D(0,0,-5);
	//Vector3D lookAt = Vector3D(0,0,0);
	//Vector3D up = Vector3D(0,1,0);
	//float fov = (float)PI_HALF;
	//float nearDistance = 1.0f;
	//float farDistance = 1000.0f;


	void Update(double tickTime);
	void Draw();				

	
};

