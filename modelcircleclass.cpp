#include"modelcircleclass.h"

bool ModelCircleClass::LoadModel()
{
	m_model = new ModelType[m_triNum * 3];
	m_vertexCount = m_triNum * 3;
	m_indexCount = m_vertexCount;

	float per_radian = 2 * 3.141592 / m_triNum;
	float now_radian = 0;
	for (int i = 0; i < m_triNum * 3; i += 3)
	{
		m_model[i].x = 0.0f;
		m_model[i].y = 0.0f;
		m_model[i].z = 0.0f;
		m_model[i].tu = 0.0f;
		m_model[i].tv = 1.0f;
		m_model[i].nx = 0.0f;
		m_model[i].ny = 0.0f;
		m_model[i].nz = -1.0f;

		m_model[i + 1].x = m_r*cosf(now_radian);
		m_model[i + 1].y = m_r*sinf(now_radian);
		m_model[i + 1].z = 0.0f;
		m_model[i + 1].tu = 0.0f;
		m_model[i + 1].tv = 0.0f;
		m_model[i + 1].nx = 0.0f;
		m_model[i + 1].ny = 0.0f;
		m_model[i + 1].nz = -1.0f;

		m_model[i + 2].x = m_r*cosf(now_radian + per_radian);
		m_model[i + 2].y = m_r*sinf(now_radian + per_radian);
		m_model[i + 2].z = 0.0f;
		m_model[i + 2].tu = 1.0f;
		m_model[i + 2].tv = 0.0f;
		m_model[i + 2].nx = 0.0f;
		m_model[i + 2].ny = 0.0f;
		m_model[i + 2].nz = -1.0f;

		now_radian += per_radian;
	}

	return true;
}

// TODO!!!!!!!!!!!!!!!!!!!
// 변수 관리 잘할 것
static float y = -5.0f;
static float yv = 0.0f;
static float xv = 0.0f;

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