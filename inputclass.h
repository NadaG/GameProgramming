////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_
#include<iostream>
#include<stdlib.h>
using namespace std;
////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////
class InputClass
{
public:
    static InputClass* GetInstance();

    void Initialize();

    void KeyDown(unsigned int);
    void KeyUp(unsigned int);
    void MouseLeftButtonDown(unsigned int);
    void MouseLeftButtonUp(unsigned int);
    


    bool IsKeyDown(unsigned int);
    bool isMouseDown(unsigned int);


    int getMouseX(unsigned int);
    int getMouseY(unsigned int);
    float getdiffY();
    float getdiffX();

private:
    bool m_keys[256];
    bool leftclick;
    InputClass();
    ~InputClass();

    int Y[2];
    int X[2];
    static InputClass* m_instance;
};


#endif