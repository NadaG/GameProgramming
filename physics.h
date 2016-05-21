#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "mymath.h"

class Physics
{
public:
	Physics();
	Physics(const Physics& physics);
	Physics& operator=(const Physics& physics);
	~Physics();

	// TODO!!!!!!!!!!!!!!!!!!!!!!!!!!
	// � ������ �Ǿ��ִ��� �� �𸣰ڴ�.
	// �ϴ� ������ �� �ִ� ���� model Ŭ���� �ȿ� Physics ��ü�� �δ� ��?

	// ���̸� �߻��ؼ� �¾Ҵ��� Ȯ���ϴ� �Լ�
	bool RayCast(const Vector3f& origin, const Vector3f& dir, const float& dis);

	// �ӵ��� �ִ� �Լ�...
	void AddForce(const Vector3f& dir, const float& size);

private:
};

#endif