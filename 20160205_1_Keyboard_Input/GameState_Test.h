#pragma once
#include "GameState.h"
#include "Cube.h"
#include "Camera.h"
#include "Grid.h"
class GameState_Test :
	public GameState
{
public:
	GameState_Test();
	virtual ~GameState_Test();

	virtual void Update(double tickTime) override;
	virtual void Draw(HDC targetDC) override;

	virtual void OnEnterState() override;
	virtual void OnLeaveState() override;

	virtual LRESULT GameInputProc(
		HWND hWnd, UINT message,
		WPARAM wParam, LPARAM lParam) override;

private:
	Cube* myCube = nullptr;
	Camera* mainCamera = nullptr;
	Grid* grid = nullptr;
};

