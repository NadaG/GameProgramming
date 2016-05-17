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

void ModelCircleClass::Start()
{
	Collider* col = new Collider(COL_SPHERE);
	SetComponent(COM_COLLIDER, col);
	// col->SetCenter({ 0.0f, 0.0f, 0.0f });
	// m_worldScale.x += 2.0f;
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

	z += zv;
	x += xv;
	m_worldPosition = { x, y, z };
	m_worldRotation = { 0.0f, 135.0f, 0.0f };
}

void ModelCircleClass::OnCollisionStay(ModelClass* model)
{
	zv = -0.3f;

	xv = (GetPosition().x - model->GetPosition().x)*0.4f / 1.0f;
}