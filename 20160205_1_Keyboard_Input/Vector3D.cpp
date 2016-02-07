#include <math.h>
#include "Vector3D.h"


Vector3D::Vector3D()
{	
}

Vector3D::Vector3D(const Vector3D& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}
Vector3D::Vector3D(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3D::~Vector3D()
{
}

//대입
Vector3D& Vector3D::operator = (const Vector3D& other)
{
	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

Vector3D& Vector3D::operator += (const Vector3D& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}
Vector3D& Vector3D::operator -= (const Vector3D& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}
Vector3D& Vector3D::operator *= (float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

Vector3D& Vector3D::operator /= (float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

//단항
Vector3D Vector3D::operator - () const
{
	return Vector3D(-x, -y, -z);
}

//이항
Vector3D Vector3D::operator + (const Vector3D& other) const
{
	return Vector3D(x + other.x, y + other.y, z + other.z);
}
Vector3D Vector3D::operator - (const Vector3D& other) const
{
	return Vector3D(x - other.x, y - other.y, z - other.z);
}
Vector3D Vector3D::operator * (float scalar) const
{
	return Vector3D(x * scalar, y * scalar, z * scalar);
}
Vector3D Vector3D::operator / (float scalar) const
{
	return Vector3D(x / scalar, y / scalar, z / scalar);
}

//비교
bool Vector3D::operator == (const Vector3D& other) const
{
	if (fabs(x - other.x) < THRESHOLD
		&& fabs(y - other.y) < THRESHOLD
		&& fabs(z - other.z) < THRESHOLD)
	{
		return true;
	}

	return false;
}
bool Vector3D::operator != (const Vector3D& other) const
{
	if (fabs(x - other.x) > THRESHOLD
		|| fabs(y - other.y) > THRESHOLD
		|| fabs(z - other.z) > THRESHOLD)
	{
		return true;
	}

	return false;
}

//길이
float Vector3D::Length()
{	
	return sqrtf(x*x + y*y + z*z);
}

float Vector3D::LengthSquar()
{
	return (x*x + y*y + z*z);
}

//노멀라이즈
void Vector3D::Normalize()
{
	float length = Length();
	if (length != 0)
	{
		(*this) /= length;
	}
	else
	{
		x = 0;
		y = 0;
		z = 0;
	}
}

//내적
float Vector3D::Dot(const Vector3D& other) const
{
	return (x * other.x + y * other.y + z * other.z);
}

//외적
Vector3D Vector3D::Cross(const Vector3D& other) const
{
	return Vector3D(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
}
