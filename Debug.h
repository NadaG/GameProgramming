#ifndef _DEBUG_H_
#define _DEBUG_H_

#include<iostream>
#include<string>

#include"d3dclass.h"

using std::cout;
using std::endl;
using std::string;

class Debug
{
public:
	static Debug* GetInstance();
	void Log(const char* str);
	void Log(const string& str);
	void Log(const int& num);
	void Log(const float& fnum);
	void Log(const D3DXVECTOR3& vec);

private:
	Debug();
	Debug(const Debug& debug);
	~Debug();

	static Debug* m_instance;
};

#endif