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
    int i;
    leftclick = false;
    // Initialize all the keys to being released and not pressed.
    for (i = 0; i<256; i++)
    {
	   m_keys[i] = false;
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
void InputClass::MouseLeftButtonDown(unsigned int input)
{
    POINT mouse;
    ::GetCursorPos(&mouse);
    cout << "before : " << mouse.y << " " << mouse.x << endl;
    Y[0] = mouse.y;
    X[0] = mouse.x;
    return;
}
void InputClass::MouseLeftButtonUp(unsigned int input)
{
    POINT mouse;
    ::GetCursorPos(&mouse);
    cout << "after : " << mouse.y << " " << mouse.x << endl;
    Y[1] = mouse.y;
    X[1] = mouse.x;
    cout << Y[0] - Y[1] << " " << X[0] - X[1] << endl;
    leftclick = true;
    return;
}

float InputClass::getdiffY() {
    float ret = Y[1] - Y[0];
    ret /= 6400.0;
    return ret;
}
float InputClass::getdiffX() {
    float ret = X[1] - X[0];
    ret /= 6400.0;
    return ret;
}

bool InputClass::isMouseDown(unsigned int mouse) {
    return leftclick;
}