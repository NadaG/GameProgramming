#ifndef _MODELRACKETCLASS_H_
#define _MODELRACKETCLASS_H_

#include<D3DX11.h>
#include<D3DX10math.h>

#include"textureclass.h"
#include"modelclass.h"

class ModelRacketClass : public ModelClass
{
protected:
    virtual bool LoadModel() override;
    //virtual void SetX() override;

public:

    ModelRacketClass()
    {
    }

    virtual void Update() override;
	virtual void OnCollisionEnter(ModelClass* model) override;
    virtual void OnCollisionStay(ModelClass* model) override;
	virtual void OnCollisionExit(ModelClass* model) override;
    virtual void Start() override;

    const float& GetX() const { return m_worldScale.m_x; }
    const float& GetY() const { return m_worldScale.m_y; }
    const float& GetZ() const { return m_worldScale.m_z; }


private:
};

#endif