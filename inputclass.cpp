////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "inputclass.h"
#include<Windows.h>
#include<iostream>
using namespace std;
InputClass* InputClass::m_instance = new InputClass;

InputClass::InputClass()
{
}

InputClass::~InputClass()
{
}

InputClass* InputClass::GetInstance()
{
    return m_instance;
}

void InputClass::Initialize()
{
    // Initialize all the keys to being released and not pressed.
    for (int i = 0; i<256; i++)
    {
	   m_keys[i] = false;
    }

	// 고쳐야할 하드코딩
	for (int i = 0; i < 4; i++)
	{
		m_mouse[i] = false;
		m_mouseDownFlag[i] = false;
		m_mouseUpFlag[i] = false;
	}

    return;
}


void InputClass::KeyDown(unsigned int input)
{
    // If a key is pressed then save that state in the key array.
    m_keys[input] = true;
    return;
}


void InputClass::KeyUp(unsigned int input)
{
    // If a key is released then clear that state in the key array.
    m_keys[input] = false;
    return;
}


bool InputClass::IsKeyDown(unsigned int key)
{
    // Return what state the key is in (pressed/not pressed).
    return m_keys[key];
}

void InputClass::ButtonDown(const INPUT_MOUSE_TYPE& t)
{
	m_mouseDownFlag[t] = true;
}

void InputClass::ButtonUp(const INPUT_MOUSE_TYPE& t)
{
	m_mouseUpFlag[t] = true;
}

const bool& InputClass::GetMouseButtonDown(const INPUT_MOUSE_TYPE& t)
{
	if (m_mouseDownFlag[t])
	{
		m_mouse[t] = true;
		m_mouseDownFlag[t] = false;
		return true;
	}
	else
		return false;
}

const bool& InputClass::GetMouseButtonUp(const INPUT_MOUSE_TYPE& t)
{
	if (m_mouseUpFlag[t])
	{
		m_mouse[t] = false;
		m_mouseUpFlag[t] = false;
		return true;
	}
	else
		return false;
}

const bool& InputClass::GetMouseButton(const INPUT_MOUSE_TYPE& t)
{
	if (m_mouse[t])
		return true;
	else
		return false;
}

const Vector2f& InputClass::GetMousePos()
{
	Vector2f ret;
	POINT cursor;
	GetCursorPos(&cursor);
	ret.m_x = cursor.x;
	ret.m_y = cursor.y;
	return ret;
}