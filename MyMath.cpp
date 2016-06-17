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
{
	m_x = 0.0f;
	m_y = 0.0f;
}

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
	vec.m_x = m_x*mat.m_mat[0][0] + m_y*mat.m_mat[1][0] + m_z*mat.m_mat[2][0] + 1 * mat.m_mat[3][0];
	vec.m_y = m_x*mat.m_mat[0][1] + m_y*mat.m_mat[1][1] + m_z*mat.m_mat[2][1] + 1 * mat.m_mat[3][1];
	vec.m_z = m_x*mat.m_mat[0][2] + m_y*mat.m_mat[1][2] + m_z*mat.m_mat[2][2] + 1 * mat.m_mat[3][2];
	return vec;
}

// 잘 되는지 모르겠다....
const Vector3f& Vector3f::operator*(const Matrix4f& mat)
{
	return (*this).Transform(mat);
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

// TODO!!!!!!!!!!!! 초기화
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

void Matrix4f::Multiply(Matrix4f& out, const Matrix4f& mat1, const Matrix4f& mat2)
{
	D3DXMATRIX m1, m2;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m1.m[i][j] = mat1.m_mat[i][j];
			m2.m[i][j] = mat2.m_mat[i][j];
		}
	}

	D3DXMatrixMultiply(&m1, &m1, &m2);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			out.m_mat[i][j] = m1.m[i][j];
		}
	}
}

void Translate(Matrix4f& mat, const Vector3f& vec)
{
	Translate(mat, vec.m_x,vec.m_y,vec.m_z);
}

void Translate(Matrix4f& mat, const float& x, const float& y, const float& z)
{
	D3DXMATRIX ma = Matrix4fToD3DXMATRIX(mat);
	D3DXMatrixTranslation(&ma, x, y, z);
	mat = D3DXMATRIXToMatrix4f(ma);
}

// Degree를 넘기시게
void Rotate(Matrix4f& mat, const Vector3f& vec)
{
	Rotate(mat, vec.m_x, vec.m_y, vec.m_z);
}

// Degree를 넘기시게
void Rotate(Matrix4f& mat, const float& x, const float& y, const float& z)
{
	D3DXMATRIX ma = Matrix4fToD3DXMATRIX(mat);
	D3DXMatrixRotationYawPitchRoll(&ma, Deg2Rad(y), Deg2Rad(x), Deg2Rad(z));
	mat = D3DXMATRIXToMatrix4f(ma);
}

void Scale(Matrix4f& mat, const Vector3f& vec)
{
	Scale(mat, vec.m_x,vec.m_y,vec.m_x);
}

void Scale(Matrix4f& mat, const float& x, const float& y, const float& z)
{
	D3DXMATRIX ma = Matrix4fToD3DXMATRIX(mat);
	D3DXMatrixScaling(&ma, x, y, z);
	mat = D3DXMATRIXToMatrix4f(ma);
}

const D3DXMATRIX& Matrix4fToD3DXMATRIX(const Matrix4f& mat)
{
	D3DXMATRIX ma;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ma.m[i][j] = mat.m_mat[i][j];
		}
	}
	return ma;
}

const Matrix4f& D3DXMATRIXToMatrix4f(const D3DXMATRIX& mat)
{
	Matrix4f ma;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ma.m_mat[i][j] = mat.m[i][j];
		}
	}
	return ma;
}



