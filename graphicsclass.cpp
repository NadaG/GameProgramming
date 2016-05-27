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
	result = InitializeModels();
	if (!result)
	{
		MessageBox(hwnd, L"Initialize models failed", L"Error", MB_OK);
		return false;
	}

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

	InitializeTransform();

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
					//m_Models.erase(m_Models.begin() + j);
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

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 여기서 미리 위치와 회전 스케일을 정할것
bool GraphicsClass::InitializeModels()
{
	ModelCircleClass* circle = new ModelCircleClass;
	if (!circle)
		return false;

	ModelCubeClass* cube = new ModelCubeClass;
	ModelCubeClass* cube2 = new ModelCubeClass;
	ModelCubeClass* cube3 = new ModelCubeClass;
	ModelCubeClass* cube4 = new ModelCubeClass;
	ModelCubeClass* cube5 = new ModelCubeClass;
	ModelRacketClass* racket1 = new ModelRacketClass;
	ModelSphereClass* sphere = new ModelSphereClass;

	m_Models.push_back(circle);
	m_Models.push_back(cube);
	m_Models.push_back(racket1);
	m_Models.push_back(sphere);
	/*m_Models.push_back(cube2);
	m_Models.push_back(cube3);
	m_Models.push_back(cube4);
	m_Models.push_back(cube5);*/
}

void GraphicsClass::InitializeTransform()
{
	m_Models[1]->SetPosition({ 0.0f, 0.0f, 12.5f });
	m_Models[1]->SetScale({ 5.0f, 5.0f, 1.0f });

	/*m_Models[2]->SetPosition({ 0.0f, 5.0f, 10.0f });
	m_Models[2]->SetScale({ 5.0f, 0.3f, 1.0f });
	
	m_Models[3]->SetPosition({ 0.0f, -5.0f, 10.0f });
	m_Models[3]->SetScale({ 5.0f, 0.3f, 1.0f });
	
	m_Models[4]->SetPosition({ 5.0f, 0.0f, 10.0f });
	m_Models[4]->SetScale({ 5.0f, 0.3f, 1.0f });
	m_Models[4]->SetRotation({ 0.0f, 0.0f, 90.0f });

	m_Models[5]->SetPosition({ -5.0f, 0.0f, 10.0f });
	m_Models[5]->SetScale({ 5.0f, 0.3f, 1.0f });
	m_Models[5]->SetRotation({ 0.0f, 0.0f, -90.0f });*/
}

bool GraphicsClass::CollisionCheck(ModelClass* model1, ModelClass* model2)
{
	// TODO!!!!!! 
	// GetComponent template 프로그래밍을 배워서 바꿀것!!!!!!!
	Collider* model1_col = ((Collider*)model1->GetComponent(COM_COLLIDER));
	Collider* model2_col = ((Collider*)model2->GetComponent(COM_COLLIDER));

	COLLIDER_TYPE col_type1 = model1_col->GetType();
	COLLIDER_TYPE col_type2 = model2_col->GetType();

	Vector3f center1, center2, size1, size2, rot1, rot2;
	float radius1, radius2;

	// 충돌체의 월드좌표계에서의 위치
	center1 = model1->GetPosition() + model1_col->GetCenter()*model1->GetScale();
	center2 = model2->GetPosition() + model2_col->GetCenter()*model2->GetScale();

	// 충돌체의 월드좌표계에서의 크기
	size1 = model1_col->GetSize()*model1->GetScale();
	size2 = model2_col->GetSize()*model2->GetScale();

	// TODO!!!!!!!!!!!!!! 반지름이 모든 충돌체에 있지는 않을것
	// 충돌체의 반지름!!!!!!!!!!!
	radius1 = model1_col->GetRadius();
	radius2 = model2_col->GetRadius();
	
	rot1 = model1->GetRotation() + model1_col->GetRotation();
	rot2 = model2->GetRotation() + model2_col->GetRotation();

	// 월드 좌표계, 충돌체의 센터, 회전, 크기를 이용해서 각각 점의 노말벡터와 위치를 구해낸다.
	


	// TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// 좌표계 관리 해야함
	switch (col_type1)
	{
	case COL_CUBE:

		switch (col_type2)
		{
		case COL_CUBE:
			if ((center1.m_x + size1.m_x / 2 > center2.m_x - size2.m_x / 2 &&
				center1.m_x - size1.m_x / 2   < center2.m_x + size2.m_x / 2) &&
				(center1.m_y + size1.m_y / 2   > center2.m_y - size2.m_y / 2 &&
				center1.m_y - size1.m_y / 2  < center2.m_y + size2.m_y / 2) &&
				(center1.m_z + size1.m_z / 2 > center2.m_z - size2.m_z / 2 &&
				center1.m_z - size1.m_z / 2< center2.m_z + size2.m_z / 2))
			{
				return true;
			}
			else
				return false;
			break;
		case COL_SPHERE:
			// 구해낸 노말벡터와 위치를 이용해
			// 충돌처리를 할 수 있음... ㅠㅠ

			if (GetDistance(model1->GetPosition(), model2->GetPosition()) <
				radius1 + radius2)
			{
				return true;
			}
			else
			{
			}
			break;
		default:
			break;
		}

		break;
	case COL_SPHERE:
		switch (col_type2)
		{
		case COL_CUBE:
			return CollisionCheck(model2, model1);
		case COL_SPHERE:
			if (GetDistance(model1->GetPosition(), model2->GetPosition()) <
				radius1 + radius2)
			{
				return true;
			}
			else
			{
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}


	
	return false;
}