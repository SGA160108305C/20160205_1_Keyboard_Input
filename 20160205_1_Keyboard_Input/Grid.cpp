#include "stdafx.h"
#include "Grid.h"


Grid::Grid()
{
}


Grid::~Grid()
{
}

void Grid::Initialize(int lineCount /*= 10*/, float interval/* = 1.0f*/)
{
	lines.clear();
	int halfLineCount = (int)(lineCount * 0.5f);
	float edge = (float)halfLineCount * interval;

	//일반 줄
	COLORREF color = 0;
	for ( int i = 0; i <= halfLineCount; ++i )
	{
		if ( i % 5 == 0 )
		{
			color = RGB(255, 255, 255);
		}
		else
		{
			color = RGB(128, 128, 128);
		}

		lines.push_back(Line(Vector3D(edge, 0.0f, (float)i), Vector3D(-edge, 0.0f, (float)i), color));
		lines.push_back(Line(Vector3D(edge, 0.0f, (float)-i), Vector3D(-edge, 0.0f, (float)-i), color));
		lines.push_back(Line(Vector3D((float)i, 0.0f, edge), Vector3D((float)i, 0.0f, -edge), color));
		lines.push_back(Line(Vector3D((float)-i, 0.0f, edge), Vector3D((float)-i, 0.0f, -edge), color));
	}

	//축
	color = RGB(255, 0, 0);
	lines.push_back(Line(Vector3D(edge, 0.0f, 0.0f), Vector3D(-edge, 0.0f, 0.0f), color));

	color = RGB(0, 255, 0);
	lines.push_back(Line(Vector3D(0.0f, edge, 0.0f), Vector3D(0.0f, -edge, 0.0f), color));

	color = RGB(0, 0, 255);
	lines.push_back(Line(Vector3D(0.0f, 0.0f, edge), Vector3D(0.0f, 0.0f, -edge), color));

}

void Grid::Destroy()
{
	lines.clear();
}

void Grid::Render(HDC targetDC,
	const Matrix& view,
	const Matrix& projection,
	const Matrix& viewport)
{
	Matrix pipeline = view * projection * viewport;
	for ( auto iter = lines.cbegin(); iter != lines.cend(); ++iter )
	{
		Vector3D start = (*iter).start;
		Vector3D end = (*iter).end;

		start = pipeline * start;
		end = pipeline * end;

		COLORREF oldColor = SetDCPenColor(targetDC, ( *iter ).color);
		MoveToEx(targetDC, (int)start.x, (int)start.y, nullptr);
		LineTo(targetDC, (int)end.x, (int)end.y);
		SetDCPenColor(targetDC, oldColor);
	}
}
