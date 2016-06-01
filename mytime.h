#ifndef _MYTIME_H_
#define _MYTIME_H_

#include<ctime>

class MyTime
{
public:
	
	static MyTime* GetInstance();

	void SetDeltaTime(float dtm);
	float GetDeltaTime();
	
private:

	MyTime();
	MyTime(const MyTime& mytime);
	const MyTime& operator=(const MyTime& mytime);
	~MyTime();

	static MyTime* m_instance;

	float m_deltaTime;
};

#endif