#include "meshclass.h"

Mesh::Mesh()
{
}

Mesh::Mesh(const Mesh& mesh)
{
}

Mesh::~Mesh()
{
}

void Mesh::LoadVertices(const MESH_TYPE& mesh_type, ModelType* vertices, const int& v_n)
{
	float now_radian, per_radian;

	switch (mesh_type)
	{
	case MESH_NONE:
		break;
	case MESH_CUBE:

		// ÁÂ»ó´Ü
		vertices[0].x = -1.0f;
		vertices[0].y = 1.0f;
		vertices[0].z = -1.0f;
		vertices[0].tu = 0.0f;
		vertices[0].tv = 0.0f;
		vertices[0].nx = 0.0f;
		vertices[0].ny = 0.0f;
		vertices[0].nz = -1.0f;

		// ¿ì»ó´Ü
		vertices[1].x = 1.0f;
		vertices[1].y = 1.0f;
		vertices[1].z = -1.0f;
		vertices[1].tu = 1.0f;
		vertices[1].tv = 0.0f;
		vertices[1].nx = 0.0f;
		vertices[1].ny = 0.0f;
		vertices[1].nz = -1.0f;

		// ÁÂÇÏ´Ü
		vertices[2].x = -1.0f;
		vertices[2].y = -1.0f;
		vertices[2].z = -1.0f;
		vertices[2].tu = 0.0f;
		vertices[2].tv = 1.0f;
		vertices[2].nx = 0.0f;
		vertices[2].ny = 0.0f;
		vertices[2].nz = -1.0f;

		vertices[3] = vertices[2];
		vertices[4] = vertices[1];

		// ¿ìÇÏ´Ü
		vertices[5].x = 1.0f;
		vertices[5].y = -1.0f;
		vertices[5].z = -1.0f;
		vertices[5].tu = 1.0f;
		vertices[5].tv = 1.0f;
		vertices[5].nx = 0.0f;
		vertices[5].ny = 0.0f;
		vertices[5].nz = -1.0f;

		// ÁÂ»ó´Ü
		vertices[6].x = 1.0f;
		vertices[6].y = 1.0f;
		vertices[6].z = -1.0f;
		vertices[6].tu = 0.0f;
		vertices[6].tv = 0.0f;
		vertices[6].nx = 1.0f;
		vertices[6].ny = 0.0f;
		vertices[6].nz = 0.0f;

		// ¿ì»ó´Ü
		vertices[7].x = 1.0f;
		vertices[7].y = 1.0f;
		vertices[7].z = 1.0f;
		vertices[7].tu = 1.0f;
		vertices[7].tv = 0.0f;
		vertices[7].nx = 1.0f;
		vertices[7].ny = 0.0f;
		vertices[7].nz = 0.0f;

		// ÁÂÇÏ´Ü
		vertices[8].x = 1.0f;
		vertices[8].y = -1.0f;
		vertices[8].z = -1.0f;
		vertices[8].tu = 0.0f;
		vertices[8].tv = 1.0f;
		vertices[8].nx = 1.0f;
		vertices[8].ny = 0.0f;
		vertices[8].nz = 0.0f;

		vertices[9] = vertices[8];
		vertices[10] = vertices[7];

		vertices[11].x = 1.0f;
		vertices[11].y = -1.0f;
		vertices[11].z = 1.0f;
		vertices[11].tu = 1.0f;
		vertices[11].tv = 1.0f;
		vertices[11].nx = 1.0f;
		vertices[11].ny = 0.0f;
		vertices[11].nz = 0.0f;

		vertices[12].x = 1.0f;
		vertices[12].y = 1.0f;
		vertices[12].z = 1.0f;
		vertices[12].tu = 0.0f;
		vertices[12].tv = 0.0f;
		vertices[12].nx = 0.0f;
		vertices[12].ny = 0.0f;
		vertices[12].nz = 1.0f;

		vertices[13].x = -1.0f;
		vertices[13].y = 1.0f;
		vertices[13].z = 1.0f;
		vertices[13].tu = 1.0f;
		vertices[13].tv = 0.0f;
		vertices[13].nx = 0.0f;
		vertices[13].ny = 0.0f;
		vertices[13].nz = 1.0f;

		vertices[14].x = 1.0f;
		vertices[14].y = -1.0f;
		vertices[14].z = 1.0f;
		vertices[14].tu = 0.0f;
		vertices[14].tv = 1.0f;
		vertices[14].nx = 0.0f;
		vertices[14].ny = 0.0f;
		vertices[14].nz = 1.0f;

		vertices[15] = vertices[14];
		vertices[16] = vertices[13];

		vertices[17].x = -1.0f;
		vertices[17].y = -1.0f;
		vertices[17].z = 1.0f;
		vertices[17].tu = 1.0f;
		vertices[17].tv = 1.0f;
		vertices[17].nx = 0.0f;
		vertices[17].ny = 0.0f;
		vertices[17].nz = 1.0f;

		vertices[18].x = -1.0f;
		vertices[18].y = 1.0f;
		vertices[18].z = 1.0f;
		vertices[18].tu = 0.0f;
		vertices[18].tv = 0.0f;
		vertices[18].nx = -1.0f;
		vertices[18].ny = 0.0f;
		vertices[18].nz = 0.0f;

		vertices[19].x = -1.0f;
		vertices[19].y = 1.0f;
		vertices[19].z = -1.0f;
		vertices[19].tu = 1.0f;
		vertices[19].tv = 0.0f;
		vertices[19].nx = -1.0f;
		vertices[19].ny = 0.0f;
		vertices[19].nz = 0.0f;

		vertices[20].x = -1.0f;
		vertices[20].y = -1.0f;
		vertices[20].z = 1.0f;
		vertices[20].tu = 0.0f;
		vertices[20].tv = 1.0f;
		vertices[20].nx = -1.0f;
		vertices[20].ny = 0.0f;
		vertices[20].nz = 0.0f;

		vertices[21] = vertices[20];
		vertices[22] = vertices[19];

		vertices[23].x = -1.0f;
		vertices[23].y = -1.0f;
		vertices[23].z = -1.0f;
		vertices[23].tu = 1.0f;
		vertices[23].tv = 1.0f;
		vertices[23].nx = -1.0f;
		vertices[23].ny = 0.0f;
		vertices[23].nz = 0.0f;

		vertices[24].x = -1.0f;
		vertices[24].y = 1.0f;
		vertices[24].z = 1.0f;
		vertices[24].tu = 0.0f;
		vertices[24].tv = 0.0f;
		vertices[24].nx = 0.0f;
		vertices[24].ny = 1.0f;
		vertices[24].nz = 0.0f;

		vertices[25].x = 1.0f;
		vertices[25].y = 1.0f;
		vertices[25].z = 1.0f;
		vertices[25].tu = 1.0f;
		vertices[25].tv = 0.0f;
		vertices[25].nx = 0.0f;
		vertices[25].ny = 1.0f;
		vertices[25].nz = 0.0f;

		vertices[26].x = -1.0f;
		vertices[26].y = 1.0f;
		vertices[26].z = -1.0f;
		vertices[26].tu = 0.0f;
		vertices[26].tv = 1.0f;
		vertices[26].nx = 0.0f;
		vertices[26].ny = 1.0f;
		vertices[26].nz = 0.0f;

		vertices[27] = vertices[26];
		vertices[28] = vertices[25];

		vertices[29].x = 1.0f;
		vertices[29].y = 1.0f;
		vertices[29].z = -1.0f;
		vertices[29].tu = 1.0f;
		vertices[29].tv = 1.0f;
		vertices[29].nx = 0.0f;
		vertices[29].ny = 1.0f;
		vertices[29].nz = 0.0f;

		vertices[30].x = -1.0f;
		vertices[30].y = -1.0f;
		vertices[30].z = -1.0f;
		vertices[30].tu = 0.0f;
		vertices[30].tv = 0.0f;
		vertices[30].nx = 0.0f;
		vertices[30].ny = -1.0f;
		vertices[30].nz = 0.0f;

		vertices[31].x = 1.0f;
		vertices[31].y = -1.0f;
		vertices[31].z = -1.0f;
		vertices[31].tu = 1.0f;
		vertices[31].tv = 0.0f;
		vertices[31].nx = 0.0f;
		vertices[31].ny = -1.0f;
		vertices[31].nz = 0.0f;

		vertices[32].x = -1.0f;
		vertices[32].y = -1.0f;
		vertices[32].z = 1.0f;
		vertices[32].tu = 0.0f;
		vertices[32].tv = 1.0f;
		vertices[32].nx = 0.0f;
		vertices[32].ny = -1.0f;
		vertices[32].nz = 0.0f;

		vertices[33] = vertices[32];
		vertices[34] = vertices[31];

		vertices[35].x = 1.0f;
		vertices[35].y = -1.0f;
		vertices[35].z = 1.0f;
		vertices[35].tu = 1.0f;
		vertices[35].tv = 1.0f;
		vertices[35].nx = 0.0f;
		vertices[35].ny = -1.0f;
		vertices[35].nz = 0.0f;
		break;
	case MESH_SHPERE:

		per_radian = 2 * 3.141592 / (v_n / 3);
		now_radian = 0;
		for (int i = 0; i < v_n; i += 3)
		{
			vertices[i].x = 0.0f;
			vertices[i].y = 0.0f;
			vertices[i].z = 0.0f;
			vertices[i].tu = 0.0f;
			vertices[i].tv = 1.0f;
			vertices[i].nx = 0.0f;
			vertices[i].ny = 0.0f;
			vertices[i].nz = -1.0f;

			vertices[i + 1].x = cosf(now_radian);
			vertices[i + 1].y = sinf(now_radian);
			vertices[i + 1].z = 0.0f;
			vertices[i + 1].tu = 0.0f;
			vertices[i + 1].tv = 0.0f;
			vertices[i + 1].nx = 0.0f;
			vertices[i + 1].ny = 0.0f;
			vertices[i + 1].nz = -1.0f;

			vertices[i + 2].x = cosf(now_radian + per_radian);
			vertices[i + 2].y = sinf(now_radian + per_radian);
			vertices[i + 2].z = 0.0f;
			vertices[i + 2].tu = 1.0f;
			vertices[i + 2].tv = 0.0f;
			vertices[i + 2].nx = 0.0f;
			vertices[i + 2].ny = 0.0f;
			vertices[i + 2].nz = -1.0f;

			now_radian += per_radian;
		}

		break;
	default:
		break;
	}

}