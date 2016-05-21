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
	// 어떤 구조로 되어있는지 잘 모르겠다.
	// 일단 유추할 수 있는 것은 model 클래스 안에 Physics 객체를 두는 것?

	// 레이를 발사해서 맞았는지 확인하는 함수
	bool RayCast(const Vector3f& origin, const Vector3f& dir, const float& dis);

	// 속도를 주는 함수...
	void AddForce(const Vector3f& dir, const float& size);

private:
};

#endif