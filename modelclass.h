////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"
#include "inputclass.h"
#include "Debug.h"
#include "Component.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////

class ModelClass
{
protected:
	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();
	D3DXMATRIX GetWorldMatrix();

	virtual void Update();
	void SyncMatrix();
	virtual void OnCollisionStay(ModelClass* model);

	const D3DXVECTOR3& GetPosition() const{ return m_worldPosition; }
	const D3DXVECTOR3& GetRotation() const{ return m_worldRotation; }
	const D3DXVECTOR3& GetScale() const{ return m_worldScale; }
	//virtual void SetRadius(float r) = 0;
	//virtual void SetX() = 0;

	const Component& GetComponent(COMPONENT_ID component_id) const;

protected:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	virtual bool LoadModel();
	void ReleaseModel();

protected:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	ModelType* m_model;
	D3DXMATRIX m_worldMatrix;

	// 트리 구조 구현을 위한 부분
	// TODO!!!!!!!!!!!!!!!!!!!!!!!
	ModelClass* m_parent;
	vector<ModelClass*> m_children; 

	// TODO!!!!!!!!!!!!!!!!!!!!!!!!!
	// GameObject class를 만들어 map으로
	// Component들을 넣을 것
	map<COMPONENT_ID, Component> m_components;

	// 이 행렬들을 조작하면 오브젝트의 움직임이 가능하도록 구현함
	D3DXVECTOR3 m_worldPosition;
	D3DXVECTOR3 m_worldScale;
	D3DXVECTOR3 m_worldRotation;
};

#endif