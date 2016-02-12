#include <windowsx.h>
#include "Camera.h"
#include "GameManager.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::Initialize(Vector3D* cubePosition, float* xRadian, float* yRadian)
{
	pCubePosition = cubePosition;
	pXradian = xRadian;
	pYradian = yRadian;
	Matrix::View(viewMatrix, eye, lookAt, up);
	Matrix::Projection(projectionMatrix,
		fov, (float)GameManager::RESOLUTION_X / (float)GameManager::RESOLUTION_Y,
		nearDistance, farDistance);
}

void Camera::Destroy()
{

}

void Camera::Update()
{
	/*if (pXradian)
	{
		camRotX = (*pXradian);
	}

	if (pYradian)
	{
		camRotY = (*pYradian);
	}*/

	Matrix rotX, rotY;
	Matrix::RotationX(rotX, camRotX);
	Matrix::RotationY(rotY, camRotY);

	eye = Vector3D(0, 0, -cameraDistance);
	eye = rotX * rotY * eye;

	if (pCubePosition)
	{
		lookAt = (*pCubePosition);
		eye = (*pCubePosition) + eye;
	}

	Matrix::View(viewMatrix, eye, lookAt, up);
}

LRESULT Camera::CameraInputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_RBUTTONDOWN:
	{
		mouseDown = true;
		mouseStart.x = GET_X_LPARAM(lParam);
		mouseStart.y = GET_Y_LPARAM(lParam);
	}
	break;
	case WM_RBUTTONUP:
	{
		mouseDown = false;
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (mouseDown)
		{
			POINT mouseCurrent;
			mouseCurrent.x = GET_X_LPARAM(lParam);
			mouseCurrent.y = GET_Y_LPARAM(lParam);

			int deltaX = mouseCurrent.x - mouseStart.x;
			int deltaY = mouseCurrent.y - mouseStart.y;
			camRotX += (float)deltaY*0.01f;
			camRotY -= (float)deltaX*0.01f;

			mouseStart = mouseCurrent;
		}
	}
	break;
	case WM_MOUSEWHEEL:
	{
		cameraDistance -= GET_WHEEL_DELTA_WPARAM(wParam) * 0.01f;
		if (cameraDistance < 1.0f)
			cameraDistance = 1.0f;
	}
	default:
		break;
	}
	return 0;

}
