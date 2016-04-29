#ifndef _DEBUG_H_
#define _DEBUG_H_

#include<iostream>
#include<string>

using std::cout;
using std::endl;
using std::string;

class Debug
{
public:
	static Debug* GetInstance();
	void Log(string str);

private:
	Debug();
	Debug(const Debug& debug);
	~Debug();

	static Debug* m_instance;
};

#endif