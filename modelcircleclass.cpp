#include"modelcircleclass.h"

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
static float z = -5.0f;
static float zv = 0.0f;
static float xv = 0.0f;
static float yv = 0.0f;

void ModelCircleClass::Start()
{
    Collider* col = new Collider(COL_CUBE);
    SetComponent(COM_COLLIDER, col);
    m_worldRotation = { 0.0f, 180.0f, 0.0f };

}

void ModelCircleClass::Update()
{
    static bool isFired = false;

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

    if (InputClass::GetInstance()->IsKeyDown(VK_SPACE) &&
	   !isFired)
    {
	   isFired = true;
	   zv = 0.3f;
    }
    if (InputClass::GetInstance()->isMouseDown(WM_LBUTTONUP) && !isFired) {
	   isFired = true;
	   zv = 0.3f;
	   xv = InputClass::GetInstance()->getdiffX(); //x는 그냥 그대로
	   yv = -InputClass::GetInstance()->getdiffY();

    }
    z += zv;
    x += xv;
    y += yv;
    m_worldPosition = { x, y, z };
}

void ModelCircleClass::OnCollisionStay(ModelClass* model)
{
    zv = -0.3f;

    //xv = (GetPosition().m_x - model->GetPosition().m_x)*0.4f / 1.0f;

}