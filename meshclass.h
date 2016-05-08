////////////////////////////////////////////////////////////////////////////////
// Filename: meshclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MESHCLASS_H_
#define _MESHCLASS_H_

#include "d3dclass.h"

enum MESH_TYPE
{
	MESH_NONE = 0,
	MESH_CUBE = 1,
	MESH_SHPERE = 2
};

struct ModelType
{
	float x, y, z;
	float tu, tv;
	float nx, ny, nz;
};

class Mesh
{
public:
	Mesh();
	Mesh(const Mesh&);
	~Mesh();

	void LoadVertices(const MESH_TYPE& mesh_type, ModelType* vertices, const int& v_n);

private:

};

#endif