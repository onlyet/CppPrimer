#pragma once
#include<iostream>
#include<string>

class HasPtr {
public:
	friend void swap(HasPtr&, HasPtr&);
	HasPtr(const std::string &s = std::string());
	HasPtr(const HasPtr &hp);
	HasPtr(HasPtr &&hp) noexcept;
	//rhs非引用，进行拷贝初始化，如果实参是左值调用拷贝构造函数，是右值则调用移动构造函数
	//优点：拷贝初始化时：既可以调用拷贝构造函数，又可以调用移动构造函数
	HasPtr& operator=(HasPtr rhs);
	//HasPtr& operator=(HasPtr &&rhs) noexcept;
	~HasPtr();
private:
	std::string *ps;
	int i;
};

void swap(HasPtr &lhs, HasPtr &rhs)
{
	std::swap(lhs.ps, rhs.ps);
	std::swap(lhs.i, rhs.i);
}

HasPtr::HasPtr(const std::string &s) : ps(new std::string(s)), i(0)
{
	std::cout << "ctor: " << *ps << std::endl;
}

HasPtr::HasPtr(const HasPtr &hp) : ps(new std::string(*hp.ps)), i(hp.i)
{
	std::cout << "copy ctor: " << *ps << std::endl;
}

HasPtr::HasPtr(HasPtr && hp) noexcept : ps(hp.ps), i(hp.i)
{
	hp.ps = nullptr;
	std::cout << "move ctor: " << *ps << std::endl;
}

HasPtr& HasPtr::operator=(HasPtr rhs)
{
	std::cout << "before assignment: " << *ps << std::endl;
	swap(*this, rhs);
	std::cout << "after assignment: " << *ps << std::endl;
	return *this;
}

//HasPtr& HasPtr::operator=(HasPtr &&rhs) noexcept
//{
//	std::cout << "before assignment" << *ps << std::endl;
//	if (this != &rhs) {
//	/*	delete ps;
//		swap(*this, rhs);*/
//		delete ps;
//		ps = rhs.ps;
//		i = rhs.i;
//		rhs.ps = nullptr;
//		std::cout << "after assignment" << *ps << std::endl;
//	}
//	return *this;
//}

HasPtr::~HasPtr()
{
	std::cout << "dtor: ";
	if (ps) {
		std::cout << *ps << std::endl;
		delete ps;
	}
}