#pragma once
#include <Windows.h>
#include "Matrix.h"
#include "Vector3D.h"
#include "MathDefines.h"
class Camera
{
public:
	Camera();
	~Camera();
	void Initialize();
	void Destroy();
	void Update();

	LRESULT CameraInputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	inline const Matrix& GetViewMatrix(){ return viewMatrix; }
	inline const Matrix& GetProjectionMatrix(){ return projectionMatrix; }

private :
	Matrix viewMatrix;
	Matrix projectionMatrix;

	Vector3D eye = Vector3D(0, 0, 0);
	Vector3D lookAt = Vector3D(0, 0, 0);
	Vector3D up = Vector3D(0, 1, 0);

	float fov = (float)PI_HALF;
	float nearDistance = 1.0f;
	float farDistance = 1000.0f;

	float camRotX = 0.7f;
	float camRotY = 0.0f;
	float cameraDistance = 10.0f;

	bool mouseDown = false;
	POINT mouseStart;
};

