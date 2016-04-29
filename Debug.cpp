#include"Debug.h"

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

void Debug::Log(string str)
{
	cout << str << endl;
}