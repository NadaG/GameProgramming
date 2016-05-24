////////////////////////////////////////////////////////////////////////////////
// Filename: colliderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _COLLIDERCLASS_H_
#define _COLLIDERCLASS_H_

#include "Component.h"
#include "d3dclass.h"
#include "mymath.h"

// TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Ÿ�� �������ٴ� ��ӱ����� ������ ����!!!!!!!!!!
enum COLLIDER_TYPE
{
	COL_NONE = 0,
	COL_CUBE = 1,
	COL_SPHERE = 2
};

// ���� ���� ���� ��������
// �� Ŭ������ ��� ���� ��Ƶδ� ���� �����̴� ��
class Collider : public Component
{
public:
	Collider();
	Collider(const COLLIDER_TYPE&);
	Collider(const Collider&);
	virtual ~Collider();
	
	const Vector3f& GetCenter();
	const Vector3f& GetSize();
	const Vector3f& GetRotation();
	const float& GetRadius();

	const COLLIDER_TYPE& GetType();

	void SetCenter(const Vector3f& center);
	void SetSize(const Vector3f& size);
	void SetRotation(const Vector3f& rotation);
	void SetRadius(const float& radius);

private:
	Vector3f m_center;
	Vector3f m_size;
	Vector3f m_rotation;

	float m_radius;


	COLLIDER_TYPE m_type;
};

#endif