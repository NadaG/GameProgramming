#include"modelcircleclass.h"

bool ModelCircleClass::LoadModel()
{
	m_model = new ModelType[3];
	m_vertexCount = 3;
	m_indexCount = 3;

	m_model[0].x = -1.0f;
	m_model[0].y = 1.0f;
	m_model[0].z = 1.0f;
	m_model[0].tu = 0.0f;
	m_model[0].tv = 0.0f;
	m_model[0].nx = 0.0f;
	m_model[0].ny = 0.0f;
	m_model[0].nz = -1.0f;

	m_model[1].x = 1.0f;
	m_model[1].y = 1.0f;
	m_model[1].z = 1.0f;
	m_model[1].tu = 1.0f;
	m_model[1].tv = 0.0f;
	m_model[1].nx = 0.0f;
	m_model[1].ny = 0.0f;
	m_model[1].nz = -1.0f;

	m_model[2].x = -1.0f;
	m_model[2].y = -1.0f;
	m_model[2].z = 1.0f;
	m_model[2].tu = 0.0f;
	m_model[2].tv = 1.0f;
	m_model[2].nx = 0.0f;
	m_model[2].ny = 0.0f;
	m_model[2].nz = -1.0f;

	return true;
}
//
//void ModelCircleClass::SetRadius(float r)
//{
//
//}