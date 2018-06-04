#pragma once
#include<string>

class HasPtr {
public:
	HasPtr(HasPtr &&p)	noexcept : ps(p.ps), i(p.i) { p.ps = 0; }
	//rhs非引用，进行拷贝初始化，如果实参是左值调用拷贝构造函数，是右值则调用移动构造函数
	//优点：拷贝初始化时：既可以调用拷贝构造函数，又可以调用移动构造函数
	HasPtr& operator=(HasPtr rhs) { std::swap(*this, rhs);  return *this; }

private:
	std::string *ps;
	int i;
};
