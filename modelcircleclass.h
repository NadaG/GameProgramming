#ifndef _MODELCIRCLECLASS_H_
#define _MODELCIRCLECLASS_H_

#include <d3d11.h>
#include <d3dx10math.h>

#include "textureclass.h"
#include "modelclass.h"

// circle class�� model class�� �ڽ����� �� ��
class ModelCircleClass : public ModelClass
{
protected:
	virtual bool LoadModel() override;
	// final�� �������� ����, override�� override�� �Լ����� ����

	//virtual void SetRadius(float r) override;
};

#endif