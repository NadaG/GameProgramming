#include"mytime.h"

MyTime* MyTime::m_instance = 0;

MyTime::MyTime()
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
	if (m_instance == nullptr)
		m_instance = new MyTime;
	return m_instance;
}

void MyTime::SetStartTime()
{
	m_startTime = clock();
}

void MyTime::SetEndTime()
{
	m_endTime = clock();
}

const clock_t& MyTime::GetDeltaTime()
{
	return m_endTime - m_startTime;
}
