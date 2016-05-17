#ifndef _MYMATH_H_
#define _MYMATH_H_

#include "Debug.h"

// 수학적인 요소들이 들어있는 소스

// TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// namespace 개념을 공부해서 이 및에 부분들을 namespace로 뺄것
class Vector3f
{
public:
	Vector3f();
	Vector3f(const float& x, const float& y, const float& z);
	Vector3f(const Vector3f&);
	~Vector3f();

	const float& GetX();
	const float& GetY();
	const float& GetZ();

	void SetX(const float& x);
	void SetY(const float& y);
	void SetZ(const float& z);
	void SetVector3f(const Vector3f& vec);
	void SetVector3f(const float& x, const float& y, const float& z);

	// 내적
	const float& DotProduct(const Vector3f& a);
	// 외적
	const Vector3f& CrossProduct(const Vector3f& a);
	// 거리
	const float& GetDistance(const Vector3f& a);
	// 정규화
	const Vector3f& Normalize();
	// 크기
	const float& GetLength();

	// 각 요소끼리 합하는 것
	friend const Vector3f& operator+(const Vector3f& a, const Vector3f& b);
	// 각 요소끼리 곱하는 것
	friend Vector3f& operator*(const Vector3f& a, const Vector3f& b);
	// 상수와 벡터 곱
	friend const Vector3f& operator*(const float& a, const Vector3f& b);
	friend const Vector3f& operator*(const Vector3f& a, const float& b);

private:
	float m_x;
	float m_y;
	float m_z;
};


// TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 쿼터니언을 공부해서 4차원 벡터와 좌표계를 사용할것
class Vector4f
{

};

#endif