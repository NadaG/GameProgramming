#ifndef _DEBUG_H_
#define _DEBUG_H_

#include<iostream>
#include<string>

#include"d3dclass.h"
#include"mymath.h"
#include"mytime.h"

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
	void Log(const double& dnum);
	void Log(const Vector3f& vec);
	void Log(const Vector2f& vec);
	void Log(const clock_t& t);

private:
	Debug();
	Debug(const Debug& debug);
	const Debug& operator=(const Debug& debug);
	~Debug();

	static Debug* m_instance;
};

#endif

