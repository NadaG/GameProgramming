#include "modelcubeclass.h"

bool ModelCubeClass::LoadModel()
{
	m_model = new ModelType[36];
	m_vertexCount = 36;
	m_indexCount = m_vertexCount;

	m_mesh.LoadVertices(MESH_CUBE, m_model, 36);

	return true;
}

void ModelCubeClass::Start()
{
	Collider* col = new Collider(COL_CUBE);
	SetComponent(COM_COLLIDER, col);
}

void ModelCubeClass::Update()
{
	m_worldPosition = { 0.0f, 5.0f, 10.0f };
}

void ModelCubeClass::OnCollisionStay(ModelClass* model)
{
}