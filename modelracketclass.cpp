#include "modelracketclass.h"
#include<iostream>
float x = 2.0f;
float y = 2.0f;
float z = 2.0f;
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
   // Collider* col = new Collider(COL_CUBE);
    //SetComponent(COM_COLLIDER, col);
    //m_worldPosition = {0.0f,1.0f,1.0f};
}

void ModelRacketClass::Update()
{

    float y = InputClass::GetInstance()->getMouseY(WM_MOUSEMOVE);
    float x = InputClass::GetInstance()->getMouseX(WM_MOUSEMOVE);
    y /= 64.0f;
    x /= 64.0f;
    cout << x << " " << y << endl;
    m_worldPosition = { x, -y, 0.0f };
    //m_worldPosition = { 0.0f, 5.0f, 10.0f };
}

void ModelRacketClass::OnCollisionStay(ModelClass* model)
{
  
    
}