#ifndef _MODELCUBECLASS_H_
#define _MODELCUBECLASS_H_

#include<D3DX11.h>
#include<D3DX10math.h>

#include"textureclass.h"
#include"modelclass.h"

class ModelCubeClass : public ModelClass
{
protected:
	virtual bool LoadModel() override;
	//virtual void SetX() override;

public:

	ModelCubeClass()
	{
		m_size = { 2, 2, 2 };
		m_center = { 0, -3, 2 };
	}

	const float& GetWidth() const;
	const float& GetHeight() const;
	const float& GetDepth() const;

	const float& GetX() const;
	const float& GetY() const;
	const float& GetZ() const;

	void SetPosition(float x, float y, float z);
	void SetSize(float x, float y, float z);

private:
	D3DVECTOR m_size;
	D3DVECTOR m_center;
};

#endif