#include "stdafx.h"
#include "GameManager.h"


const WCHAR GameManager::WINDOW_CLASS_NAME[] = L"Win32App";
const WCHAR GameManager::WINDOW_TITLE_CAPTION[] = L"SGA Programing";

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
	Destroy();
}

void GameManager::Initialize(HWND handle)
{
	windowHandle = handle;

	gameStates[GAME_STATE::TEST] = new GameState_Test();
	currentState = GAME_STATE::TEST;
	ChangeGameState(currentState);	

	
	RECT clientRect;
	GetClientRect(windowHandle, &clientRect);
	HDC hDC = GetDC(windowHandle);

	hMemDC = CreateCompatibleDC(hDC);
	hMemBitmap = CreateCompatibleBitmap(hDC, clientRect.right, clientRect.bottom);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hMemBitmap);

	SetTextColor(hMemDC, RGB(255, 255, 255));

	SetBkMode(hMemDC, TRANSPARENT);

	ReleaseDC(windowHandle, hDC);		

	SetGraphicsMode(hMemDC, GM_ADVANCED);

	//Matrix::View(viewMatrix, eye, lookAt, up);
	//Matrix::Projection(projectionMatrix,
	//	fov, (float)RESOLUTION_X / (float)RESOLUTION_Y,
	//	nearDistance, farDistance);
	Matrix::ViewPort(viewportMatrix,
		0, 0,
		(float)RESOLUTION_X,
		(float)RESOLUTION_Y);

	
}

void GameManager::Destroy()
{
	
	if ( hOldBitmap )
	{
		SelectObject(hMemDC, hOldBitmap);
		hOldBitmap = nullptr;
	}
	if ( hMemBitmap )
	{
		DeleteObject(hMemBitmap);
		hMemBitmap = nullptr;
	}
	if ( hMemDC )
	{
		DeleteDC(hMemDC);
		hMemDC = nullptr;
	}

	for ( int i = 0; i < GAME_STATE::NUM_OF_GAME_STATE; ++i )
	{
		if ( gameStates[i] != nullptr )
		{
			gameStates[i]->OnLeaveState();
			delete gameStates[i];
			gameStates[i] = nullptr;
		}
	}

}

void GameManager::Loop(double tick)
{
	Update(tick);
	Draw();
}

void GameManager::Update(double tickTime)
{
	lastTickTime = tickTime;

	gameStates[currentState]->Update(tickTime);
}

void GameManager::Draw()
{
	if ( windowHandle == nullptr )
		return;

	RECT clientRect;
	GetClientRect(windowHandle, &clientRect);

	FillRect(hMemDC, &clientRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
	
	HPEN defaultPen = (HPEN)SelectObject(hMemDC, GetStockObject(DC_PEN));
	HBRUSH defaultBrush = (HBRUSH)SelectObject(hMemDC, GetStockObject(DC_BRUSH));
	
	SetDCPenColor(hMemDC, RGB(255, 255, 255));	
	SetDCBrushColor(hMemDC, RGB(255, 255, 255));

	gameStates[currentState]->Draw(hMemDC);

	SelectObject(hMemDC, defaultBrush);
	SelectObject(hMemDC, defaultPen);


	HDC hDC = GetDC(windowHandle);
	
	BitBlt(hDC, 0, 0, clientRect.right, clientRect.bottom, hMemDC, 0, 0, SRCCOPY);
	ReleaseDC(windowHandle, hDC);
	InvalidateRect(windowHandle, &clientRect, false);
}

void GameManager::ChangeGameState(GAME_STATE state)
{
	gameStates[currentState]->OnLeaveState();
	currentState = state;
	gameStates[currentState]->OnEnterState();
}

LRESULT GameManager::GameInputProc(
	HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	return gameStates[currentState]->GameInputProc(hWnd, message, wParam, lParam);
}