#include "modelcubeclass.h"

bool ModelCubeClass::LoadModel()
{
	m_model = new ModelType[36];
	m_vertexCount = 36;
	m_indexCount = m_vertexCount;

	// ÁÂ»ó´Ü
	m_model[0].x = -1.0f;
	m_model[0].y = 1.0f;
	m_model[0].z = -1.0f;
	m_model[0].tu = 0.0f;
	m_model[0].tv = 0.0f;
	m_model[0].nx = 0.0f;
	m_model[0].ny = 0.0f;
	m_model[0].nz = -1.0f;

	// ¿ì»ó´Ü
	m_model[1].x = 1.0f;
	m_model[1].y = 1.0f;
	m_model[1].z = -1.0f;
	m_model[1].tu = 1.0f;
	m_model[1].tv = 0.0f;
	m_model[1].nx = 0.0f;
	m_model[1].ny = 0.0f;
	m_model[1].nz = -1.0f;

	// ÁÂÇÏ´Ü
	m_model[2].x = -1.0f;
	m_model[2].y = -1.0f;
	m_model[2].z = -1.0f;
	m_model[2].tu = 0.0f;
	m_model[2].tv = 1.0f;
	m_model[2].nx = 0.0f;
	m_model[2].ny = 0.0f;
	m_model[2].nz = -1.0f;

	m_model[3] = m_model[2];
	m_model[4] = m_model[1];

	// ¿ìÇÏ´Ü
	m_model[5].x = 1.0f;
	m_model[5].y = -1.0f;
	m_model[5].z = -1.0f;
	m_model[5].tu = 1.0f;
	m_model[5].tv = 1.0f;
	m_model[5].nx = 0.0f;
	m_model[5].ny = 0.0f;
	m_model[5].nz = -1.0f;

	// ÁÂ»ó´Ü
	m_model[6].x = 1.0f;
	m_model[6].y = 1.0f;
	m_model[6].z = -1.0f;
	m_model[6].tu = 0.0f;
	m_model[6].tv = 0.0f;
	m_model[6].nx = 1.0f;
	m_model[6].ny = 0.0f;
	m_model[6].nz = 0.0f;

	// ¿ì»ó´Ü
	m_model[7].x = 1.0f;
	m_model[7].y = 1.0f;
	m_model[7].z = 1.0f;
	m_model[7].tu = 1.0f;
	m_model[7].tv = 0.0f;
	m_model[7].nx = 1.0f;
	m_model[7].ny = 0.0f;
	m_model[7].nz = 0.0f;

	// ÁÂÇÏ´Ü
	m_model[8].x = 1.0f;
	m_model[8].y = -1.0f;
	m_model[8].z = -1.0f;
	m_model[8].tu = 0.0f;
	m_model[8].tv = 1.0f;
	m_model[8].nx = 1.0f;
	m_model[8].ny = 0.0f;
	m_model[8].nz = 0.0f;

	m_model[9] = m_model[8];
	m_model[10] = m_model[7];

	m_model[11].x = 1.0f;
	m_model[11].y = -1.0f;
	m_model[11].z = 1.0f;
	m_model[11].tu = 1.0f;
	m_model[11].tv = 1.0f;
	m_model[11].nx = 1.0f;
	m_model[11].ny = 0.0f;
	m_model[11].nz = 0.0f;

	m_model[12].x = 1.0f;
	m_model[12].y = 1.0f;
	m_model[12].z = 1.0f;
	m_model[12].tu = 0.0f;
	m_model[12].tv = 0.0f;
	m_model[12].nx = 0.0f;
	m_model[12].ny = 0.0f;
	m_model[12].nz = 1.0f;

	m_model[13].x = -1.0f;
	m_model[13].y = 1.0f;
	m_model[13].z = 1.0f;
	m_model[13].tu = 1.0f;
	m_model[13].tv = 0.0f;
	m_model[13].nx = 0.0f;
	m_model[13].ny = 0.0f;
	m_model[13].nz = 1.0f;

	m_model[14].x = 1.0f;
	m_model[14].y = -1.0f;
	m_model[14].z = 1.0f;
	m_model[14].tu = 0.0f;
	m_model[14].tv = 1.0f; 
	m_model[14].nx = 0.0f;
	m_model[14].ny = 0.0f;
	m_model[14].nz = 1.0f;

	m_model[15] = m_model[14];
	m_model[16] = m_model[13];

	m_model[17].x = -1.0f;
	m_model[17].y = -1.0f;
	m_model[17].z = 1.0f;
	m_model[17].tu = 1.0f;
	m_model[17].tv = 1.0f; 
	m_model[17].nx = 0.0f;
	m_model[17].ny = 0.0f;
	m_model[17].nz = 1.0f;

	m_model[18].x = -1.0f;
	m_model[18].y = 1.0f;
	m_model[18].z = 1.0f;
	m_model[18].tu = 0.0f;
	m_model[18].tv = 0.0f;
	m_model[18].nx = -1.0f;
	m_model[18].ny = 0.0f;
	m_model[18].nz = 0.0f;

	m_model[19].x = -1.0f;
	m_model[19].y = 1.0f;
	m_model[19].z = -1.0f;
	m_model[19].tu = 1.0f;
	m_model[19].tv = 0.0f;
	m_model[19].nx = -1.0f;
	m_model[19].ny = 0.0f;
	m_model[19].nz = 0.0f;

	m_model[20].x = -1.0f;
	m_model[20].y = -1.0f;
	m_model[20].z = 1.0f;
	m_model[20].tu = 0.0f;
	m_model[20].tv = 1.0f;
	m_model[20].nx = -1.0f;
	m_model[20].ny = 0.0f;
	m_model[20].nz = 0.0f;

	m_model[21] = m_model[20];
	m_model[22] = m_model[19];

	m_model[23].x = -1.0f;
	m_model[23].y = -1.0f;
	m_model[23].z = -1.0f;
	m_model[23].tu = 1.0f;
	m_model[23].tv = 1.0f;
	m_model[23].nx = -1.0f;
	m_model[23].ny = 0.0f;
	m_model[23].nz = 0.0f;

	m_model[24].x = -1.0f;
	m_model[24].y = 1.0f;
	m_model[24].z = 1.0f;
	m_model[24].tu = 0.0f;
	m_model[24].tv = 0.0f;
	m_model[24].nx = 0.0f;
	m_model[24].ny = 1.0f;
	m_model[24].nz = 0.0f;

	m_model[25].x = 1.0f;
	m_model[25].y = 1.0f;
	m_model[25].z = 1.0f;
	m_model[25].tu = 1.0f;
	m_model[25].tv = 0.0f;
	m_model[25].nx = 0.0f;
	m_model[25].ny = 1.0f;
	m_model[25].nz = 0.0f;

	m_model[26].x = -1.0f;
	m_model[26].y = 1.0f;
	m_model[26].z = -1.0f;
	m_model[26].tu = 0.0f;
	m_model[26].tv = 1.0f;
	m_model[26].nx = 0.0f;
	m_model[26].ny = 1.0f;
	m_model[26].nz = 0.0f;

	m_model[27] = m_model[26];
	m_model[28] = m_model[25];

	m_model[29].x = 1.0f;
	m_model[29].y = 1.0f;
	m_model[29].z = -1.0f;
	m_model[29].tu = 1.0f;
	m_model[29].tv = 1.0f;
	m_model[29].nx = 0.0f;
	m_model[29].ny = 1.0f;
	m_model[29].nz = 0.0f;

	m_model[30].x = -1.0f;
	m_model[30].y = -1.0f;
	m_model[30].z = -1.0f;
	m_model[30].tu = 0.0f;
	m_model[30].tv = 0.0f;
	m_model[30].nx = 0.0f;
	m_model[30].ny = -1.0f;
	m_model[30].nz = 0.0f;

	m_model[31].x = 1.0f;
	m_model[31].y = -1.0f;
	m_model[31].z = -1.0f;
	m_model[31].tu = 1.0f;
	m_model[31].tv = 0.0f;
	m_model[31].nx = 0.0f;
	m_model[31].ny = -1.0f;
	m_model[31].nz = 0.0f;

	m_model[32].x = -1.0f;
	m_model[32].y = -1.0f;
	m_model[32].z = 1.0f;
	m_model[32].tu = 0.0f;
	m_model[32].tv = 1.0f;
	m_model[32].nx = 0.0f;
	m_model[32].ny = -1.0f;
	m_model[32].nz = 0.0f;

	m_model[33] = m_model[32];
	m_model[34] = m_model[31];

	m_model[35].x = 1.0f;
	m_model[35].y = -1.0f;
	m_model[35].z = 1.0f;
	m_model[35].tu = 1.0f;
	m_model[35].tv = 1.0f;
	m_model[35].nx = 0.0f;
	m_model[35].ny = -1.0f;
	m_model[35].nz = 0.0f;

	return true;
}

void ModelCubeClass::Update()
{
	static float x = 0.0f;
	static float r_x = 0.0f;

	if (InputClass::GetInstance()->IsKeyDown(VK_LEFT))
	{
		m_worldPosition.x = x;
		x -= 0.1f;
	}
	if (InputClass::GetInstance()->IsKeyDown(VK_RIGHT))
	{
		m_worldPosition.x = x;
		x += 0.1f;
	}

	if (InputClass::GetInstance()->IsKeyDown(VK_UP))
	{
		m_worldRotation.x = r_x;
		r_x += 0.1f;
	}

	if (InputClass::GetInstance()->IsKeyDown(VK_DOWN))
	{
		m_worldRotation.x = r_x;
		r_x -= 0.1f;
	}
	//m_worldScale = { 2.0f, 1.0f, 1.0f };
}