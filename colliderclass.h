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

class Collider : public Component
{
public:
	Collider();
	Collider(const COLLIDER_TYPE&);
	Collider(const Collider&);
	virtual ~Collider();
	
	const D3DXVECTOR3& GetCenter();
	const D3DXVECTOR3& GetSize();

	const COLLIDER_TYPE& GetType();

	void SetCenter(const D3DXVECTOR3 center);
	void SetSize(const D3DXVECTOR3 size);
private:
	D3DXVECTOR3 m_center;
	D3DXVECTOR3 m_size;

	COLLIDER_TYPE m_type;
};

#endif