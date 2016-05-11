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
#include "colliderclass.h"
#include "meshclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////

// ������ ������Ʈ�� ������ ���̵� ��������
class ModelClass
{
protected:
	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};

	int m_id;

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

	// ������ ������Ʈ ���� ���� �����Ǵ� �Լ���
	// ��ũ��Ʈ �κ��� ���⼭ ¥���� �ϸ� �ɰ�!
	virtual void Update();
	void SyncMatrix();
	virtual void OnCollisionStay(ModelClass* model);
	virtual void Start();

	// TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// ���� ���� Ŭ������ ���� �����ϸ� ������ ����
	// D3DXVECTOR3������ �ϱ⿡�� �ͼ����� ���� �κ��� ����
	const D3DXVECTOR3& GetPosition() const{ return m_worldPosition; }
	const D3DXVECTOR3& GetRotation() const{ return m_worldRotation; }
	const D3DXVECTOR3& GetScale() const{ return m_worldScale; }
	//virtual void SetRadius(float r) = 0;
	//virtual void SetX() = 0;

	// ������Ʈ�� ������Ʈ���� �����ϴ� �Լ���
	const Component* GetComponent(COMPONENT_ID component_id) const;
	void SetComponent(COMPONENT_ID component_id, Component* component);
	void DeleteComponent(COMPONENT_ID component_id);
	bool isComponentExist(COMPONENT_ID component_id);

	// �ڽ� ������Ʈ�� �����ϴ� �Լ���
	void AddChild(const ModelClass*);
	ModelClass* GetChild(const int& i) const;
	vector<ModelClass*> GetChildren() const;

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
	int* m_model_indices;
	
	D3DXMATRIX m_worldMatrix;

	// Ʈ�� ���� ������ ���� �κ�
	// TODO!!!!!!!!!!!!!!!!!!!!!!!
	ModelClass* m_parent;
	vector<ModelClass*> m_children; 

	// GameObject class�� ����� map����
	// Component���� ����
	// ���� ��� ����� ������ ���� ��
	map<COMPONENT_ID, Component*> m_components;

	// �� ��ĵ��� �����ϸ� ������Ʈ�� �������� �����ϵ��� ������
	D3DXVECTOR3 m_worldPosition;
	D3DXVECTOR3 m_worldScale;
	D3DXVECTOR3 m_worldRotation;

	Mesh m_mesh;
};

#endif