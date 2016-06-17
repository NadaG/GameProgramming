#include "modelsphereclass.h"

bool ModelSphereClass::LoadModel()
{
	m_vertexCount = 12288;
	m_model = new ModelType[m_vertexCount];
	m_indexCount = m_vertexCount * 2;
	m_model_indices = new int[m_indexCount];

	m_mesh.LoadVertices(MESH_SHPERE, m_model, m_model_indices);

	return true;
}

void ModelSphereClass::Start()
{
	Collider* col = new Collider(COL_SPHERE);
	SetComponent(COM_COLLIDER, col);

	m_tag = MODEL_SPHERE;
}

static float y = 0.0f;
void ModelSphereClass::Update()
{
	//m_worldPosition = { 0.0f, 5.0f, 10.0f };
	//m_worldScale = { 3.0f, 3.0f, 3.0f };
	m_worldRotation = { 0.0f, y, 0.0f };
}

void ModelSphereClass::OnCollisionStay(ModelClass* model)
{
}