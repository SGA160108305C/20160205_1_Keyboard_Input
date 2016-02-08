#include "stdafx.h"
#include <windowsx.h>
#include "Cube.h"

Cube::Cube()
{
}


Cube::~Cube()
{
}

void Cube::Initialize()
{
	vertex[0] = Vector3D(-1, 0, -1);
	vertex[1] = Vector3D(-1, 2, -1);
	vertex[2] = Vector3D(1, 2, -1);
	vertex[3] = Vector3D(1, 0, -1);
	vertex[4] = Vector3D(-1, 0, 1);
	vertex[5] = Vector3D(-1, 2, 1);
	vertex[6] = Vector3D(1, 2, 1);
	vertex[7] = Vector3D(1, 0, 1);

	triangles[0] = Triangle(0, 1, 2);
	triangles[1] = Triangle(0, 2, 3);
	triangles[2] = Triangle(4, 6, 5);
	triangles[3] = Triangle(4, 7, 6);
	triangles[4] = Triangle(4, 5, 1);
	triangles[5] = Triangle(4, 1, 0);
	triangles[6] = Triangle(3, 2, 6);
	triangles[7] = Triangle(3, 6, 7);
	triangles[8] = Triangle(1, 5, 6);
	triangles[9] = Triangle(1, 6, 2);
	triangles[10] = Triangle(4, 0, 3);
	triangles[11] = Triangle(4, 3, 7);
}

void Cube::Render(HDC targetDC,
	const Matrix& view,
	const Matrix& projection,
	const Matrix& viewport)
{
	Matrix viewProj = world * view * projection;

	for (int i = 0; i < TRIANGLE_COUNT; ++i)
	{
		Vector3D v1 = 
			vertex[triangles[i].vertexIndex[0]];
		Vector3D v2 =
			vertex[triangles[i].vertexIndex[1]];
		Vector3D v3 =
			vertex[triangles[i].vertexIndex[2]];

		//분리 필요
		/*v1 = viewProj * viewport * v1;
		v2 = viewProj * viewport * v2;
		v3 = viewProj * viewport * v3;*/

		//뷰 메트릭스와 프로젝션 메트릭스 까지만 곱함
		v1 = viewProj * v1;
		v2 = viewProj * v2;
		v3 = viewProj * v3;

		//노멀 벡터 구하기
		Vector3D v1to2 = v2 - v1;
		Vector3D v1to3 = v3 - v1;
		Vector3D normal = v1to2.Cross(v1to3);
		if (normal.Dot(Vector3D(0, 0, 1)) > 0)	//90도 보다 작으므로 컬링
		{
			continue;
		}

		//뷰포트 메트릭스 적용하기
		v1 = viewport * v1;
		v2 = viewport * v2;
		v3 = viewport * v3;

		MoveToEx(targetDC, (int)v1.x, (int)v1.y, nullptr);
		LineTo(targetDC, (int)v2.x, (int)v2.y);
		LineTo(targetDC, (int)v3.x, (int)v3.y);
		LineTo(targetDC, (int)v1.x, (int)v1.y);
	}
}

void Cube::Update()
{
	Matrix translation;
	Matrix::Translation(translation, 0, 0, speed);

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		speed += 0.05f;
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		speed -= 0.05f;
	}

	Matrix rotY;	//y축을 기준으로 회전하는 메트릭스
	//yRadian = (float)PI * 0.25f;
	Matrix::RotationY(rotY, yRadian);

	Matrix rotX;	//x축을 기준으로 회전하는 메트릭스
	//xRadian = (float)PI * 0.25f;
	Matrix::RotationX(rotX, xRadian);

	//항상 초기화 필요
	Matrix::Identity(world);
	//world = world * rotY;
	//world = rotY;	//위 라인이랑 같은 코드
	world = world * translation;
	world = world * rotX * rotY;	//x,y순서에 따라 방향이 틀려짐
		
}

LRESULT Cube::CubeInputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		mouseDown = true;		
		mouseStart.x = GET_X_LPARAM(lParam);
		mouseStart.y = GET_Y_LPARAM(lParam);
	}
		break;
	case WM_LBUTTONUP:
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
			xRadian -= (float)deltaY*0.01f;
			yRadian -= (float)deltaX*0.01f;

			mouseStart = mouseCurrent;
		}
	}
		break;
	default:
		break;
	}
	return 0;
}