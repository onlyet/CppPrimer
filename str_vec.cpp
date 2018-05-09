#include"str_vec.h"

void StrVec::free()
{
	//销毁要从尾部开始,为什么要一个个元素销毁呢，要一个个的析构？
	if (elements) {
		for (auto beg = first_free; beg != elements; )
			alloc.destroy(--beg);
		alloc.deallocate(elements, capacity());
	}
}

void StrVec::reallocate()
{
	std::string* new_elem = alloc.allocate(size() ? 2 * size() : 1);
		
}

void StrVec::push_back(const std::string &s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
}