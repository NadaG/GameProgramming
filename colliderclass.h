////////////////////////////////////////////////////////////////////////////////
// Filename: colliderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _COLLIDERCLASS_H_
#define _COLLIDERCLASS_H_

#include "Component.h"
#include "d3dclass.h"

enum COLLIDER_TYPE
{
	COL_NONE = 0,
	COL_CUBE = 1,
	COL_SPHERE = 2
};

// 별로 좋지 않은 구조같다
// 한 클래스에 모든 것을 모아두는 듯한 느낌이다 ㅠ
class Collider : public Component
{
public:
	Collider();
	Collider(const COLLIDER_TYPE&);
	Collider(const Collider&);
	virtual ~Collider();
	
	const D3DXVECTOR3& GetCenter();
	const D3DXVECTOR3& GetSize();
	const float& GetRadius();

	const COLLIDER_TYPE& GetType();

	void SetCenter(const D3DXVECTOR3& center);
	void SetSize(const D3DXVECTOR3& size);
	void SetSize(const float& radius);

private:
	D3DXVECTOR3 m_center;
	D3DXVECTOR3 m_size;

	float m_radius;

	COLLIDER_TYPE m_type;
};

#endif