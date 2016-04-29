////////////////////////////////////////////////////////////////////////////////
// Filename: colliderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _COLLIDERCLASS_H_
#define _COLLIDERCLASS_H_

#include "modelclass.h"

class Collider : public ModelClass
{
public:
	Collider();
	Collider(const Collider&);
	virtual ~Collider();

protected:

	virtual void Update() override;

private:
};

#endif