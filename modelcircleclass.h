#ifndef _MODELCIRCLECLASS_H_
#define _MODELCIRCLECLASS_H_

#include <d3d11.h>
#include <d3dx10math.h>

#include "textureclass.h"
#include "modelclass.h"

// circle class를 model class의 자식으로 둘 것
class ModelCircleClass : public ModelClass
{
protected:
	virtual bool LoadModel() override;
	// final은 마지막을 뜻함, override는 override된 함수임을 뜻함

	//virtual void SetRadius(float r) override;
};

#endif