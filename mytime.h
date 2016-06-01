#ifndef _MYTIME_H_
#define _MYTIME_H_

#include<ctime>

class MyTime
{
public:
	
	static MyTime* GetInstance();

	void SetStartTime();
	void SetEndTime();

	const clock_t& GetDeltaTime();
	
private:

	MyTime();
	MyTime(const MyTime& mytime);
	const MyTime& operator=(const MyTime& mytime);
	~MyTime();

	static MyTime* m_instance;

	clock_t m_deltaTime;

	clock_t m_startTime;
	clock_t m_endTime;
};

#endif