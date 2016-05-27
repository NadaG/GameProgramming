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
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	vector<ModelClass*> m_Models;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	
	bool CollisionCheck(ModelClass*, ModelClass*);
	bool InitializeModels();
	void InitializeTransform();

	// TODO!!!!!!!!!!!!!!!!!! 나중에 할것 pimpl 인가? ㄷ
	class CollisionChecker
	{


	};
};

#endif