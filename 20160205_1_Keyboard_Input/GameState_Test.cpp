#include "stdafx.h"
#include "GameState_Test.h"


GameState_Test::GameState_Test()
{
}


GameState_Test::~GameState_Test()
{
}

void GameState_Test::Update(double tickTime)
{
	if (myCube != nullptr)
	{
		myCube->Update();
	}
	if (mainCamera != nullptr)
	{
		mainCamera->Update();
	}
}

void GameState_Test::Draw(HDC targetDC)
{
	if (grid != nullptr)
	{
		grid->Render(targetDC,
			mainCamera->GetViewMatrix(),
			mainCamera->GetProjectionMatrix(),
			g_GameManager.GetViewPortMatrix()
			);
	}
	if (myCube != nullptr)
	{
		myCube->Render(
			targetDC,
			mainCamera->GetViewMatrix(),
			mainCamera->GetProjectionMatrix(),
			g_GameManager.GetViewPortMatrix()
			);
	}
}

void GameState_Test::OnEnterState()
{
	if (myCube != nullptr)
	{
		delete myCube;
		myCube = nullptr;
	}
	myCube = new Cube();
	myCube->Initialize();

	if (mainCamera != nullptr)
	{
		delete mainCamera;
		mainCamera = nullptr;
	}
	mainCamera = new Camera();
	mainCamera->Initialize();

	if (grid != nullptr)
	{
		delete grid;
		grid = nullptr;
	}
	grid = new Grid();
	grid->Initialize();
}

void GameState_Test::OnLeaveState()
{
	if (myCube != nullptr)
	{
		delete myCube;
		myCube = nullptr;
	}
	if (mainCamera != nullptr)
	{
		delete mainCamera;
		mainCamera = nullptr;
	}
	if (grid != nullptr)
	{
		delete grid;
		grid = nullptr;
	}
}

LRESULT GameState_Test::GameInputProc(
	HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	if (myCube)
	{
		result = myCube->CubeInputProc(hWnd, message, wParam, lParam);
	}
	if (mainCamera)
	{
		result = mainCamera->CameraInputProc(hWnd, message, wParam, lParam);
	}
	return result;
}
