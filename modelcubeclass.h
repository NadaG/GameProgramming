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
};

#endif