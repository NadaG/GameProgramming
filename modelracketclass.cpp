#include "modelracketclass.h"
#include<iostream>
bool ModelRacketClass::LoadModel()
{
    m_vertexCount = 36;
    m_model = new ModelType[m_vertexCount];
    m_indexCount = m_vertexCount;
    m_model_indices = new int[m_indexCount];

    m_mesh.LoadVertices(MESH_CUBE, m_model, m_vertexCount, m_model_indices, m_indexCount);

    return true;
}

void ModelRacketClass::Start()
{
    Collider* col = new Collider(COL_CUBE);
    SetComponent(COM_COLLIDER, col);
    //m_worldPosition = {0.0f,1.0f,1.0f};
    m_worldScale = {1.0f,1.0f,0.01f};
}

void ModelRacketClass::Update()
{

	float x = InputClass::GetInstance()->GetMousePos().m_x;
	float y = InputClass::GetInstance()->GetMousePos().m_y;
    y /= 64.0f;
    x /= 64.0f;
    //cout << x << " " << y << endl;
    m_worldPosition = { x, -y, -1.5f };

	if (InputClass::GetInstance()->GetMouseButtonDown(MOUSE_LEFT))
		Debug::GetInstance()->Log("QQWER");

	if (InputClass::GetInstance()->GetMouseButton(MOUSE_LEFT))
		Debug::GetInstance()->Log("CCCC");

	if (InputClass::GetInstance()->GetMouseButtonUp(MOUSE_LEFT))
		Debug::GetInstance()->Log("ZZZZ");

	if (InputClass::GetInstance()->GetMouseButton(MOUSE_LEFT))
	{
	   m_worldRotation = {0.0f,-50.0f,10.0f};
    }

	if (!InputClass::GetInstance()->GetMouseButton(MOUSE_LEFT))
	{
	   m_worldRotation = { 0.0f,0.0f,0.0f };
    }
 
    //m_worldPosition = { 0.0f, 5.0f, 10.0f };
}

void ModelRacketClass::OnCollisionStay(ModelClass* model)
{
  
    
}
int ModelRacketClass::gettype() {
    return MODEL_RACKET;
}