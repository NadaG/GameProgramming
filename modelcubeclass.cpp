#include "modelcubeclass.h"

bool ModelCubeClass::LoadModel()
{
	m_vertexCount = 36;
	m_model = new ModelType[m_vertexCount];
	m_indexCount = m_vertexCount;
	m_model_indices = new int[m_indexCount];

	m_mesh.LoadVertices(MESH_CUBE, m_model, m_model_indices);

	return true;
}

void ModelCubeClass::Start()
{
	Collider* col = new Collider(COL_CUBE);
	SetComponent(COM_COLLIDER, col);

	m_tag = MODEL_CUBE;
}

void ModelCubeClass::Update()
{
	//m_worldPosition = { 0.0f, 5.0f, 10.0f };
	//m_worldScale = { 500.0f, 500.0f, 1.0f };
}

void ModelCubeClass::OnCollisionStay(ModelClass* model)
{
	if (model->GetTag() == MODEL_CIRCLE)
	{
		//model->SetVelocity({ model->GetVelocity().m_x, model->GetVelocity().m_y, -model->GetVelocity().m_z });
	}
}

