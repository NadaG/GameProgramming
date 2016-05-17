#ifndef _MYMATH_H_
#define _MYMATH_H_

#include "Debug.h"

// �������� ��ҵ��� ����ִ� �ҽ�

// TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// namespace ������ �����ؼ� �� �׿� �κе��� namespace�� ����
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

	// ����
	const float& DotProduct(const Vector3f& a);
	// ����
	const Vector3f& CrossProduct(const Vector3f& a);
	// �Ÿ�
	const float& GetDistance(const Vector3f& a);
	// ����ȭ
	const Vector3f& Normalize();
	// ũ��
	const float& GetLength();

	// �� ��ҳ��� ���ϴ� ��
	friend const Vector3f& operator+(const Vector3f& a, const Vector3f& b);
	// �� ��ҳ��� ���ϴ� ��
	friend Vector3f& operator*(const Vector3f& a, const Vector3f& b);
	// ����� ���� ��
	friend const Vector3f& operator*(const float& a, const Vector3f& b);
	friend const Vector3f& operator*(const Vector3f& a, const float& b);

private:
	float m_x;
	float m_y;
	float m_z;
};


// TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// ���ʹϾ��� �����ؼ� 4���� ���Ϳ� ��ǥ�踦 ����Ұ�
class Vector4f
{

};

#endif