////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_LightShader = 0;
	m_Light = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	
	// Create the model object.
	// 여기서 초기화함!!!!!!!!!!!!!!!!!
	ModelCircleClass* circle = new ModelCircleClass;
	if (!circle)
		return false;
	
	ModelCubeClass* cube = new ModelCubeClass;
	if (!cube)
		return false;
	
	m_Models.push_back(circle);
	m_Models.push_back(cube);

	// Initialize the model object.
	for (int i = 0; i < m_Models.size(); i++)
	{
		result = m_Models[i]->Initialize(m_D3D->GetDevice(), L"./data/seafloor.dds");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the model object.

	for (int i = 0; i < m_Models.size(); i++)
	{
		if (m_Models[i])
		{
			m_Models[i]->Shutdown();
			delete m_Models[i];
			m_Models[i] = 0;
		}
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}

//bool GraphicsClass::Start()
//{
//
//}

// 각 프레임마다 호출되는 함수
bool GraphicsClass::Frame()
{
	bool result;

	// 하... 망했다 너무 맘대로다
	// 보통 어떤식으로 짜는지 모르니까 넘 힘들다 ㅠ
	for (int i = 0; i < m_Models.size(); i++)
	{
		m_Models[i]->Update();
		m_Models[i]->SyncMatrix();
	}

	for (int i = 0; i < m_Models.size(); i++)
	{
		for (int j = i + 1; j < m_Models.size(); j++)
		{
			if (m_Models[i]->isComponentExist(COM_COLLIDER) &&
				m_Models[j]->isComponentExist(COM_COLLIDER))
			{
				if (CollisionCheck(m_Models[i], m_Models[j]))
				{
					// TODO!!!!!!!!!!!!!!!!!!!!!
					// 누구와 부딪혔는지 인자로 넘겨줄 것!!!!!!!!
					m_Models[i]->OnCollisionStay(m_Models[j]);
					m_Models[j]->OnCollisionStay(m_Models[i]);

					// TODO!!!!!!!!!!!!!!!!!!!!!!!
					// 메모리 누수를 신경씁시다
					m_Models.erase(m_Models.begin() + j);
				}
			}
		}
	}

	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render()
{
	D3DXMATRIX viewMatrix, projectionMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	
	for (int i = 0; i < m_Models.size(); i++)
	{
		m_Models[i]->Render(m_D3D->GetDeviceContext());
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(), m_Models[i]->GetWorldMatrix(), viewMatrix, projectionMatrix,
			m_Models[i]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result)
		{
			return false;
		}
	}
	// Render the model using the light shader.
	
	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}


// TODO!!!!!!!!!!!!!!!!!!!!!!!!
// MYMATH 클래스로 다 빼낼것
double GetDistance(D3DXVECTOR3 a, D3DXVECTOR3 b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) +
		(a.y - b.y)*(a.y - b.y) +
		(a.z - b.z)*(a.z - b.z));
}

// TODO!!!!!!!!!!!!!!!!!!!!!!!!
// MYMATH 클래스로 다 빼낼것
D3DXVECTOR3 ScaleProduct(D3DXVECTOR3 a, D3DXVECTOR3 b)
{
	D3DXVECTOR3 ret;
	ret.x = a.x*b.x;
	ret.y = a.y*b.y;
	ret.z = a.z*b.z;
	return ret;
}

// TODO!!!!!!!!!!!!!!!!!!!!!!!!
// MYMATH 클래스로 다 빼낼것
D3DXVECTOR3 VECTOR3PLUS(D3DXVECTOR3 a, D3DXVECTOR3 b)
{
	D3DXVECTOR3 ret;
	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return ret;
}

bool GraphicsClass::CollisionCheck(ModelClass* model1, ModelClass* model2)
{
	Collider* model1_col = ((Collider*)model1->GetComponent(COM_COLLIDER));
	Collider* model2_col = ((Collider*)model2->GetComponent(COM_COLLIDER));

	COLLIDER_TYPE col_type1 = model1_col->GetType();
	COLLIDER_TYPE col_type2 = model2_col->GetType();

	D3DXVECTOR3 center1, center2, size1, size2, rot1, rot2;

	center1 = VECTOR3PLUS(model1->GetPosition(),
		ScaleProduct(model1_col->GetCenter(), model1->GetScale()));
	center2 = VECTOR3PLUS(model2->GetPosition(),
		ScaleProduct(model2_col->GetCenter(), model2->GetScale()));

	size1 = ScaleProduct(model1_col->GetSize(), model1->GetScale());
	size2 = ScaleProduct(model2_col->GetSize(), model2->GetScale());
	
	// TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// 좌표계 관리 해야함
	if (GetDistance(model1->GetPosition(), model2->GetPosition()) <
		model1->GetScale().x + model2->GetScale().x)
	{
		return true;
	}
	else
	{
	}


	Vector3f a = { 1.0f, 2.0f, 5.0f };
	Vector3f b = { 2.0f, 1.5f, 1.0f };

	float aa = (a*b).GetX();
	float bb = (a*b).GetY();
	float cc = (a*b).GetZ();

	
	return false;
}