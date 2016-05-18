#include "mymath.h"

Vector2f::Vector2f()
{}

Vector2f::Vector2f(const float& x, const float& y)
{
	m_x = x;
	m_y = y;
}

Vector2f::Vector2f(Vector2f& vec)
{
	m_x = vec.m_x;
	m_y = vec.m_y;
}

Vector2f& Vector2f::operator=(Vector2f& vec)
{
	return *this;
}

Vector2f::~Vector2f()
{

}

const float& Vector2f::GetX()
{
	return m_x;
}

const float& Vector2f::GetY()
{
	return m_y;
}

void Vector2f::SetX(const float& x)
{
	m_x = x;
}

void Vector2f::SetY(const float& y)
{
	m_y = y;
}

void Vector2f::SetVector2f(Vector2f& vec)
{
	m_x = vec.m_x;
	m_y = vec.m_y;
}

void Vector2f::SetVector2f(const float& x, const float& y)
{

}

const float& CrossProduct(const float& a, const float& b, const float& c)
{}

const float& CrossProduct(const Vector2f& a, const Vector2f& b)
{}

Vector3f::Vector3f()
{
	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 0.0f;
}

Vector3f::Vector3f(Vector3f& vec)
{
	m_x = vec.m_x;
	m_y = vec.m_y;
	m_z = vec.m_z;
}

Vector3f::Vector3f(const float& x, const float& y, const float& z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

Vector3f::~Vector3f()
{
}

const float& Vector3f::GetX()
{
	return m_x;
}

const float& Vector3f::GetY()
{
	return m_y;
}

const float& Vector3f::GetZ()
{
	return m_z;
}

void Vector3f::SetX(const float& x)
{
	m_x = x;
}

void Vector3f::SetY(const float& y)
{
	m_y = y;
}

void Vector3f::SetZ(const float& z)
{
	m_z = z;
}

void Vector3f::SetVector3f(Vector3f& vec)
{
	m_x = vec.m_x;
	m_y = vec.m_y;
	m_z = vec.m_z;
}

void Vector3f::SetVector3f(const float& x, const float& y, const float& z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

const float& Vector3f::DotProduct(const Vector3f& a)
{
	float t;
	t = a.m_x*m_x + a.m_y*m_y + a.m_z*m_z;
	return t;
}

// n헷 * a의 크기 * b의 크기 * 사인사잇각
const Vector3f& Vector3f::CrossProduct(const Vector3f& a)
{
	Vector3f t;
	t.m_x = m_y*a.m_z - m_z*a.m_y;
	t.m_y = m_z*a.m_x - m_x*a.m_z;
	t.m_z = m_x*a.m_y - m_y*a.m_x;
	return t;
}

const Vector3f& operator+(const Vector3f& a, const Vector3f& b)
{
	Vector3f t;
	t.m_x = a.m_x + b.m_x;
	t.m_y = a.m_y + b.m_y;
	t.m_z = a.m_z + b.m_z;
	return t;
}
Vector3f& operator*(const Vector3f& a, const Vector3f& b)
{
	Vector3f t;
	t.m_x = a.m_x*b.m_x;
	t.m_y = a.m_y*b.m_y;
	t.m_z = a.m_z*b.m_z;
	return t;
}

const Vector3f& operator*(const float& a, const Vector3f& b)
{
	Vector3f t;
	t.m_x = a*b.m_x;
	t.m_y = a*b.m_y;
	t.m_z = a*b.m_z;
	return t;
}

const Vector3f& operator*(const Vector3f& a, const float& b)
{
	return b*a;
}