#pragma once
class Vector3D
{
public:
	Vector3D();
	Vector3D(const Vector3D& other);
	Vector3D(float _x, float _y, float _z);
	~Vector3D();
	
	//대입
	Vector3D& operator = (const Vector3D& other);
	Vector3D& operator += (const Vector3D& other);
	Vector3D& operator -= (const Vector3D& other);
	Vector3D& operator *= (float scalar);
	Vector3D& operator /= (float scalar);

	//단항
	Vector3D operator - () const;

	//이항
	Vector3D operator + (const Vector3D& other) const;
	Vector3D operator - (const Vector3D& other) const;
	Vector3D operator * (float scalar) const;
	Vector3D operator / (float scalar) const;

	//비교
	bool operator == (const Vector3D& other) const;
	bool operator != (const Vector3D& other) const;

	//길이
	float Length();
	float LengthSquar();

	//노멀라이즈
	void Normalize();
	
	//내적
	float Dot(const Vector3D& other) const;

	//외적
	Vector3D Cross(const Vector3D& other) const;


	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

protected:
	const float THRESHOLD = 0.001f;
};

