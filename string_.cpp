#include <iostream>
#include "string_.h"

using namespace std;

#pragma warning( disable : 4996 )
//#define _CRT_SECURE_NO_WARNINGS

String::String(const char* s)
{
	if (nullptr == s) {
		m_data = new char[1];
		m_data[0] = '\0';
	}
	else {
		m_data = new char[strlen(s) + 1];
		strcpy(m_data, s);
		//m_data[strlen(s)] = '\0';	//不需要，因为s+strlen(s)一定是'\0'
	}
	cout << "constructor: " << m_data << endl;
}

String::String(const String& rhs)
{
	m_data = new char[strlen(rhs.m_data) + 1];
	strcpy(m_data, rhs.m_data);
	cout << "copy constructor: " << m_data << endl;
}

//不需要检验rhs是否为nullptr，因为它存在就代表它已经在构造的时候获得至少一字节的内存
String& String::operator=(const String& rhs)
{
	char* new_data = new char[strlen(rhs.m_data) + 1];
	strcpy(new_data, rhs.m_data);
	delete[] m_data;	//m_data一定非空
	m_data = new_data;
	cout << "copy assignment: " << m_data << endl;
	return *this;
}

String::~String()
{
	cout << "destructor: " <</* m_data <<*/ endl;
	delete[] m_data;
}

String::String(String&& rhs) : m_data(rhs.m_data)
{
	rhs.m_data = nullptr;	//为空不会调用析构函数
	cout << "move constructor: " << m_data << endl;
}

String& String::operator=(String&& rhs)
{
	if (this != &rhs) {
		delete[] m_data;
		m_data = rhs.m_data;
		rhs.m_data = nullptr;	//rhs.m_data=nullptr后，rhs变为0X0?
	}
	cout << "move assginment: " << m_data << endl;
	return *this;
}