#ifndef _MYMATH_H_
#define _MYMATH_H_

// �������� ��ҵ��� ����ִ� �ҽ�
#include<cmath>

// TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const float M_PI = 3.141592653f;
// namespace ������ �����ؼ� �� �׿� �κе��� namespace�� ����

// mymath�� ��� �Լ����� ���ڷ� ������ ������� �ʰ�
// �������� ������ �����ִ� ������ ó���ȴ�!!

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

	// ����
	const float& DotProduct(const Vector3f& a);
	// ����
	const Vector3f& CrossProduct(const Vector3f& a);
	// �Ÿ�
	//const float& GetDistance(const Vector3f& a);
	// ����ȭ
	const Vector3f& Normalize();
	// ũ��
	const float& GetLength();

	const Vector3f& Transform(const Matrix4f& mat);

	// �� ��ҳ��� ���ϴ� ��
	friend const Vector3f& operator+(const Vector3f& a, const Vector3f& b);
	// �� ��ҳ��� ���ϴ� ��
	friend Vector3f& operator*(const Vector3f& a, const Vector3f& b);
	// ����� ���� ��
	friend const Vector3f& operator*(const float& a, const Vector3f& b);
	friend const Vector3f& operator*(const Vector3f& a, const float& b);

	friend const float& GetDistance(const Vector3f& a, const Vector3f& b);

	float m_x;
	float m_y;
	float m_z;
};


// TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// ���ʹϾ��� �����ؼ� 4���� ���Ϳ� ��ǥ�踦 ����Ұ�
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
	const Matrix4f& Multiply(const Matrix4f& mat);

	const Matrix4f& Translate(const Vector3f& vec);
	const Matrix4f& Translate(const float& x, const float& y, const float& z);

	const Matrix4f& Rotate(const Vector3f& vec);
	const Matrix4f& Rotate(const float& x, const float& y, const float& z);

	const Matrix4f& Scale(const Vector3f& vec);
	const Matrix4f& Scale(const float& x, const float& y, const float& z);

	float m_mat[4][4];
};



#endif