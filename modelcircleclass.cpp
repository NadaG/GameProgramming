#include"modelcircleclass.h"
#include "soundclass.h"
#include "systemclass.h"
#include<mmsystem.h>

#pragma comment (lib,"winmm")


bool ModelCircleClass::LoadModel()
{
    m_vertexCount = m_triNum * 3;
    m_model = new ModelType[m_vertexCount];
    m_indexCount = m_vertexCount;
    m_model_indices = new int[m_indexCount];

    m_mesh.LoadVertices(MESH_CIRCLE, m_model, m_vertexCount, m_model_indices, m_indexCount);
    
    m_tag = MODEL_CIRCLE;
    return true;
}

// TODO!!!!!!!!!!!!!!!!!!!
// 변수 관리 잘할 것
static float x = 0.0f;
static float y = 0.0f;
static float z = -1.0f;
static float zv = 0.0f;
static float xv = 0.0f;
static float yv = 0.0f;

static bool isFired = false;
void ModelCircleClass::Start()
{
    Collider* col = new Collider(COL_CUBE);
    SetComponent(COM_COLLIDER, col);

    m_worldRotation = { 0.0f, 180.0f, 0.0f };
	m_velocity = { 0.0f, 0.0f, 0.0f };
}

void ModelCircleClass::Update()
{


    if (InputClass::GetInstance()->IsKeyDown(VK_LEFT) &&
	   !isFired)
	   x -= 0.05f;

    if (InputClass::GetInstance()->IsKeyDown(VK_RIGHT) &&
	   !isFired)
	   x += 0.05f;

    if (InputClass::GetInstance()->IsKeyDown(VK_UP) &&
	   !isFired)
	   y += 0.05f;

    if (InputClass::GetInstance()->IsKeyDown(VK_DOWN) &&
	   !isFired)
	   y -= 0.05f;

	if (InputClass::GetInstance()->GetMouseButtonDown(MOUSE_LEFT) &&
		!isFired)
	{
		isFired = true;
		m_velocity.m_z = 0.3f;
	}

 //   if (InputClass::GetInstance()->isFirstClick() && !isFired) 
	//{
	//   isFired = true;
	//   zv = 0.3f;
	//   xv = InputClass::GetInstance()->getdiffX(); //x는 그냥 그대로
	//   yv = -InputClass::GetInstance()->getdiffY();
 //   }


	z += m_velocity.m_z;
	x += m_velocity.m_x;
	y += m_velocity.m_y;
    m_worldPosition = { x, y, z };
	m_worldScale = { 1.0f, 1.0f, 1.0f };
}

void ModelCircleClass::OnCollisionStay(ModelClass* model)
{
    PlaySound(TEXT("./data/hit.wav"), NULL, SND_FILENAME);

    
    //cout << "A" << endl;
    //system("pause");


    if (model->GetTag() == MODEL_CUBE) 
	{

    }
    
	if (model->GetTag() == MODEL_RACKET && InputClass::GetInstance()->GetMouseButton(MOUSE_LEFT) && isFired) 
	{
		///////////일해라 남창현////////////
		///////////로테이션을 기준으로 노말 구해서 입사, 반사 구현
	    float yy = model->GetWorldRotation().m_y;
	    float xx = model->GetWorldRotation().m_x;
	    
		m_velocity.m_z = 0.3f;
    }
    //xv = (GetPosition().m_x - model->GetPosition().m_x)*0.4f / 1.0f;

}