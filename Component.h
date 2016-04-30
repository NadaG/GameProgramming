#ifndef _COMPONENT_H_
#define _COMPONENT_H_

enum COMPONENT_ID
{
	COLLiDER = 0,
	SPRITERENDERER = 1
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