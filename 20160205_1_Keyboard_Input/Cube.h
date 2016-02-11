#pragma once
#include <Windows.h>
#include <list>
#include "Vector3D.h"
#include "Matrix.h"
#include "MathDefines.h"

struct Triangle
{
	Triangle()
	{
		vertexIndex[0] = -1;
		vertexIndex[1] = -1;
		vertexIndex[2] = -1;
	}
	Triangle(int index1, int index2, int index3)
	{
		vertexIndex[0] = index1;
		vertexIndex[1] = index2;
		vertexIndex[2] = index3;
	}
	int vertexIndex[3];
};

class CubeAxis
{
public:
	CubeAxis()
	{
		start = end = Vector3D();
		color = RGB(50, 50, 50);
	}
	CubeAxis(Vector3D& _start, Vector3D& _end, COLORREF _color = RGB(50, 50, 50))
	{
		start = _start;
		end = _end;
		color = _color;
	}
	~CubeAxis(){};

	Vector3D start;
	Vector3D end;
	COLORREF color;
};

class Cube
{
public:
	Cube();
	~Cube();

	void Initialize();
	void Update();
	void Render(
		HDC targetDC, 
		const Matrix& view,
		const Matrix& projection, 
		const Matrix& viewport );

	LRESULT CubeInputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	Vector3D* getCubePosition() { return &position; }

protected:
	float rotationAxisX = 0.0f;
	float rotationAxisY = 0.0f;
	
	static const int VERTEX_COUNT = 8;
	static const int TRIANGLE_COUNT = 12;

	Vector3D vertex[VERTEX_COUNT];
	Triangle triangles[TRIANGLE_COUNT];	

	Matrix world;

	bool mouseDown = false;
	POINT mouseStart;

	float xRadian = 0.0f;
	float yRadian = 0.0f;

	float modelY = 3.0f;

	Vector3D direction = Vector3D(0, modelY, 1);
	Vector3D position = Vector3D(0, 3, 0);

	float jumpAngle = PI_HALF;
	float jumpSpeed = 0.07f;
	float gravity = 0.0f;

	bool hasCubeJumped = false;

private:
	std::list<CubeAxis> lines;
};

