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

	m_worldPosition = { 0.0f, 0.0f, 0.0f };
    m_worldRotation = { 0.0f, 180.0f, 0.0f };
	m_velocity = { 0.0f, 0.0f, 0.0f };

	m_tag = MODEL_CIRCLE;
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
    

    
    //cout << "A" << endl;
    //system("pause");


    if (model->GetTag() == MODEL_CUBE) 
	{
	    float adv = ((rand() % 100)+50) / 100.0; // 0.5 ~ 1.5
	    float adv2 = (rand()%10+300) / 300.0; // 1.0~1.03
	   // PlaySound(TEXT("./data/hit.wav"), NULL, SND_FILENAME);
	    sndPlaySoundA("./data/hit.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC);

	    cout << model->GetDirection() << " "<<adv<<endl;
	    cout << m_velocity.m_x << " " << m_velocity.m_y << " " << m_velocity.m_z << endl;
	    switch (model->GetDirection())
		{

		case FRONT_BACK:
		    m_velocity.m_z = -m_velocity.m_z*adv2;
			break;
		case LEFT_RIGHT:
			m_velocity.m_x = -m_velocity.m_x*adv;
			break;
		case UP_DOWN:
			m_velocity.m_y = -m_velocity.m_y*adv;
			break;
		default:
		    
			break;
		}
    }
    
	if (model->GetTag() == MODEL_RACKET && InputClass::GetInstance()->GetMouseButton(MOUSE_LEFT) && isFired) 
	{
	    sndPlaySoundA("./data/hit.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC);
		///////////일해라 남창현////////////
		///////////로테이션을 기준으로 노말 구해서 입사, 반사 구현
	    float yy = model->GetWorldRotation().m_y;
	    float xx = model->GetWorldRotation().m_x;
	    cout << "A" << endl;
	    if (rand() % 2) {
		   yy += rand() % 10;
	    }
	    else {
		   yy -= rand() % 10;
	    }
	    if (rand() % 2) {
		   xx += rand() % 10;
	    }
	    else {
		   xx -= rand() % 10;
	    }
	    cout << yy << " " << xx << endl;
		//m_velocity.m_z = 0.3f;
		m_velocity.m_z = -m_velocity.m_z;
		m_velocity.m_x = yy*0.002f;
		m_velocity.m_y = -xx*0.002f;
    }
    //xv = (GetPosition().m_x - model->GetPosition().m_x)*0.4f / 1.0f;

}