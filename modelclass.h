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
#include <thread>
#include <chrono>
using namespace std;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include"textureclass.h"
#include "inputclass.h"
#include "debug.h"
#include "component.h"
#include "colliderclass.h"
#include "meshclass.h"
#include "mymath.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////

// ���� �±�
// �� ���� ������Ʈ�� �±׸� �Ҵ��ؼ� ���� ����
enum MODEL_TAG
{
	MODEL_NONE = 0,
	MODEL_CIRCLE = 1,
	MODEL_CUBE = 2,
	MODEL_RACKET = 3,
	MODEL_SPHERE = 4
};

enum WALL_DIRECTION
{
	LEFT_RIGHT = 0,
	UP_DOWN = 1,
	FRONT_BACK = 2
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
    int HP;
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();
	D3DXMATRIX GetWorldMatrix();

	// ��Ʈ������ ����ȭ�ϴ� �Լ�
	void SyncMatrix();

	// ������ ������Ʈ ���� ���� �����Ǵ� �Լ���
	// ��ũ��Ʈ �κ��� ���⼭ ¥���� �ϸ� �ɰ�!
	virtual void Update();
	virtual void OnCollisionStay(ModelClass* model);
	virtual void Start();
	
	// TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// �ڽ� ��ǥ��� �θ� ��ǥ�踦 �� �����!!!!

	const Vector3f& GetWorldPosition() const{ return m_worldPosition; }
	const Vector3f& GetWorldRotation() const{ return m_worldRotation; }
	const Vector3f& GetWorldScale() const{ return m_worldScale; }
	
	void SetWorldPosition(const Vector3f& position){ m_worldPosition = position; }
	void SetWorldRotation(const Vector3f& rotation){ m_worldRotation = rotation; }
	void SetWorldScale(const Vector3f& scale){ m_worldScale = scale; }

	const Vector3f& GetLocalPosition() const{ return m_localPosition; }
	const Vector3f& GetLocalRotation() const{ return m_localRotation; }
	const Vector3f& GetLocalScale() const{ return m_localScale; }

	void SetLocalPosition(const Vector3f& position){ m_localPosition = position; }
	void SetLocalRotation(const Vector3f& rotation){ m_localRotation = rotation; }
	void SetLocalScale(const Vector3f& scale){ m_localScale = scale; }

	/////////////////////////////////////////////////////////////////////////

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

	void SetTag(const MODEL_TAG& tag){ m_tag = tag; }
	const MODEL_TAG& GetTag(){ return m_tag; }

	void SetVelocity(const Vector3f& velo){ m_velocity = velo; }
	const Vector3f& GetVelocity(){ return m_velocity; }

	void SetDirection(const WALL_DIRECTION& wall_direction);
	const WALL_DIRECTION& GetDirection() const;

protected:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	virtual bool LoadModel();
	void ReleaseModel();

protected:

	WALL_DIRECTION m_wallDirection;

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
	Vector3f m_localPosition;
	Vector3f m_localScale;
	Vector3f m_localRotation;

	Vector3f m_worldPosition;
	Vector3f m_worldScale;
	Vector3f m_worldRotation;

	// �ӵ�
	// �̰ɷ� ���ӵ� ���� �͵� ���� �� ���� ��??
	Vector3f m_velocity;

	Mesh m_mesh;

	string m_name;
	MODEL_TAG m_tag;
};

#endif