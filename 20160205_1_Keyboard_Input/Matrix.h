#pragma once
#include "Vector3D.h"

class Matrix
{
public:
	Matrix();
	Matrix(const Matrix& other);
	Matrix(const float* numbers);
	~Matrix();

	//대입
	Matrix& operator += (const Matrix& other);
	Matrix& operator -= (const Matrix& other);
	Matrix& operator *= (const Matrix& other);
	Matrix& operator *= (float scalar);
	Matrix& operator /= (float scalar);

	//단항
	Matrix& operator = (const Matrix& other);

	//이항
	Matrix operator + (const Matrix& other) const;
	Matrix operator - (const Matrix& other) const;
	Matrix operator * (const Matrix& other) const;
	Vector3D operator * (const Vector3D& other) const;
	Matrix operator * (float scalar) const;
	Matrix operator / (float scalar) const;

	//비교
	bool operator == (const Matrix& other) const;
	bool operator != (const Matrix& other) const;
	
	//항등행렬
	static void Identity(Matrix& out);

	//전치행렬
	void Transpose(Matrix& out);

	//역행렬
	bool Inverse(Matrix& out);

	//scale
	static void Scale(Matrix& out, float x, float y, float z);	//x,y,z는 배율 (ex:1.0배, 2.1배 등등)
	
	//rotation
	static void RotationX(Matrix& out, float angle);	//angle은 라디안
	static void RotationY(Matrix& out, float angle);
	static void RotationZ(Matrix& out, float angle);

	//translation
	static void Translation(Matrix& out, float x, float y, float z);	//x,y,z는 좌표값

	//랜더링 파이프 라인용 함수들
	static void View(
		Matrix& out,
		Vector3D& eye,
		Vector3D& lookAt,
		Vector3D& up);
	static void Projection(
		Matrix& out,
		float fovY, float aspect,
		float nearZ, float farZ);
	static void ViewPort(
		Matrix& out,
		float x, float y,
		float w, float h,
		float minZ = 0.0f, 
		float maxZ = 1.0f);

	float num[4][4];

protected:
	const float THRESHOLD = 0.001f;
	const int MATRIX_SIZE = 4;

	bool IsSameFloat(const float f1, const float f2) const;
	float Determinant();
};

