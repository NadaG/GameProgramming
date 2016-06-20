////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"

GraphicsClass* GraphicsClass::m_instance = new GraphicsClass;

GraphicsClass::GraphicsClass()
{
}

GraphicsClass* GraphicsClass::GetInstance()
{
	return m_instance;
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
		m_Models[i]->Shutdown();
		delete m_Models[i];
		m_Models[i] = 0;
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
						if (m_Models.size() <= 2)
							return true;
						m_Models[j]->OnCollisionStay(m_Models[i]);
					}
					else
					{
						isCollisionChecked[i][j] = true;
						isCollisionChecked[j][i] = true;
						m_Models[i]->OnCollisionEnter(m_Models[j]);
						if (m_Models.size() <= 2)
						{
							return true;
						}
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

const int StartIndexNum = 2;
const int MaxStageNum = 3;
bool GraphicsClass::InitializeModels()
{
	InitializeRacketAndCircle();

	for (int i = 0; i < MaxStageNum * 2; i++)
	{
		ModelCubeClass* cube = new ModelCubeClass;
		cube->SetDirection(LEFT_RIGHT);
		m_Models.push_back(cube);
	}

	for (int i = MaxStageNum * 2; i < MaxStageNum * 4; i++)
	{
		ModelCubeClass* cube = new ModelCubeClass;
		cube->SetDirection(UP_DOWN);
		m_Models.push_back(cube);
	}

	for (int i = MaxStageNum * 4; i < 44; i++)
	{
		ModelCubeClass* cube = new ModelCubeClass;
		cube->SetDirection(FRONT_BACK);
		m_Models.push_back(cube);
	}

	return true;
}

void GraphicsClass::InitializeTransform()
{
	for (int i = StartIndexNum; i < StartIndexNum + MaxStageNum * 2; i += 2)
	{
		m_Models[i]->SetWorldPosition({ -5.0f, 0.0f, 20.0f - 100 * ((i - StartIndexNum) / 2) });
		m_Models[i]->SetWorldScale({ 1.0f, 10.0f, 50.0f });
		m_Models[i]->SetBelongStage((i - StartIndexNum) / 2 + 1);

		m_Models[i + 1]->SetWorldPosition({ 5.0f, 0.0f, 20.0f - 100 * ((i - StartIndexNum) / 2) });
		m_Models[i + 1]->SetWorldScale({ 1.0f, 10.0f, 50.0f });
		m_Models[i + 1]->SetBelongStage((i - StartIndexNum) / 2 + 1);
	}

	for (int i = StartIndexNum + MaxStageNum * 2; i < StartIndexNum + MaxStageNum * 4; i += 2)
	{
		m_Models[i]->SetWorldPosition({ 0.0f, 5.0f, 20.0f - 100 * ((i - (StartIndexNum + MaxStageNum * 2)) / 2) });
		m_Models[i]->SetWorldScale({ 10.0f, 1.0f, 50.0f });
		m_Models[i]->SetBelongStage((i - (StartIndexNum + MaxStageNum * 2)) / 2 + 1);

		m_Models[i + 1]->SetWorldPosition({ 0.0f, -5.0f, 20.0f - 100 * ((i - (StartIndexNum + MaxStageNum * 2)) / 2) });
		m_Models[i + 1]->SetWorldScale({ 10.0f, 1.0f, 50.0f });
		m_Models[i + 1]->SetBelongStage((i - (StartIndexNum + MaxStageNum * 2)) / 2 + 1);
	}

	for (int i = StartIndexNum + MaxStageNum * 4; i < StartIndexNum + MaxStageNum * 4 + 3; i++)
	{
		m_Models[i]->SetWorldPosition({ 0.0f, 0.0f, 22.5f - 100 * (i - (StartIndexNum + MaxStageNum * 4))});
		m_Models[i]->SetWorldScale({ 10.0f, 10.0f, 1.0f });
		m_Models[i]->SetBelongStage((i - (StartIndexNum + MaxStageNum * 4)) + 1);
	}

	float start_x, start_y;
	int now = 17;
	for (int i = 0; i < 3; i++)
	{
		float width_height = 10.0f / (i + 2);
		start_x = -5.0f + (width_height / 2);
		start_y = 5.0f - (width_height / 2);
		for (int j = 0; j < i + 2; j++)
		{
			for (int k = 0; k < i + 2; k++)
			{
				m_Models[now]->SetWorldPosition({ start_x + j*width_height, start_y - k*width_height, 10.0f-i*100 });
				m_Models[now]->SetWorldScale({ width_height, width_height, 1.0f });
				m_Models[now]->SetBelongStage(i + 1);
				now++;
			}
		}
	}
}

void GraphicsClass::InitializeRacketAndCircle()
{
	ModelCircleClass* circle = new ModelCircleClass;
	ModelRacketClass* racket1 = new ModelRacketClass;
	m_Models.push_back(circle);
	m_Models.push_back(racket1);
	
}

void GraphicsClass::InitializeRacketAndCircleTransform()
{
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
	/*while (!m_Models.empty())
	{*/
	m_Models.clear();
	//}
}


void GraphicsClass::ToNextStage(const int& stage)
{
	vector<ModelClass*> tmp_vec;
	switch (stage)
	{
	case 1:
		break;
	case 2:
		for (int i = 0; i < m_Models.size(); i++)
		{
			if (m_Models[i]->GetTag() != MODEL_CUBE)
			{
				tmp_vec.push_back(m_Models[i]);
			}
		}

		for (int i = 0; i < tmp_vec.size(); i++)
		{
			m_Models.push_back(tmp_vec[i]);
			m_Models[i]->Start();
		}

		m_Camera->SetPosition(0.0f, 0.0f, -110.0f);
		break;
	case 3:
		for (int i = 0; i < m_Models.size(); i++)
		{
			if (m_Models[i]->GetTag() != MODEL_CUBE)
			{
				tmp_vec.push_back(m_Models[i]);
			}
		}

		for (int i = 0; i < tmp_vec.size(); i++)
		{
			m_Models.push_back(tmp_vec[i]);
			m_Models[i]->Start();
		}

		m_Camera->SetPosition(0.0f, 0.0f, -210.0f);
		break;
	default:
		break;
	}
}