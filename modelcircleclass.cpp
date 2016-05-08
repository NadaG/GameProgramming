#include"modelcircleclass.h"

bool ModelCircleClass::LoadModel()
{
	m_model = new ModelType[m_triNum * 3];
	m_vertexCount = m_triNum * 3;
	m_indexCount = m_vertexCount;

	m_mesh.LoadVertices(MESH_SHPERE, m_model, m_triNum * 3);

	return true;
}

// TODO!!!!!!!!!!!!!!!!!!!
// 변수 관리 잘할 것
static float y = -5.0f;
static float yv = 0.0f;
static float xv = 0.0f;

void ModelCircleClass::Start()
{
	Collider* col = new Collider(COL_SPHERE);
	SetComponent(COM_COLLIDER, col);
	// col->SetCenter({ 0.0f, 0.0f, 0.0f });
	// m_worldScale.x += 2.0f;
}

void ModelCircleClass::Update()
{	
	static float x = 0.0f;
	static bool isFired = false;

	if (InputClass::GetInstance()->IsKeyDown(VK_LEFT) &&
		!isFired)
		x -= 0.05f;

	if (InputClass::GetInstance()->IsKeyDown(VK_RIGHT) &&
		!isFired)
		x += 0.05f;

	if (InputClass::GetInstance()->IsKeyDown(VK_SPACE) &&
		!isFired)
	{
		isFired = true;
		yv = 0.3f;
	}

	y += yv;
	x += xv;
	m_worldPosition = { x, y, 10.0f };
	m_worldRotation = { 0.0f, 135.0f, 0.0f };
}

void ModelCircleClass::OnCollisionStay(ModelClass* model)
{
	yv = -0.3f;

	xv = (GetPosition().x - model->GetPosition().x)*0.4f / 1.0f;
}