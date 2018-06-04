#pragma once
#include<iostream>
#include<memory>
#include<algorithm>

#pragma warning( disable : 4996 )

namespace ch13_44 {
	class String {
	public:
		String() : beg(nullptr), end(nullptr) {}
		String(const char *str)
		{
			char *str_end = const_cast<char *>(str);
			while (*str_end) {
				++str_end;
			}
			//注意str_end要自增，指向空字符的尾后位置
			range_initializer(str, ++str_end);
		}
		String(const String &str)
		{
			range_initializer(str.beg, str.end);
		}
		String& operator=(const String &str)
		{
	/*		if (this != &str) {
				free();
				range_initializer(str.beg, str.end);
			}*/
			auto data = alloc_n_copy(str.beg, str.end);
			free();
			beg = data.first;
			end = data.second;

			return *this;
		}
		~String()
		{
			free();
		}
		const char *c_str() { return beg; }
		size_t size() { return end - beg; }
		size_t length() { end - beg - 1; }
	private:
		std::pair<char*, char*> alloc_n_copy(const char *b, const char *e)
		{
			//data是未初始化内存
			//uninitialized_copy想当于给未初始化内存data进行初始化，不要被名字误导
			auto data = alloc.allocate(e - b);
			return { data, std::uninitialized_copy(b, e, data) };
		}
		void range_initializer(const char *b, const char *e)
		{
			auto str = alloc_n_copy(b, e);
			beg = str.first;
			end = str.second;
		}
		void free()
		{
			if (beg) {
				std::for_each(beg, end, [this](char &c) {alloc.destroy(&c); });
				alloc.deallocate(beg, size());
			}
		}

	private:
		char *beg;
		char *end;
		std::allocator<char> alloc;
	};
}

