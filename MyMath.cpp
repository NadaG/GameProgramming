#include "mymath.h"

const float& Rad2Deg(const float& radian)
{
	return radian*180.0f / M_PI;
}

const float& Deg2Rad(const float& degree)
{
	return degree*M_PI / 180.0f;
}

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
{
	return 0;
}

const float& CrossProduct(const Vector2f& a, const Vector2f& b)
{
	return 0;
}

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

// 정규화
const Vector3f& Vector3f::Normalize()
{
	Vector3f t;
	t.m_x = m_x / GetLength();
	t.m_y = m_y / GetLength();
	t.m_z = m_z / GetLength();
	return t;
}

// 크기
const float& Vector3f::GetLength()
{
	return sqrtf(m_x*m_x + m_y*m_y + m_z*m_z);
}

const Vector3f& Vector3f::Transform(const Matrix4f& mat)
{
	Vector3f vec;
	vec.m_x = m_x*mat.m_mat[0][0] + m_y*mat.m_mat[1][0] + m_z*mat.m_mat[2][0];
	vec.m_y = m_x*mat.m_mat[0][1] + m_y*mat.m_mat[1][1] + m_z*mat.m_mat[2][1];
	vec.m_z = m_x*mat.m_mat[0][2] + m_y*mat.m_mat[1][2] + m_z*mat.m_mat[2][2];
	return vec;
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

const float& GetDistance(const Vector3f& a, const Vector3f& b)
{
	return sqrtf((a.m_x - b.m_x)*(a.m_x - b.m_x) +
		(a.m_y - b.m_y)*(a.m_y - b.m_y) +
		(a.m_z - b.m_z)*(a.m_z - b.m_z));
}

Matrix4f::Matrix4f()
{
}

Matrix4f::Matrix4f(const Matrix4f& mat)
{
}

Matrix4f::~Matrix4f()
{
}

const Matrix4f& Matrix4fIdentity()
{
	Matrix4f mat;
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			mat.m_mat[i][j] = 0.0f;
	}
	
	for (int i = 0; i < 4; i++)
		mat.m_mat[i][i] = 1.0f;

	return mat;
}

const Matrix4f& Matrix4f::Multiply(const Matrix4f& mat)
{
	Matrix4f m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float tmp = 0.0f;
			for (int k = 0; k < 4; k++)
			{
				tmp += m_mat[i][k] * mat.m_mat[k][j];
			}
			m.m_mat[i][j] = tmp;
		}
	}
	return m;
}

const Matrix4f& Matrix4f::Translate(const Vector3f& vec)
{
	Matrix4f mat;
	mat.m_mat[0][3] += vec.m_x;
	mat.m_mat[1][3] += vec.m_y;
	mat.m_mat[2][3] += vec.m_z;
	return mat;
}

const Matrix4f& Matrix4f::Translate(const float& x, const float& y, const float& z)
{
	Matrix4f mat;
	mat.m_mat[0][3] += x;
	mat.m_mat[1][3] += y;
	mat.m_mat[2][3] += z;
	return mat;
}

// TODO!!!!!!!!!!!!!!!!!!
const Matrix4f& Matrix4f::Rotate(const Vector3f& vec)
{
	Matrix4f mat;
	return mat;
}

const Matrix4f& Matrix4f::Rotate(const float& x, const float& y, const float& z)
{
	Matrix4f mat, t;
	mat = Matrix4fIdentity();

	mat.m_mat[1][1] = cosf(Deg2Rad(x));
	mat.m_mat[1][2] = -sinf(Deg2Rad(x));
	mat.m_mat[2][1] = sinf(Deg2Rad(x));
	mat.m_mat[2][2] = cosf(Deg2Rad(x));

	t = Matrix4fIdentity();

	t.m_mat[0][0] = cosf(Deg2Rad(y));
	t.m_mat[2][0] = -sinf(Deg2Rad(y));
	t.m_mat[0][2] = sinf(Deg2Rad(y));
	t.m_mat[2][2] = cosf(Deg2Rad(y));
	mat = mat.Multiply(t);

	t = Matrix4fIdentity();
	t.m_mat[0][0] = cosf(Deg2Rad(z));
	t.m_mat[0][1] = -sinf(Deg2Rad(z));
	t.m_mat[1][0] = sinf(Deg2Rad(z));
	t.m_mat[2][1] = cosf(Deg2Rad(z));

	mat = mat.Multiply(t);

	return mat;
}

const Matrix4f& Matrix4f::Scale(const Vector3f& vec)
{
	Matrix4f mat;
	mat.m_mat[0][0] = m_mat[0][0] * vec.m_x;
	mat.m_mat[1][1] = m_mat[1][1] * vec.m_x;
	mat.m_mat[2][2] = m_mat[2][2] * vec.m_x;
	return mat;
}

const Matrix4f& Matrix4f::Scale(const float& x, const float& y, const float& z)
{
	Matrix4f mat;
	mat.m_mat[0][0] = m_mat[0][0] * x;
	mat.m_mat[1][1] = m_mat[1][1] * y;
	mat.m_mat[2][2] = m_mat[2][2] * z;
	return mat;
}



