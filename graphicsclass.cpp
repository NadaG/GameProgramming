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
	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 1000; j++)
		{
			isCollisionChecked[i][j] = false;
		}
	}
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
	
	InitializeTransform();
	for (int i = 0; i < m_Models.size(); i++)
	{
		m_Models[i]->Start();
	}

	// Initialize the model object.
	for (int i = 0; i < m_Models.size(); i++)
	{
		result = m_Models[i]->InitializeByTag(m_D3D->GetDevice(), m_Models[i]->GetTag());
		/*switch (m_Models[i]->GetTag())
		{
		case MODEL_CIRCLE:
			result = m_Models[i]->Initialize(m_D3D->GetDevice(), L"./data/seafloor.dds");
			break;
		case MODEL_CUBE:
			result = m_Models[i]->Initialize(m_D3D->GetDevice(), L"./data/earth.dds");
			break;
		case MODEL_RACKET:
			result = m_Models[i]->Initialize(m_D3D->GetDevice(), L"./data/seafloor.dds");
			break;
		case MODEL_SPHERE:
			result = m_Models[i]->Initialize(m_D3D->GetDevice(), L"./data/earth.dds");
			break;
		default:
			break; 
		}*/

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

	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(0.7f, 0.7f, 0.7f, 1.0f);
	m_Light->SetDirection(0.0f, 1.0f, 1.0f);
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

// 각 프레임마다 호출되는 함수
bool GraphicsClass::Frame()
{
	bool result;

	// 하... 망했다 너무 맘대로다
	// 보통 어떤식으로 짜는지 모르니까 넘 힘들다 ㅠ
	clock_t starttm = clock();

	for (int i = 0; i < m_Models.size(); i++)
	{
		m_Models[i]->Update();
		m_Models[i]->SyncMatrix();
	}

	//Debug::GetInstance()->Log(MyTime::GetInstance()->GetDeltaTime());

	InputClass::GetInstance()->ButtonUpEnd(MOUSE_LEFT);
	InputClass::GetInstance()->ButtonUpEnd(MOUSE_RIGHT);
	InputClass::GetInstance()->ButtonDownEnd(MOUSE_LEFT);
	InputClass::GetInstance()->ButtonDownEnd(MOUSE_RIGHT);

	for (int i = 0; i < m_Models.size(); i++)
	{
		for (int j = i + 1; j < m_Models.size(); j++)
		{
			if (m_Models[i]->isComponentExist(COM_COLLIDER) &&
				m_Models[j]->isComponentExist(COM_COLLIDER))
			{
				if (CollisionCheck(m_Models[i], m_Models[j]))
				{
					if (isCollisionChecked[i][j] && isCollisionChecked[j][i])
					{
						m_Models[i]->OnCollisionStay(m_Models[j]);
						m_Models[j]->OnCollisionStay(m_Models[i]);
					}
					else
					{
						isCollisionChecked[i][j] = true;
						isCollisionChecked[j][i] = true;
						m_Models[i]->OnCollisionEnter(m_Models[j]);
						m_Models[j]->OnCollisionEnter(m_Models[i]);
					}
				}
				else if (isCollisionChecked[i][j] && isCollisionChecked[j][i])
				{
					isCollisionChecked[i][j] = false;
					isCollisionChecked[j][i] = false;
					m_Models[i]->OnCollisionExit(m_Models[j]);
					m_Models[j]->OnCollisionExit(m_Models[i]);
				}
			}
		}
	}

	// Render the graphics scene.
	result = Render();

	clock_t endtm = clock();
	MyTime::GetInstance()->SetDeltaTime(float(endtm - starttm) / CLOCKS_PER_SEC);

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
		switch (m_Models[i]->GetTag())
		{
		case MODEL_CIRCLE:
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(), m_Models[i]->GetWorldMatrix(), viewMatrix, projectionMatrix,
				m_Models[i]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
			break;
		case MODEL_CUBE:
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(), m_Models[i]->GetWorldMatrix(), viewMatrix, projectionMatrix,
				m_Models[i]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
			
			break;
		case MODEL_RACKET:
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(), m_Models[i]->GetWorldMatrix(), viewMatrix, projectionMatrix,
				m_Models[i]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
			break;
		case MODEL_SPHERE:
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(), m_Models[i]->GetWorldMatrix(), viewMatrix, projectionMatrix,
				m_Models[i]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
			break;
		default:
			result = true;
			break;
		}
		
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
	ModelCubeClass* cube = new ModelCubeClass;
	ModelCubeClass* cube2 = new ModelCubeClass;
	ModelCubeClass* cube3 = new ModelCubeClass;
	ModelCubeClass* cube4 = new ModelCubeClass;
	ModelCubeClass* cube5 = new ModelCubeClass;
	ModelCubeClass* cube6 = new ModelCubeClass;
	ModelCubeClass* cube7 = new ModelCubeClass;
	ModelCubeClass* cube8 = new ModelCubeClass;
	ModelCubeClass* cube9 = new ModelCubeClass;
	ModelRacketClass* racket1 = new ModelRacketClass;

	m_Models.push_back(circle);

	m_Models.push_back(cube); 
	cube->SetDirection(FRONT_BACK);
	m_Models.push_back(cube2);
	cube2->SetDirection(LEFT_RIGHT);
	
	m_Models.push_back(cube3);
	cube3->SetDirection(LEFT_RIGHT);
	m_Models.push_back(cube4);
	cube4->SetDirection(UP_DOWN);
	m_Models.push_back(cube5);
	cube5->SetDirection(UP_DOWN);


	//cube 6,7,8,9는 부술것.
	//cube1은 닿으면 게임종료.
	m_Models.push_back(cube6);
	cube6->SetDirection(FRONT_BACK);
	m_Models.push_back(cube7);
	cube7->SetDirection(FRONT_BACK);
	m_Models.push_back(cube8);
	cube8->SetDirection(FRONT_BACK);
	m_Models.push_back(cube9);
	cube9->SetDirection(FRONT_BACK);

	m_Models.push_back(racket1);

	return true;
}

void GraphicsClass::InitializeTransform()
{
	m_Models[1]->SetWorldPosition({ 0.0f, 0.0f, 22.5f });
	m_Models[1]->SetWorldScale({ 10.0f, 10.0f, 1.0f });

	m_Models[2]->SetWorldPosition({ -5.0f, 0.0f, 20.0f });
	m_Models[2]->SetWorldScale({ 1.0f, 10.0f, 50.0f });

	m_Models[3]->SetWorldPosition({ 5.0f, 0.0f, 20.0f });
	m_Models[3]->SetWorldScale({ 1.0f, 10.0f, 50.0f });
	
	m_Models[4]->SetWorldPosition({ 0.0f, 5.0f, 20.0f });
	m_Models[4]->SetWorldScale({ 10.0f, 1.0f, 50.0f });

	m_Models[5]->SetWorldPosition({ 0.0f, -5.0f, 20.0f });
	m_Models[5]->SetWorldScale({ 10.0f, 1.0f, 50.0f });

	m_Models[6]->SetWorldPosition({ -2.5f, 2.5f, 18.0f });
	m_Models[6]->SetWorldScale({ 5.0f, 5.0f, 1.0f });

	m_Models[7]->SetWorldPosition({ 2.5f, 2.5f, 18.0f });
	m_Models[7]->SetWorldScale({ 5.0f, 5.0f, 1.0f });

	m_Models[8]->SetWorldPosition({ 2.5f, -2.5f, 18.0f });
	m_Models[8]->SetWorldScale({ 5.0f, 5.0f, 1.0f });

	m_Models[9]->SetWorldPosition({ -2.5f, -2.5f, 18.0f });
	m_Models[9]->SetWorldScale({ 5.0f, 5.0f, 1.0f });
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

	center1 = model1->GetWorldPosition();
	center2 = model2->GetWorldPosition();

	//Debug::GetInstance()->Log(center2);

	rot1 = model1->GetWorldRotation();
	rot2 = model2->GetWorldRotation();

	// 충돌체의 월드좌표계에서의 크기
	size1 = model1->GetWorldScale();
	size2 = model2->GetWorldScale();


	// TODO!!!!!!!!!!!!!! 반지름이 모든 충돌체에 있지는 않을것
	// 충돌체의 반지름!!!!!!!!!!!
	radius1 = model1_col->GetRadius();
	radius2 = model2_col->GetRadius();

	// 월드 좌표계, 충돌체의 센터, 회전, 크기를 이용해서 각각 점의 노말벡터와 위치를 구해낸다.

	// TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// 좌표계 관리 해야함

	Vector3f Model1Min = { center1.m_x - size1.m_x / 2, center1.m_y - size1.m_y / 2, center1.m_z - size1.m_z / 2 };
	Vector3f Model1Max = { center1.m_x + size1.m_x / 2, center1.m_y + size1.m_y / 2, center1.m_z + size1.m_z / 2 };
	Vector3f Model2Min = { center2.m_x - size2.m_x / 2, center2.m_y - size2.m_y / 2, center2.m_z - size2.m_z / 2 };
	Vector3f Model2Max = { center2.m_x + size2.m_x / 2, center2.m_y + size2.m_y / 2, center2.m_z + size2.m_z / 2 };

	switch (col_type1)
	{
	case COL_CUBE:

		switch (col_type2)
		{
		case COL_CUBE:
			if ((Model1Max.m_x > Model2Min.m_x && Model1Min.m_x < Model2Max.m_x) &&
				(Model1Max.m_y > Model2Min.m_y && Model1Min.m_y < Model2Max.m_y) &&
				(Model1Max.m_z > Model2Min.m_z && Model1Min.m_z < Model2Max.m_z))
			{
				return true;
			}
			else
				return false;
			break;
		case COL_SPHERE:
			// 구해낸 노말벡터와 위치를 이용해
			// 충돌처리를 할 수 있음... ㅠㅠ

			if (GetDistance(model1->GetWorldPosition(), model2->GetWorldPosition()) <
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
			if (GetDistance(model1->GetWorldPosition(), model2->GetWorldPosition()) <
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

void GraphicsClass::Create(ModelClass* model, Vector3f pos, Vector3f rot, Vector3f scale)
{
	model->SetWorldPosition(pos);
	model->SetWorldScale(scale);
	model->SetWorldRotation(rot);
	m_Models.push_back(model);
	model->Start();
	model->InitializeByTag(m_D3D->GetDevice(), model->GetTag());
}

void GraphicsClass::Destroy(ModelClass* model)
{

	vector<ModelClass*>::iterator itr;
	for (itr = m_Models.begin(); itr != m_Models.end(); itr++)
	{
		if (*itr == model)
		{
			m_Models.erase(itr);
			break;
		}
	}
}

void GraphicsClass::DestroyAll()
{
	while (!m_Models.empty())
	{
		m_Models.pop_back();
	}
}