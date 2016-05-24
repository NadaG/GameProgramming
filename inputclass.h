////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_
#include<iostream>
#include<stdlib.h>

#include"mymath.h"

using namespace std;

enum INPUT_MOUSE_TYPE
{
	MOUSE_LEFT = 0,
	MOUSE_RIGHT = 1,
	MOUSE_MIDDLE = 2
};

////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////
class InputClass
{
public:
    static InputClass* GetInstance();

    void Initialize();

	// Keyboard 관련된 함수들!
    void KeyDown(unsigned int);
    void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

	// Mouse 관련된 함수들!
	// 버튼이 눌러지는 순간에 true 리턴
	const bool& GetMouseButtonDown(const INPUT_MOUSE_TYPE& t);
	// 버튼이 떨어지는 순간에 true 리턴
	const bool& GetMouseButtonUp(const INPUT_MOUSE_TYPE& t);
	// 버튼이 눌러지는 동안 true 리턴
	const bool& GetMouseButton(const INPUT_MOUSE_TYPE& t);
	const Vector2f& GetMousePos();

	// SystemClass에서 호출할 함수
	void ButtonDown(const INPUT_MOUSE_TYPE& t);
	void ButtonUp(const INPUT_MOUSE_TYPE& t);

private:
    bool m_keys[256];

	// enum의 크기만큼의 크기로 배열을 만들고 싶음
	// 마우스가 눌러졌는지 체크하는 변수
	bool m_mouse[4];
	// 마우스 누르고 떼고를 관리하기 위해 사용하는 변수
	bool m_mouseDownFlag[4];
	bool m_mouseUpFlag[4];

	InputClass();
	~InputClass();

	static InputClass* m_instance;
};


#endif