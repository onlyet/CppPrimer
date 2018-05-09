#include"str_vec.h"
#include<memory>


void StrVec::free()
{
	//销毁要从尾部开始,为什么要一个个元素销毁呢，要一个个的析构？
	if (elements) {
		for (auto beg = first_free; beg != elements; )
			alloc.destroy(--beg);
		alloc.deallocate(elements, capacity());
	}
}

//void StrVec::reallocate()
//{
//	size_t len = first_free - elements;
//	std::string* new_elem = alloc.allocate(size() ? 2 * size() : 1);
//	//alloc.construct(new_elem, )
//	std::copy(elements, first_free, new_elem);
//	free();
//	elements = new_elem;
//	first_free = new_elem + len;
//	cap = new_elem + 
//}

void StrVec::reallocate()
{
	auto new_cap = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(new_cap);
	auto elem = newdata;
	auto beg = elements;
	for (; beg != first_free; )
		alloc.construct(elem++, std::move(*beg++));
	free();
	elements = newdata;
	first_free = elem;
	cap = newdata + new_cap;
}

void StrVec::push_back(const std::string &s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
}

std::pair<std::string*, std::string*> 
StrVec::alloc_n_copy(const std::string *lhs, const std::string *rhs)
{
	std::string* new_elem = alloc.allocate(rhs - lhs);
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