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
#include "debug.h"
#include "component.h"
#include "colliderclass.h"
#include "meshclass.h"
#include "mymath.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////

// ������ ������Ʈ�� ������ ���̵� ��������

enum MODEL_TYPE
{
    MODEL_NONE=0,
    MODEL_CIRCLE=1,
    MODEL_CUBE=2,
    MODEL_RACKET=3
};


class ModelClass
{
protected:
	struct VertexType
	{
		Vector3f position;
		Vector2f texture;
		Vector3f normal;
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
	void SyncMatrix();

	virtual void Update();
	virtual void OnCollisionStay(ModelClass* model);
	virtual void Start();
	virtual int gettype();
	// TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// ���� ���� Ŭ������ ���� �����ϸ� ������ ����
	// D3DXVECTOR3������ �ϱ⿡�� �ͼ����� ���� �κ��� ����
	const Vector3f& GetPosition() const{ return m_worldPosition; }
	const Vector3f& GetRotation() const{ return m_worldRotation; }
	const Vector3f& GetScale() const{ return m_worldScale; }
	
	void SetPosition(const Vector3f& position){ m_worldPosition = position; }
	void SetRotation(const Vector3f& rotation){ m_worldRotation = rotation; }
	void SetScale(const Vector3f& scale){ m_worldScale = scale; }

	// ������Ʈ�� ������Ʈ���� �����ϴ� �Լ���
	const Component* GetComponent(COMPONENT_ID component_id) const;
	void SetComponent(COMPONENT_ID component_id, Component* component);
	void DeleteComponent(COMPONENT_ID component_id);
	bool isComponentExist(COMPONENT_ID component_id);

	// �ڽ� ������Ʈ�� �����ϴ� �Լ���
	void AddChild(ModelClass*);
	void DeleteChild(const int& k);
	ModelClass* GetChild(const int& i) const;
	vector<ModelClass*> GetChildren() const;

	void SetName(const string& str){ m_name = str; }
	const string& GetName(){ return m_name; }

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
	Vector3f m_worldPosition;
	Vector3f m_worldScale;
	Vector3f m_worldRotation;

	// �ӵ�
	// �̰ɷ� ���ӵ� ���� �͵� ���� �� ���� ��??
	Vector3f m_velocity;

	Mesh m_mesh;

	string m_name;

};

#endif