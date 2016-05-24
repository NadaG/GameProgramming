////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "systemclass.h"
#include<d3d10.h>
<<<<<<< HEAD

=======
//TEST123
>>>>>>> becafe56557b90d21eda4467c558a307d1aa8441
#pragma comment( lib, "d3d11.lib" )   // D3D11 라이브러리 
#pragma comment( lib, "d3dx11.lib" )

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* System;
	bool result;

	// Create the system object.
	System = new SystemClass;
	if (!System)
	{
		return 0;
	}

	// Initialize and run the system object.
	result = System->Initialize();
	if (result)
	{
		System->Run();
	}

	// Shutdown and release the system object.
	System->Shutdown();
	delete System;
	System = 0;

	return 0;
}