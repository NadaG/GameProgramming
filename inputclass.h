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

	// Keyboard ���õ� �Լ���!
    void KeyDown(unsigned int);
    void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

	// Mouse ���õ� �Լ���!
	// ��ư�� �������� ������ true ����
	const bool& GetMouseButtonDown(const INPUT_MOUSE_TYPE& t);
	// ��ư�� �������� ������ true ����
	const bool& GetMouseButtonUp(const INPUT_MOUSE_TYPE& t);
	// ��ư�� �������� ���� true ����
	const bool& GetMouseButton(const INPUT_MOUSE_TYPE& t);
	const Vector2f& GetMousePos();

	// SystemClass���� ȣ���� �Լ�
	void ButtonDown(const INPUT_MOUSE_TYPE& t);
	void ButtonUp(const INPUT_MOUSE_TYPE& t);

private:
    bool m_keys[256];

	// enum�� ũ�⸸ŭ�� ũ��� �迭�� ����� ����
	// ���콺�� ���������� üũ�ϴ� ����
	bool m_mouse[4];
	// ���콺 ������ ���� �����ϱ� ���� ����ϴ� ����
	bool m_mouseDownFlag[4];
	bool m_mouseUpFlag[4];

	InputClass();
	~InputClass();

	static InputClass* m_instance;
};


#endif