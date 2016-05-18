////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "modelclass.h"
#include "mymath.h"

static int id = 0;

ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
	m_model = 0;
	D3DXMatrixIdentity(&m_worldMatrix);

	m_worldPosition = { 1.0f, 0.0f, 1.0f };
	m_worldScale = { 1.0f, 1.0f, 1.0f };
	m_worldRotation = { 0.0f, 0.0f, 0.0f };

	m_id = id++;
}

ModelClass::ModelClass(const ModelClass& other)
{
}

ModelClass::~ModelClass()
{
}


bool ModelClass::Initialize(ID3D11Device* device, WCHAR* textureFilename)
{
	bool result;

	// Load in the model data,
	result = LoadModel();
	if(!result)
	{
		return false;
	}

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);
	if(!result)
	{
		return false;
	}

	Start();

	return true;
}

void ModelClass::SyncMatrix()
{
	D3DXMATRIX m;
	D3DXMatrixIdentity(&m_worldMatrix);
	D3DXMatrixScaling(&m, m_worldScale.x, m_worldScale.y, m_worldScale.z);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &m);

	D3DXMatrixRotationYawPitchRoll(&m, m_worldRotation.y*M_PI / 180.0f
		, m_worldRotation.x*M_PI / 180.0f
		, m_worldRotation.z*M_PI / 180.0f);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &m);

	D3DXMatrixTranslation(&m, m_worldPosition.x, m_worldPosition.y, m_worldPosition.z);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &m);
	
	//D3DXMatrixRotationYawPitchRoll(&m_worldMatrix, m_worldRotation.x, m_worldRotation.y, m_worldRotation.z);
	//D3DXMatrixScaling(&m_worldMatrix, m_worldScale.x, m_worldScale.y, m_worldScale.z);
}

void ModelClass::Shutdown()
{
	// Release the model texture.
	ReleaseTexture();

	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	// Release the model data.
	ReleaseModel();

	return;
}


void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}

int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	return m_Texture->GetTexture();
}

D3DXMATRIX ModelClass::GetWorldMatrix()
{
	return m_worldMatrix;
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	// Load the vertex array and index array with data.
	for (int i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = Vector3f(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = Vector2f(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = Vector3f(m_model[i].nx, m_model[i].ny, m_model[i].nz);
	}

	for (int i = 0; i < m_indexCount; i++)
	{
		indices[i] = m_model_indices[i];
	}

	// Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}

void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

bool ModelClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	bool result;

	// Create the texture object.
	m_Texture = new TextureClass;
	if(!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, filename);
	if(!result)
	{
		return false;
	}

	return true;
}

void ModelClass::ReleaseTexture()
{
	// Release the texture object.
	if(m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}

void ModelClass::ReleaseModel()
{
	if(m_model)
	{
		delete [] m_model;
		m_model = 0;
	}

	return;
}

bool ModelClass::LoadModel()
{
	return false;
}

// TODO!!!!!!!!!!!!!!!!!
// 필요없는 함수 정의
void ModelClass::Update()
{
}

// TODO!!!!!!!!!!!!!!!!!
// 필요없는 함수 정의
void ModelClass::OnCollisionStay(ModelClass* model)
{
}

// TODO!!!!!!!!!!!!!!!!!
// 필요없는 함수 정의
void ModelClass::Start()
{
}

const Component* ModelClass::GetComponent(COMPONENT_ID component_id) const
{
	return m_components.find(component_id)->second;
}

void ModelClass::SetComponent(COMPONENT_ID component_id, Component* component)
{
	m_components[component_id] = component;
}

void ModelClass::DeleteComponent(COMPONENT_ID component_id)
{
	if (isComponentExist(component_id))
	{
		m_components.erase(component_id);
	}
}

bool ModelClass::isComponentExist(COMPONENT_ID component_id)
{
	// nullptr로 할 경우 새 원소가 생성될 수 있기 때문에
	// 이런식으로 존재하는지 확인한다.
	return m_components.find(component_id) != m_components.end();
}

void ModelClass::AddChild(ModelClass* model)
{
	m_children.push_back(model);
}

void ModelClass::DeleteChild(const int& k)
{
	int j = 0;
	for (vector<ModelClass*>::iterator i = m_children.begin(); i != m_children.end(); ++i, ++j)
	{
		if (j == k)
		{
			m_children.erase(i);
			return;
		}
	}
}

ModelClass* ModelClass::GetChild(const int& t) const
{
	if (t >= m_children.size())
		Debug::GetInstance()->Log("No Children");

	for (int i = 0; i < m_children.size(); i++)
	{
		if (t == i)
			return m_children[i];
	}
}

vector<ModelClass*> ModelClass::GetChildren() const
{
	return m_children;
}