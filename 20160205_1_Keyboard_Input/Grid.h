#pragma once
#include <list>
#include "Vector3D.h"
#include "Matrix.h"

class Line
{
public:
	Line()
	{
		start = end = Vector3D();
		color = RGB(50, 50, 50);
	}
	Line(Vector3D& _start, Vector3D& _end, COLORREF _color = RGB(50, 50, 50))
	{
		start = _start;
		end = _end;
		color = _color;
	}
	~Line(){};

	Vector3D start;
	Vector3D end;
	COLORREF color;
};

class Grid
{
public:
	Grid();
	~Grid();

	void Initialize(int lineCount = 10, float interval = 1.0f);
	void Destroy();
	void Render(HDC targetDC,
		const Matrix& view,
		const Matrix& projection,
		const Matrix& viewport);

private:
	std::list<Line> lines;
};

