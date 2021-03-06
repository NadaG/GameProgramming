#ifndef _MYMATH_H_
#define _MYMATH_H_

// 수학적인 요소들이 들어있는 소스
#include<cmath>
#include<iostream>

//#include "debug.h"
#include "d3dclass.h"

// TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const float M_PI = 3.141592653f;
// namespace 개념을 공부해서 이 및에 부분들을 namespace로 뺄것

// mymath의 모든 함수들은 인자로 정보를 출력하지 않고
// 리턴으로 정보를 돌려주는 식으로 처리된다!!

class Matrix4f;

class Vector2f
{
public:
	Vector2f();
	Vector2f(const float& x, const float& y);
	Vector2f(Vector2f& vec);
	Vector2f& operator=(Vector2f& vec);
	~Vector2f();

	const float& GetX();
	const float& GetY();

	void SetX(const float& x);
	void SetY(const float& y);
	void SetVector2f(Vector2f& vec);
	void SetVector2f(const float& x, const float& y);

	friend const float& CrossProduct(const float& a, const float& b, const float& c);
	friend const float& CrossProduct(const Vector2f& a, const Vector2f& b);

	float m_x;
	float m_y;
};

class Vector3f
{
public:
	Vector3f();
	Vector3f(const float& x, const float& y, const float& z);
	Vector3f(Vector3f&);
	~Vector3f();

	void SetVector3f(Vector3f& vec);
	void SetVector3f(const float& x, const float& y, const float& z);

	// 내적
	const float& DotProduct(const Vector3f& a);
	// 외적
	const Vector3f& CrossProduct(const Vector3f& a);
	// 정규화
	const Vector3f& Normalize();
	// 크기 반환
	const float& GetLength();

	// 같은 것입니다
	const Vector3f& Transform(const Matrix4f& mat);
	const Vector3f& operator*(const Matrix4f& mat);

	// 각 요소끼리 합하는 것
	friend const Vector3f& operator+(const Vector3f& a, const Vector3f& b);
	// 각 요소끼리 곱하는 것
	friend Vector3f& operator*(const Vector3f& a, const Vector3f& b);
	// 상수와 벡터 곱
	friend const Vector3f& operator*(const float& a, const Vector3f& b);
	friend const Vector3f& operator*(const Vector3f& a, const float& b);

	friend const float& GetDistance(const Vector3f& a, const Vector3f& b);

public:

	float m_x;
	float m_y;
	float m_z;
};


// TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 쿼터니언을 공부해서 4차원 벡터와 좌표계를 사용할것
class Vector4f
{
};

class Matrix4f
{
public:
	Matrix4f();
	Matrix4f(const Matrix4f& mat);
	~Matrix4f();

	friend const Matrix4f& Matrix4fIdentity();
	void Multiply(Matrix4f& out, const Matrix4f& mat1, const Matrix4f& mat2);

	friend void Translate(Matrix4f& mat, const Vector3f& vec);
	friend void Translate(Matrix4f& mat, const float& x, const float& y, const float& z);

	friend void Rotate(Matrix4f& mat, const Vector3f& vec);
	friend void Rotate(Matrix4f& mat, const float& x, const float& y, const float& z);

	friend void Scale(Matrix4f& mat, const Vector3f& vec);
	friend void Scale(Matrix4f& mat, const float& x, const float& y, const float& z);

	friend const D3DXMATRIX& Matrix4fToD3DXMATRIX(const Matrix4f& mat);
	friend const Matrix4f& D3DXMATRIXToMatrix4f(const D3DXMATRIX& mat);

	float m_mat[4][4];
};



#endif