#include "modelracketclass.h"
#include "systemclass.h"
#include<iostream>

bool ModelRacketClass::LoadModel()
{
    m_vertexCount = 36;
    m_model = new ModelType[m_vertexCount];
    m_indexCount = m_vertexCount;
    m_model_indices = new int[m_indexCount];

    m_mesh.LoadVertices(MESH_CUBE, m_model, m_model_indices);

    return true;
}

void ModelRacketClass::Start()
{
    Collider* col = new Collider(COL_CUBE);
    SetComponent(COM_COLLIDER, col);
    //m_worldPosition = {0.0f,1.0f,1.0f};
    m_worldScale = {1.0f,1.0f,0.2f};
	m_worldRotation = { 0.0f, 0.0f, 0.0f };

	m_tag = MODEL_RACKET;
}

void ModelRacketClass::Update()
{
    float x = InputClass::GetInstance()->GetMousePos().m_x;
    float y = InputClass::GetInstance()->GetMousePos().m_y;
    float w = GetSystemMetrics(SM_CXSCREEN);
    float h = GetSystemMetrics(SM_CYSCREEN);
    x -= w / 2;
    y -= h / 2;
    y /= 64.0f;
    x /= 64.0f;

    //cout << x << " " << y << endl;
	if (x > 4.0f)
		x = 4.0f;
	if (x < -4.0f)
		x = -4.0f;
	if (y>4.0f)
		y = 4.0f;
	if (y < -4.0f)
		y = -4.0f;
	
	m_worldPosition = { x, -y, -1.5f + (-100)*(GraphicsClass::GetInstance()->s_StageNum-1) };
    int flag = 0;
    
    if (InputClass::GetInstance()->IsKeyDown(97))//1 
    {
	   m_worldRotation = { -20.0f, 20.0f, 0.0f };
    }
    else if (InputClass::GetInstance()->IsKeyDown(98))//2 
    {
	   m_worldRotation = { -20.0f, 0.0f, 0.0f };
    }
    else if (InputClass::GetInstance()->IsKeyDown(99))//3
    {
	   m_worldRotation = { -20.0f, -20.0f, 0.0f };
    }
    else if (InputClass::GetInstance()->IsKeyDown(100))//4
    {
	   m_worldRotation = { 1.0f, 20.0f, 0.0f };
    }
    else if (InputClass::GetInstance()->IsKeyDown(101))//5
    {
	   m_worldRotation = { 0.0f, 0.0f, 0.0f };
    }
    else if (InputClass::GetInstance()->IsKeyDown(102))//6
    {
	   m_worldRotation = { 1.0f, -20.0f, 0.0f };
    }
    else if (InputClass::GetInstance()->IsKeyDown(103))//7 
    {
	   m_worldRotation = { 20.0f, 20.0f, 0.0f };
    }
    else if (InputClass::GetInstance()->IsKeyDown(104))//8
    {
	   m_worldRotation = { 20.0f, 0.0f, 0.0f };
    }
    else if (InputClass::GetInstance()->IsKeyDown(105))//9
    {
	   m_worldRotation = { 20.0f, -20.0f, 0.0f };
    }
    else //아무것도 없쪙
    {
	   m_worldRotation = { 0.0f, 0.0f, 0.0f };
    }
    float yy = GetWorldRotation().m_y;
    float xx = GetWorldRotation().m_x;
    //cout << yy << " " << xx << endl;
	/*if (InputClass::GetInstance()->GetMouseButton(MOUSE_LEFT))
		m_worldRotation = { 20.0f, 0.0f, 0.0f };
	else
		m_worldRotation = { 0.0f, 0.0f, 0.0f };
 */
	
    //m_worldPosition = { 0.0f, 5.0f, 10.0f };
}

void ModelRacketClass::OnCollisionEnter(ModelClass* model)
{

}

void ModelRacketClass::OnCollisionExit(ModelClass* model)
{

}

void ModelRacketClass::OnCollisionStay(ModelClass* model)
{
}
