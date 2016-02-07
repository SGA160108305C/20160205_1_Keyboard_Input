#include <Windows.h>
#include <math.h>
#include "Matrix.h"


Matrix::Matrix()
{
	ZeroMemory(num, sizeof(float) * MATRIX_SIZE * MATRIX_SIZE);
}

Matrix::Matrix(const Matrix& other)
{
	int copySize = sizeof(float)*MATRIX_SIZE*MATRIX_SIZE;
	memcpy_s(num, copySize, other.num, copySize);
}

Matrix::Matrix(const float* numbers)
{
	int copySize = sizeof(float)*MATRIX_SIZE*MATRIX_SIZE;
	memcpy_s(num, copySize, numbers, copySize);
}

Matrix::~Matrix()
{
}

//대입
Matrix& Matrix::operator = (const Matrix& other)
{
	int copySize = sizeof(float)*MATRIX_SIZE*MATRIX_SIZE;
	memcpy_s(num, copySize, other.num, copySize);

	return *this;
}

Matrix& Matrix::operator += (const Matrix& other)
{
	num[0][0] += other.num[0][0]; num[0][1] += other.num[0][1]; num[0][2] += other.num[0][2]; num[0][3] += other.num[0][3];
	num[1][0] += other.num[1][0]; num[1][1] += other.num[1][1]; num[1][2] += other.num[1][2]; num[1][3] += other.num[1][3];
	num[2][0] += other.num[2][0]; num[2][1] += other.num[2][1]; num[2][2] += other.num[2][2]; num[2][3] += other.num[2][3];
	num[3][0] += other.num[3][0]; num[3][1] += other.num[3][1]; num[3][2] += other.num[3][2]; num[3][3] += other.num[3][3];
	
	return *this;
}

Matrix& Matrix::operator -= (const Matrix& other)
{
	num[0][0] -= other.num[0][0]; num[0][1] -= other.num[0][1]; num[0][2] -= other.num[0][2]; num[0][3] -= other.num[0][3];
	num[1][0] -= other.num[1][0]; num[1][1] -= other.num[1][1]; num[1][2] -= other.num[1][2]; num[1][3] -= other.num[1][3];
	num[2][0] -= other.num[2][0]; num[2][1] -= other.num[2][1]; num[2][2] -= other.num[2][2]; num[2][3] -= other.num[2][3];
	num[3][0] -= other.num[3][0]; num[3][1] -= other.num[3][1]; num[3][2] -= other.num[3][2]; num[3][3] -= other.num[3][3];

	return *this;
}

Matrix& Matrix::operator *= (const Matrix& other)
{
	Matrix temp;
	for (int i = 0; i < MATRIX_SIZE; ++i)
	{
		for (int j = 0; j < MATRIX_SIZE; ++j)
		{
			for (int k = 0; k < MATRIX_SIZE; ++k)
			{
				temp.num[i][j] += (num[i][k] * other.num[k][j]);
			}
		}
	}
	*this = temp;

	return *this;
}

Matrix& Matrix::operator *= (float scalar)
{
	num[0][0] *= scalar; num[0][1] *= scalar; num[0][2] *= scalar; num[0][3] *= scalar;
	num[1][0] *= scalar; num[1][1] *= scalar; num[1][2] *= scalar; num[1][3] *= scalar;
	num[2][0] *= scalar; num[2][1] *= scalar; num[2][2] *= scalar; num[2][3] *= scalar;
	num[3][0] *= scalar; num[3][1] *= scalar; num[3][2] *= scalar; num[3][3] *= scalar;

	return *this;
}

Matrix& Matrix::operator /= (float scalar)
{
	num[0][0] /= scalar; num[0][1] /= scalar; num[0][2] /= scalar; num[0][3] /= scalar;
	num[1][0] /= scalar; num[1][1] /= scalar; num[1][2] /= scalar; num[1][3] /= scalar;
	num[2][0] /= scalar; num[2][1] /= scalar; num[2][2] /= scalar; num[2][3] /= scalar;
	num[3][0] /= scalar; num[3][1] /= scalar; num[3][2] /= scalar; num[3][3] /= scalar;

	return *this;
}

//이항
Matrix Matrix::operator + (const Matrix& other) const
{
	Matrix ret;
	ret.num[0][0] = num[0][0] + other.num[0][0]; ret.num[0][1] = num[0][1] + other.num[0][1]; ret.num[0][2] = num[0][2] + other.num[0][2]; ret.num[0][3] = num[0][3] + other.num[0][3];
	ret.num[1][0] = num[1][0] + other.num[1][0]; ret.num[1][1] = num[1][1] + other.num[1][1]; ret.num[1][2] = num[1][2] + other.num[1][2]; ret.num[1][3] = num[1][3] + other.num[1][3];
	ret.num[2][0] = num[2][0] + other.num[2][0]; ret.num[2][1] = num[2][1] + other.num[2][1]; ret.num[2][2] = num[2][2] + other.num[2][2]; ret.num[2][3] = num[2][3] + other.num[2][3];
	ret.num[3][0] = num[3][0] + other.num[3][0]; ret.num[3][1] = num[3][1] + other.num[3][1]; ret.num[3][2] = num[3][2] + other.num[3][2]; ret.num[3][3] = num[3][3] + other.num[3][3];

	return ret;
}

Matrix Matrix::operator - (const Matrix& other) const
{
	Matrix ret;
	ret.num[0][0] = num[0][0] - other.num[0][0]; ret.num[0][1] = num[0][1] - other.num[0][1]; ret.num[0][2] = num[0][2] - other.num[0][2]; ret.num[0][3] = num[0][3] - other.num[0][3];
	ret.num[1][0] = num[1][0] - other.num[1][0]; ret.num[1][1] = num[1][1] - other.num[1][1]; ret.num[1][2] = num[1][2] - other.num[1][2]; ret.num[1][3] = num[1][3] - other.num[1][3];
	ret.num[2][0] = num[2][0] - other.num[2][0]; ret.num[2][1] = num[2][1] - other.num[2][1]; ret.num[2][2] = num[2][2] - other.num[2][2]; ret.num[2][3] = num[2][3] - other.num[2][3];
	ret.num[3][0] = num[3][0] - other.num[3][0]; ret.num[3][1] = num[3][1] - other.num[3][1]; ret.num[3][2] = num[3][2] - other.num[3][2]; ret.num[3][3] = num[3][3] - other.num[3][3];

	return ret;
}

Matrix Matrix::operator * (const Matrix& other) const
{
	Matrix ret;
	for (int i = 0; i < MATRIX_SIZE; ++i)
	{
		for (int j = 0; j < MATRIX_SIZE; ++j)
		{
			for (int k = 0; k < MATRIX_SIZE; ++k)
			{
				ret.num[i][j] += (num[i][k] * other.num[k][j]);
			}
		}
	}

	return ret;
}

Vector3D Matrix::operator * (const Vector3D& other) const
{
	Vector3D ret;
	ret.x = num[0][0] * other.x + num[1][0] * other.y + num[2][0] * other.z + num[3][0] * 1.0f;
	ret.y = num[0][1] * other.x + num[1][1] * other.y + num[2][1] * other.z + num[3][1] * 1.0f;
	ret.z = num[0][2] * other.x + num[1][2] * other.y + num[2][2] * other.z + num[3][2] * 1.0f;
	float w = num[0][3] * other.x + num[1][3] * other.y + num[2][3] * other.z + num[3][3] * 1.0f;
	if (IsSameFloat(w, 0.0f) == false)
	{
		ret /= w;
	}
	return ret;
}

Matrix Matrix::operator * (float scalar) const
{
	Matrix ret;
	ret.num[0][0] = num[0][0] * scalar; ret.num[0][1] = num[0][1] * scalar; ret.num[0][2] = num[0][2] * scalar; ret.num[0][3] = num[0][3] * scalar;
	ret.num[1][0] = num[1][0] * scalar; ret.num[1][1] = num[1][1] * scalar; ret.num[1][2] = num[1][2] * scalar; ret.num[1][3] = num[1][3] * scalar;
	ret.num[2][0] = num[2][0] * scalar; ret.num[2][1] = num[2][1] * scalar; ret.num[2][2] = num[2][2] * scalar; ret.num[2][3] = num[2][3] * scalar;
	ret.num[3][0] = num[3][0] * scalar; ret.num[3][1] = num[3][1] * scalar; ret.num[3][2] = num[3][2] * scalar; ret.num[3][3] = num[3][3] * scalar;
	return ret;
}

Matrix Matrix::operator / (float scalar) const
{
	Matrix ret;
	ret.num[0][0] = num[0][0] / scalar; ret.num[0][1] = num[0][1] / scalar; ret.num[0][2] = num[0][2] / scalar; ret.num[0][3] = num[0][3] / scalar;
	ret.num[1][0] = num[1][0] / scalar; ret.num[1][1] = num[1][1] / scalar; ret.num[1][2] = num[1][2] / scalar; ret.num[1][3] = num[1][3] / scalar;
	ret.num[2][0] = num[2][0] / scalar; ret.num[2][1] = num[2][1] / scalar; ret.num[2][2] = num[2][2] / scalar; ret.num[2][3] = num[2][3] / scalar;
	ret.num[3][0] = num[3][0] / scalar; ret.num[3][1] = num[3][1] / scalar; ret.num[3][2] = num[3][2] / scalar; ret.num[3][3] = num[3][3] / scalar;
	return ret;
}


//비교
bool Matrix::operator == (const Matrix& other) const
{
	bool same = true;
	for (int i = 0; i < MATRIX_SIZE; ++i)
	{
		for (int j = 0; j < MATRIX_SIZE; ++j)
		{
			if (IsSameFloat(num[i][j], other.num[i][j]) == false)
			{
				same = false;
				break;
			}
		}
	}
	return same;
}

bool Matrix::operator != (const Matrix& other) const
{
	bool different = false;
	for (int i = 0; i < MATRIX_SIZE; ++i)
	{
		for (int j = 0; j < MATRIX_SIZE; ++j)
		{
			if (IsSameFloat(num[i][j], other.num[i][j]) == false)
			{
				different = true;
				break;
			}
		}
	}
	return different;
}


//항등행렬
void Matrix::Identity(Matrix& out)
{
	float identity[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	out = Matrix(identity);
}


//전치행렬
void Matrix::Transpose(Matrix& out)
{
	for (int i = 0; i < MATRIX_SIZE; ++i)
	{
		for (int j = 0; j < MATRIX_SIZE; ++j)
		{
			out.num[i][j] = num[j][i];	
		}
	}
}


//역행렬
bool Matrix::Inverse(Matrix& out)
{
	float det = Determinant();
	if (IsSameFloat(det, 0.0f) == true)
	{
		Identity(out);
		return false;
	}

	float b[16] = {
		num[1][1] * num[2][2] * num[3][3]
		+ num[1][2] * num[2][3] * num[3][1]
		+ num[1][3] * num[2][1] * num[3][2]
		- num[1][1] * num[2][3] * num[3][2]
		- num[1][2] * num[2][1] * num[3][3]
		- num[1][3] * num[2][2] * num[3][1],

		num[0][1] * num[2][3] * num[3][2]
		+ num[0][2] * num[2][1] * num[3][3]
		+ num[0][3] * num[2][2] * num[3][1]
		- num[0][1] * num[2][2] * num[3][3]
		- num[0][2] * num[2][3] * num[3][1]
		- num[0][3] * num[2][1] * num[3][2],

		num[0][1] * num[1][2] * num[3][3]
		+ num[0][2] * num[1][3] * num[3][1]
		+ num[0][3] * num[1][1] * num[3][2]
		- num[0][1] * num[1][3] * num[3][2]
		- num[0][2] * num[1][1] * num[3][3]
		- num[0][3] * num[1][2] * num[3][1],

		num[0][1] * num[1][3] * num[2][2]
		+ num[0][2] * num[1][1] * num[2][3]
		+ num[0][3] * num[1][2] * num[2][1]
		- num[0][1] * num[1][2] * num[2][3]
		- num[0][2] * num[1][3] * num[2][1]
		- num[0][3] * num[1][1] * num[2][2],
		//
		num[1][0] * num[2][3] * num[3][2]
		+ num[1][2] * num[2][0] * num[3][3]
		+ num[1][3] * num[2][2] * num[3][0]
		- num[1][0] * num[2][2] * num[3][3]
		- num[1][2] * num[2][3] * num[3][0]
		- num[1][3] * num[2][0] * num[3][2],

		num[0][0] * num[2][2] * num[3][3]
		+ num[0][2] * num[2][3] * num[3][0]
		+ num[0][3] * num[2][0] * num[3][2]
		- num[0][0] * num[2][3] * num[3][2]
		- num[0][2] * num[2][0] * num[3][3]
		- num[0][3] * num[2][2] * num[3][0],

		num[0][0] * num[1][3] * num[3][2]
		+ num[0][2] * num[1][0] * num[3][3]
		+ num[0][3] * num[1][2] * num[3][0]
		- num[0][0] * num[1][2] * num[3][3]
		- num[0][2] * num[1][3] * num[3][0]
		- num[0][3] * num[1][0] * num[3][2],

		num[0][0] * num[1][2] * num[2][3]
		+ num[0][2] * num[1][3] * num[2][0]
		+ num[0][3] * num[1][0] * num[2][2]
		- num[0][0] * num[1][3] * num[2][2]
		- num[0][2] * num[1][0] * num[2][3]
		- num[0][3] * num[1][2] * num[2][0],
		//
		num[1][0] * num[2][1] * num[3][3]
		+ num[1][1] * num[2][3] * num[3][0]
		+ num[1][3] * num[2][0] * num[3][1]
		- num[1][0] * num[2][3] * num[3][1]
		- num[1][1] * num[2][0] * num[3][3]
		- num[1][3] * num[2][1] * num[3][0],

		num[0][0] * num[2][3] * num[3][1]
		+ num[0][1] * num[2][0] * num[3][3]
		+ num[0][3] * num[2][1] * num[3][0]
		- num[0][0] * num[2][1] * num[3][3]
		- num[0][1] * num[2][3] * num[3][0]
		- num[0][3] * num[2][0] * num[3][1],

		num[0][0] * num[1][1] * num[3][3]
		+ num[0][1] * num[1][3] * num[3][0]
		+ num[0][3] * num[1][0] * num[3][1]
		- num[0][0] * num[1][3] * num[3][1]
		- num[0][1] * num[1][0] * num[3][3]
		- num[0][3] * num[1][1] * num[3][0],

		num[0][0] * num[1][3] * num[2][1]
		+ num[0][1] * num[1][0] * num[2][3]
		+ num[0][3] * num[1][1] * num[2][0]
		- num[0][0] * num[1][1] * num[2][3]
		- num[0][1] * num[1][3] * num[2][0]
		- num[0][3] * num[1][0] * num[2][1],
		//
  		  num[1][0] * num[2][2] * num[3][1]
		+ num[1][1] * num[2][0] * num[3][2]
		+ num[1][2] * num[2][1] * num[3][0]
		- num[1][0] * num[2][1] * num[3][2]
		- num[1][1] * num[2][2] * num[3][0]
		- num[1][2] * num[2][0] * num[3][1],

		  num[0][0] * num[2][1] * num[3][2]
		+ num[0][1] * num[2][2] * num[3][0]
		+ num[0][2] * num[2][0] * num[3][1]
		- num[0][0] * num[2][2] * num[3][1]
		- num[0][1] * num[2][0] * num[3][2]
		- num[0][2] * num[2][1] * num[3][0],
				
		  num[0][0] * num[1][2] * num[3][1]
		+ num[0][1] * num[1][0] * num[3][2]
		+ num[0][2] * num[1][1] * num[3][0]
		- num[0][0] * num[1][1] * num[3][2]
		- num[0][1] * num[1][2] * num[3][0]
		- num[0][2] * num[1][0] * num[3][1],

		  num[0][0] * num[1][1] * num[2][2]
		+ num[0][1] * num[1][2] * num[2][0]
		+ num[0][2] * num[1][0] * num[2][1]
		- num[0][0] * num[1][2] * num[2][1]
		- num[0][1] * num[1][0] * num[2][2]
		- num[0][2] * num[1][1] * num[2][0]
	};
	out = Matrix(b) / det;

	return true;
}

float Matrix::Determinant()
{
	float det =
		num[0][0] * num[1][1] * num[2][2] * num[3][3]
		+ num[0][0] * num[1][2] * num[2][3] * num[3][1]
		+ num[0][0] * num[1][3] * num[2][1] * num[3][2]

		+ num[0][1] * num[1][0] * num[2][3] * num[3][2]
		+ num[0][1] * num[1][2] * num[2][0] * num[3][3]
		+ num[0][1] * num[1][3] * num[2][2] * num[3][0]

		+ num[0][2] * num[1][0] * num[2][1] * num[3][3]
		+ num[0][2] * num[1][1] * num[2][3] * num[3][0]
		+ num[0][2] * num[1][3] * num[2][0] * num[3][1]

		+ num[0][3] * num[1][0] * num[2][2] * num[3][1]
		+ num[0][3] * num[1][1] * num[2][0] * num[3][2]
		+ num[0][3] * num[1][2] * num[2][1] * num[3][0]

		- num[0][0] * num[1][1] * num[2][3] * num[3][2]
		- num[0][0] * num[1][2] * num[2][1] * num[3][3]
		- num[0][0] * num[1][3] * num[2][2] * num[3][1]

		- num[0][1] * num[1][0] * num[2][2] * num[3][3]
		- num[0][1] * num[1][2] * num[2][3] * num[3][0]
		- num[0][1] * num[1][3] * num[2][0] * num[3][2]

		- num[0][2] * num[1][0] * num[2][3] * num[3][1]
		- num[0][2] * num[1][1] * num[2][0] * num[3][3]
		- num[0][2] * num[1][3] * num[2][1] * num[3][0]

		- num[0][3] * num[1][0] * num[2][1] * num[3][2]
		- num[0][3] * num[1][1] * num[2][2] * num[3][0]
		- num[0][3] * num[1][2] * num[2][0] * num[3][1];

	return det;
}

bool Matrix::IsSameFloat(const float f1, const float f2) const
{
	return (fabs(f1 - f2) < THRESHOLD);
}

//scale
void Matrix::Scale(Matrix& out, float x, float y, float z)
{
	Identity(out);
	out.num[0][0] = x;
	out.num[1][1] = y;
	out.num[2][2] = z;
}

//rotation
void Matrix::RotationX(Matrix& out, float angle)
{
	Identity(out);
	out.num[1][1] = cos(angle);
	out.num[1][2] = sin(angle);
	out.num[2][1] = -sin(angle);
	out.num[2][2] = cos(angle);
}
void Matrix::RotationY(Matrix& out, float angle)
{
	Identity(out);
	out.num[0][0] = cos(angle);
	out.num[0][2] = -sin(angle);
	out.num[2][0] = sin(angle);
	out.num[2][2] = cos(angle);
}
void Matrix::RotationZ(Matrix& out, float angle)
{
	Identity(out);
	out.num[0][0] = cos(angle);
	out.num[0][1] = sin(angle);
	out.num[1][0] = -sin(angle);
	out.num[1][1] = cos(angle);
}

//translation
void Matrix::Translation(Matrix& out, float x, float y, float z)
{
	//x,y,z는 좌표값
	Identity(out);
	out.num[3][0] = x;
	out.num[3][1] = y;
	out.num[3][2] = z;
}

void Matrix::View(Matrix& out, Vector3D& eye, Vector3D& lookAt, Vector3D& up)
{
	Vector3D lookDir = (lookAt - eye);
	lookDir.Normalize();

	Vector3D rightDir = up.Cross(lookDir);
	rightDir.Normalize();

	Vector3D upDir = lookDir.Cross(rightDir);
	upDir.Normalize();

	Matrix::Identity(out);
	out.num[0][0] = rightDir.x; 
	out.num[0][1] = upDir.x; 
	out.num[0][2] = lookDir.x;
	out.num[1][0] = rightDir.y; 
	out.num[1][1] = upDir.y; 
	out.num[1][2] = lookDir.y;
	out.num[2][0] = rightDir.z; 
	out.num[2][1] = upDir.z; 
	out.num[2][2] = lookDir.z;
	out.num[3][0] = -rightDir.Dot(eye);
	out.num[3][1] = -upDir.Dot(eye);
	out.num[3][2] = -lookDir.Dot(eye);
}

void Matrix::Projection(Matrix& out, float fovY, float aspect, float nearZ, float farZ)
{
	Matrix::Identity(out);

	float scaleY = 1.0f / tanf(fovY / 2.0f);
	float scaleX = scaleY / aspect;

	out.num[0][0] = scaleX;
	out.num[1][1] = scaleY;
	out.num[2][2] = farZ / (farZ - nearZ);
	out.num[2][3] = 1.0f;
	out.num[3][2] = -farZ * nearZ / (farZ - nearZ);
	out.num[3][3] = 0.0f;
}

void Matrix::ViewPort(Matrix& out, float x, float y, float w, float h, float minZ /*= 0.0f*/, float maxZ /*= 1.0f*/)
{
	Matrix::Identity(out);

	out.num[0][0] = w * 0.5f;
	out.num[1][1] = -h * 0.5f;
	out.num[2][2] = maxZ - minZ;
	out.num[3][0] = x + w * 0.5f;
	out.num[3][1] = y + h * 0.5f;
	out.num[3][2] = minZ;
}
