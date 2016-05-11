#ifndef _COMPONENT_H_
#define _COMPONENT_H_

enum COMPONENT_ID
{
	COM_NONE = 0,
	COM_COLLIDER = 1,
	COM_SPRITERENDERER = 2,
	COM_SCRIPT = 3
};

class Component
{
public:
	Component();
	Component(const Component& component);
	virtual ~Component();

protected:
private:
};

#endif