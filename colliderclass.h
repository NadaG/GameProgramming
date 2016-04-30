////////////////////////////////////////////////////////////////////////////////
// Filename: colliderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _COLLIDERCLASS_H_
#define _COLLIDERCLASS_H_

#include "Component.h"

class Collider : public Component
{
public:
	Collider();
	Collider(const Collider&);
	virtual ~Collider();

protected:
private:
};

#endif