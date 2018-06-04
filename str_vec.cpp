#include"str_vec.h"
#include<memory>
#include<algorithm>

#pragma warning( disable : 4996 )
//#define D_SCL_SECURE_NO_WARNINGS

//alloc可能有多块已经分配的内存，所以我们怎么释放某个内存块呢？
//三个指针用于释放对应的内存
//销毁元素（析构）: 使用first_free，elements
//释放内存: 使用cap，elements
void StrVec::free()
{
	//if (elements) {
	//	for (auto beg = first_free; beg != elements; )
	//		alloc.destroy(--beg);
	//	alloc.deallocate(elements, capacity());
	//}
	//rewrite
	if (elements) {
		std::for_each(elements, first_free, [this](std::string &s) {alloc.destroy(&s); });
		alloc.deallocate(elements, capacity());
	}
}

//std::move(*beg)调用移动构造函数，所以在free()的时候，原对象逐个元素destory，
//讲道理应该没有调用析构函数，因为原string在移动构造的时候已经被置为nullptr了
//可以肯定的是string只存在移动不存在拷贝
void StrVec::alloc_n_move(size_t new_cap)
{
	auto newdata = alloc.allocate(new_cap);
	auto elem = newdata;
	auto beg = elements;
	for (; beg != first_free; )
		alloc.construct(elem++, std::move(*beg++));
	free();	//destory原对象并且释放原内存，但是由于std::move析构函数没有调用
	elements = newdata;
	first_free = elem;
	cap = newdata + new_cap;
}

void StrVec::reallocate()
{
	auto new_cap = size() ? 2 * size() : 1;
	alloc_n_move(new_cap);
}

void StrVec::push_back(const std::string &s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
}

void StrVec::push_back(const std::string &&s)
{
	chk_n_alloc();
	alloc.construct(first_free++, std::move(s));
}

std::pair<std::string*, std::string*> 
StrVec::alloc_n_copy(const std::string *lhs, const std::string *rhs)
{
	std::string* new_elem = alloc.allocate(rhs - rhs);
	return { new_elem, std::uninitialized_copy(lhs, rhs, new_elem) };	//uninitialized_copy:返回最后一个构造的元素之后的位置
}

StrVec::StrVec(const StrVec &rhs)
{
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	elements = data.first;
	first_free = cap = data.second;
}

StrVec& StrVec::operator=(const StrVec &rhs)
{
	//不用考虑自赋值的情况，因为实现是先拷贝再释放内存
	//if (this == &rhs) {
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	//}
	return *this;
}

StrVec::StrVec(std::initializer_list<std::string> il) 
{
	auto data = alloc_n_copy(il.begin(), il.end());
	elements = data.first;
	first_free = cap = data.second;
}

StrVec::StrVec(StrVec &&rhs) noexcept 
	: elements(rhs.elements), first_free(rhs.first_free), cap(rhs.cap)
{
	rhs.elements = rhs.first_free = rhs.cap = nullptr;
}

StrVec& StrVec::operator=(StrVec &&rhs) noexcept
{
	if (this != &rhs) {
		free();
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

StrVec& StrVec::operator=(std::initializer_list<std::string> il)
{
	free();
	auto data = alloc_n_copy(il.begin(), il.end());
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

void StrVec::reserve(size_t new_cap)
{
	if (new_cap <= capacity()) {
		return;
	}
	alloc_n_move(new_cap);
}

void StrVec::resize(size_t new_cap)
{
	resize(new_cap, std::string());
}

void StrVec::resize(size_t new_cap, const std::string &s)
{
	if (new_cap > size()) {
		if (new_cap > capacity()) {
			reserve(new_cap);
		}
		for (auto beg = size(); beg != new_cap;) {
			alloc.construct(first_free++, s);
		}
	}	
	//只需要销毁元素，不许释放内存块alloc
	//销毁元素从后往前递减first_free
	else {
		while (first_free != elements + new_cap)
			alloc.destroy(--first_free);
	}
}