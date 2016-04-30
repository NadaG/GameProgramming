////////////////////////////////////////////////////////////////////////////////
// Filename: collidercubeclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _COLLIDERCUBECLASS_H_
#define _COLLIDERCUBECLASS_H_

#include "colliderclass.h"
#include "Debug.h"

class ColliderCube : public Collider
{
public:
	ColliderCube();
	ColliderCube(Collider model);
	ColliderCube(const ColliderCube&);
	virtual ~ColliderCube();

protected:
private:

};

#endif