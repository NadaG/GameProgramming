#include"Debug.h"
//dasdasdsad
using namespace std;

Debug* Debug::m_instance = 0;

Debug* Debug::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new Debug;
	return m_instance;
}

Debug::Debug()
{
}

Debug::Debug(const Debug& debug)
{
}

Debug::~Debug()
{
}

void Debug::Log(const char* str)
{
	cout << str << endl;
}

void Debug::Log(const string& str)
{
	cout << str << endl;
}


void Debug::Log(const int& num)
{
	cout << num << endl;
}

void Debug::Log(const float& fnum)
{
	cout << fnum << endl;
}

void Debug::Log(const Vector3f& vec)
{
	cout << "x:" << vec.m_x << " y:" << vec.m_y << " z:" << vec.m_z << endl;
}


void Debug::Log(const Vector2f& vec)
{
	cout << "x:" << vec.m_x << " y:" << vec.m_y << endl;
}