#define _CRT_SECURE_NO_WARNINGS
#include"modelcircleclass.h"
#include "soundclass.h"
#include "systemclass.h"
#include<mmsystem.h>

#pragma comment (lib,"winmm")


bool ModelCircleClass::LoadModel()
{
	m_vertexCount = 12288;
	m_model = new ModelType[m_vertexCount];
	m_indexCount = m_vertexCount * 2;
	m_model_indices = new int[m_indexCount];

	m_mesh.LoadVertices(MESH_SHPERE, m_model, m_model_indices);

	return true;
}

// TODO!!!!!!!!!!!!!!!!!!!
// 변수 관리 잘할 것
static float x = 0.0f;
static float y = 0.0f;
static float z = 5.0f;
static float zv = 0.0f;
static float xv = 0.0f;
static float yv = 0.0f;
int am = 0;
int stage = 0;
float bz = (stage)*100.0f;
static bool isFired = false;
void cheat() {
    stage++;

    GraphicsClass::GetInstance()->s_StageNum++;
    GraphicsClass::GetInstance()->ToNextStage(GraphicsClass::GetInstance()->s_StageNum);
    HWND hWnd = FindWindow(NULL, TEXT("Engine"));
    string s = "./data/";
    s += to_string(stage);
    s += ".wav";
    const char* cp = s.c_str();
    SoundClass::GetInstance()->Shutdown();
    SoundClass::GetInstance()->Initialize(hWnd, cp);
}

void ModelCircleClass::Start()
{
	Collider* col = new Collider(COL_CUBE);
	SetComponent(COM_COLLIDER, col);

	m_worldRotation = { 0.0f, 0.0f, 0.0f };
	m_velocity = { 0.0f, 0.0f, 0.0f };
	m_worldPosition = { 0.0f, 0.0f, 0.0f };

	m_tag = MODEL_SPHERE;
	isFired = false;

	x = 0.0f;
	y = 0.0f;
	z = 5.0f;
}

void ModelCircleClass::WorldPositionInitialize()
{
    x = 0.0f;
    y = 0.0f;
    z = 5.0f + ((-100) * (GraphicsClass::GetInstance()->s_StageNum - 1));
    m_worldRotation = { 0.0f, 0.0f, 0.0f };
    m_velocity = { 0.0f, 0.0f, 0.0f };
}

void ModelCircleClass::Update()
{
    bz = (stage)*100.0f;
    if (GetWorldPosition().m_z<-8.0f-bz) {
	   HWND hWnd = FindWindow(NULL, TEXT("Engine"));
	   char q[200] = { 0, };

	   sprintf(q, "Game Over.\nScore : %d", myscore);
	   wchar_t wtext[200];
	   mbstowcs(wtext, q, strlen(q) + 1);//Plus null
	   LPWSTR query = wtext;

	   MessageBox(hWnd, query, TEXT("게임 종료"), MB_OK);
	   exit(1);
    }

    if (InputClass::GetInstance()->IsKeyDown(VK_LEFT) &&
	   !isFired) {
	   x -= 0.05f;
    }

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
		//z = 5.0f + ((-100) * (GraphicsClass::GetInstance()->s_StageNum - 1));
		m_velocity.m_z = -0.2f;
		m_velocity.m_z -= (stage*0.075f);
	}	
	if (InputClass::GetInstance()->GetMouseButtonDown(MOUSE_RIGHT) &&am<=1) {
	    am++;
	    cout << "ASDASD" << endl;
	    cheat();
	}

	Debug::GetInstance()->Log(m_worldPosition);
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

int collflag = 0;
int stagestart = 1;
DWORD beforetime = 0;
int endcount[3] = {4,9,16};
void calctime() {
	//cout << "A" << endl;
	DWORD currtime = GetTickCount();
	if (collflag == 0) { collflag = 1; }
	if (collflag == 1) {
		DWORD sub = currtime - beforetime;
		if (sub < 20) { 
		    return; }
		else {
			collflag = 0;
			beforetime = currtime;
		}
	}
}


void ModelCircleClass::OnCollisionEnter(ModelClass* model)
{
    stagestart = 1;
    float adv = ((rand() % 100) + 50) / 100.0; // 0.5 ~ 1.5
    float adv2 = (rand() % 10 + 300) / 300.0; // 1.0~1.03

    float Pyx;
    float Pyy;
    float Pyz;

    bz = (stage)*100.0f;
    calctime();
    if (collflag == 1) { return; }

    if (model->GetTag() == MODEL_CUBE) {

	   cout << "DIR : "<<" "<<model->GetDirection() << endl;

	   sndPlaySoundA("./data/hit.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC);
	   switch (model->GetDirection()) {
	   case FRONT_BACK:
		  //m_velocity.m_z = -abs(m_velocity.m_z)*adv2;
		  m_velocity.m_z = -abs(m_velocity.m_z);
		 // if (model->GetWorldPosition().m_z> 9.0f-bz && model->GetWorldPosition().m_z<11.0f-bz) {
		  if(!model->backwall){
		  model->HP--;
			 if (model->HP <= 0) {
				model->SetWorldScale({ 0.0f, 0.0f, 0.0f });
				GraphicsClass::GetInstance()->Destroy(model);
			
				myscore += 100;
				endcount[stage]--;
				if (endcount[stage] <= 0) {
				    if (stage == 2) {
				    
					   HWND hWnd = FindWindow(NULL, TEXT("Engine"));
					   char q[200] = { 0, };

					   sprintf(q, "Game Clear.\ncongratulations!\nScore : %d", myscore);
					   wchar_t wtext[200];
					   mbstowcs(wtext, q, strlen(q) + 1);//Plus null
					   LPWSTR query = wtext;

					   MessageBox(hWnd, query, TEXT("게임 클리어"), MB_OK);
					   exit(1);
				    }

				    ////////////////////////
				    stagestart = 0;
				    //cout << "ABCDE" << endl;
				    stage++;
				    collflag = 0;
				    beforetime = 0;
				    
				    GraphicsClass::GetInstance()->s_StageNum++;
				    GraphicsClass::GetInstance()->ToNextStage(GraphicsClass::GetInstance()->s_StageNum);
				    HWND hWnd = FindWindow(NULL, TEXT("Engine"));
				    string s = "./data/";
				    s += to_string(stage);
				    s += ".wav";
				    const char* cp = s.c_str();
				    SoundClass::GetInstance()->Shutdown();
				    SoundClass::GetInstance()->Initialize(hWnd, cp);
				}
			 }
			 else {
				myscore += 10;
			 }
		  }
		  else {
			 HWND hWnd = FindWindow(NULL, TEXT("Engine"));
			 char q[200] = { 0, };

			 sprintf(q, "Game Over.\nScore : %d", myscore);
			 wchar_t wtext[200];
			 mbstowcs(wtext, q, strlen(q) + 1);//Plus null
			 LPWSTR query = wtext;

			 MessageBox(hWnd, query, TEXT("게임 종료"), MB_OK);
			 exit(1);
		  }
		  break;

	   case LEFT_RIGHT:
		  if (m_velocity.m_x < 0) {
			 m_velocity.m_x = abs(m_velocity.m_x);
		  }
		  else {
			 m_velocity.m_x = -abs(m_velocity.m_x);
		  }
		  myscore++;
		  break;

	   case UP_DOWN:
		  if (m_velocity.m_y < 0) {
			 m_velocity.m_y = abs(m_velocity.m_y);
		  }
		  else {
			 m_velocity.m_y = -abs(m_velocity.m_y);
		  }
		  myscore++;
		  break;

	   default:
		  break;
	   }

    }

	

	if (model->GetTag() == MODEL_RACKET &&  isFired)
	{
	    stagestart = 1;
	    cout << "RACKET" << endl;
		sndPlaySoundA("./data/hit.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC);
		///////////일해라 남창현////////////
		///////////로테이션을 기준으로 노말 구해서 입사, 반사 구현
		float yy = model->GetWorldRotation().m_y;
		float xx = model->GetWorldRotation().m_x;
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

		m_velocity.m_z = abs(m_velocity.m_z);
		m_velocity.m_x = yy*0.003f;
		m_velocity.m_y = -xx*0.003f;
	}
}

void ModelCircleClass::OnCollisionStay(ModelClass* model)
{
    /*
    if (stagestart == 0) { return; }
    cout << "STAY" << endl;
    collflag = 0;
    float adv = ((rand() % 100) + 50) / 100.0; // 0.5 ~ 1.5
    float adv2 = (rand() % 10 + 300) / 300.0; // 1.0~1.03
    float x = GetWorldPosition().m_x;
    float y = GetWorldPosition().m_y;
    float z = GetWorldPosition().m_z;
    switch (model->GetDirection()) {
    case FRONT_BACK: 
	   SetWorldPosition({ x,y,z-0.0f });
	   m_velocity.m_z = -m_velocity.m_z*adv2;
    case LEFT_RIGHT:
	   if (m_velocity.m_x < 0) {
		  SetWorldPosition({x+0.0f,y,z});
	   }
	   else {
		  SetWorldPosition({ x - 0.0f,y,z });
	   }

	   m_velocity.m_x = -m_velocity.m_x*adv;
	   myscore++;
	   break;

    case UP_DOWN:
	   if (m_velocity.m_y < 0) {
		  SetWorldPosition({ x,y+0.0f,z });
	   }
	   else {
		  SetWorldPosition({ x,y-0.0f,z });
	   }

	   m_velocity.m_y = -m_velocity.m_y*adv;
	   myscore++;
	   break;

    }*/
}

void ModelCircleClass::OnCollisionExit(ModelClass* model)
{
}