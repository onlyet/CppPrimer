#include<iostream>
#include"string_.h"

String::String(const char* s)
{
	if (nullptr == s) {
		m_data = new char[1];
		m_data[0] = '\0';
	}
	m_data = new char[strlen(s) + 1];
	strcpy(m_data, s);
	//m_data[strlen(s)] = '\0';	//不需要，因为s+strlen(s)一定是'\0'
}

String::String(const String& rhs)
{
	m_data = new char[strlen(rhs.m_data) + 1];
	strcpy(m_data, rhs.m_data);
}

//不需要检验rhs是否为nullptr，因为它存在就代表它已经在构造的时候获得至少一字节的内存
String& String::operator=(const String& rhs)
{
	char* new_data = new char[strlen(rhs.m_data) + 1];
	strcpy(new_data, rhs.m_data);
	delete[] m_data;
	m_data = new_data;
	return *this;
}

String::~String()
{
	delete[] m_data;
}

String::String(String&& rhs)
{
	m_data = rhs.m_data;
	rhs.m_data = nullptr;
}

String& String::operator=(String&& rhs)
{
	if (this != &rhs) {
		delete[] m_data;
		m_data = rhs.m_data;
		rhs.m_data = nullptr;
	}
	return *this;
}