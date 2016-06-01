#include"mytime.h"
#include "debug.h"

MyTime* MyTime::m_instance = 0;

MyTime::MyTime()
:m_deltaTime(0)
{
}

MyTime::MyTime(const MyTime& mytime)
{
}

const MyTime& MyTime::operator=(const MyTime& mytime)
{
	return mytime;
}

MyTime::~MyTime()
{
}

MyTime* MyTime::GetInstance()
{
	if (!m_instance)
		m_instance = new MyTime();

	return m_instance;
}

void MyTime::SetDeltaTime(float dtm)
{
	m_deltaTime = dtm;
}

float MyTime::GetDeltaTime()
{
	return m_deltaTime;
}
