////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include<vector>
#include<xtree>
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelcircleclass.h"
#include "modelcubeclass.h"
#include "modelracketclass.h"
#include "modelsphereclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "mymath.h"
#include "inputclass.h"
#include "mytime.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	
	static GraphicsClass* GetInstance();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

	void Create(ModelClass* model, Vector3f pos, Vector3f rot, Vector3f scale);

	void Destroy(ModelClass* model);
	void DestroyAll();
	void ToNextStage(const int& stage);

	int s_StageNum = 1;

private:
	bool Render();

	static GraphicsClass* m_instance;

	GraphicsClass();
	~GraphicsClass();

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	vector<ModelClass*> m_Models;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	
	//// bool로 할지 vector로 할지 못 정하겠다
	bool isCollisionChecked[1000][1000];

	bool CollisionCheck(ModelClass*, ModelClass*);
	bool InitializeModels();
	void InitializeTransform();

	void InitializeRacketAndCircle();
	void InitializeRacketAndCircleTransform();
};

#endif