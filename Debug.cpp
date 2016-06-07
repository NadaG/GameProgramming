#include"Debug.h"
//dasdasdsad
using namespace std;

Debug* Debug::m_instance = 0;

Debug* Debug::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new Debug;
	return m_instance;
}

Debug::Debug()
{
}

Debug::Debug(const Debug& debug)
{
}

const Debug& Debug::operator=(const Debug& debug)
{
	return debug;
}

Debug::~Debug()
{
}

void Debug::Log(const char* str)
{
	cout << str << endl;
}

void Debug::Log(const string& str)
{
	cout << str << endl;
}

void Debug::Log(const int& num)
{
	cout << num << endl;
}

void Debug::Log(const float& fnum)
{
	cout << fnum << endl;
}

void Debug::Log(const double& dnum)
{
	cout << dnum << endl;
}

void Debug::Log(const Vector3f& vec)
{
	cout << "x:" << vec.m_x << " y:" << vec.m_y << " z:" << vec.m_z << endl;
}

void Debug::Log(const Vector2f& vec)
{
	cout << "x:" << vec.m_x << " y:" << vec.m_y << endl;
}

void Debug::Log(const clock_t& t)
{
	cout << t / (double)CLOCKS_PER_SEC << "sec" << endl;
}

void Debug::Log(const Matrix4f& mat)
{
	cout << "m11: " << mat.m_mat[0][0] << " mat12: " << mat.m_mat[0][1] << " mat13: " << mat.m_mat[0][2] << " mat14: " << mat.m_mat[0][3] << endl;
	cout << "m21: " << mat.m_mat[1][0] << " mat22: " << mat.m_mat[1][1] << " mat23: " << mat.m_mat[1][2] << " mat24: " << mat.m_mat[1][3] << endl;
	cout << "m31: " << mat.m_mat[2][0] << " mat32: " << mat.m_mat[2][1] << " mat33: " << mat.m_mat[2][2] << " mat34: " << mat.m_mat[2][3] << endl;
	cout << "m41: " << mat.m_mat[3][0] << " mat42: " << mat.m_mat[3][1] << " mat43: " << mat.m_mat[3][2] << " mat44: " << mat.m_mat[3][3] << endl;
}