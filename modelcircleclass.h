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

public:
	ModelCircleClass()
		:m_r(1.0f), m_triNum(10)
	{
	}

	virtual void Update() override;
	virtual void OnCollisionEnter(ModelClass* model) override;
	virtual void OnCollisionStay(ModelClass* model) override;
	virtual void OnCollisionExit(ModelClass* model) override;
	virtual void Start() override;

	void WorldPositionInitialize();

	const float& GetR_X() const{ return m_r*m_worldScale.m_x; }
	const float& GetR_Y() const{ return m_r*m_worldScale.m_y; }

private:
	float m_r;
	int m_triNum;
};

#endif