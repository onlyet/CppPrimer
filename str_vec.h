#include<string>

class StrVec {
public:
	StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec(std::initializer_list<std::string>);
	StrVec(const StrVec&);
	StrVec& operator=(const StrVec&);
	StrVec(StrVec&&);
	StrVec& operator=(StrVec&&);
	~StrVec() { free(); }

	void push_back(const std::string&);


	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	std::string* begin() const { return elements; }
	std::string* end() const { return first_free; }

private:
	//保证至少能分配一个元素，如果不能则调用reallocate
	void chk_n_alloc() { if (size() == capacity()) reallocate(); }
	//分配空间，并且拷贝给定范围元素
	std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);	
	//销毁已构造的元素，并释放内存
	void free();
	//空间不够的时候重新分配足够的内存
	void reallocate();

private:
	std::string* elements;	//首元素指针
	std::string* first_free;//最后一个元素元素之后的位置
	std::string* cap;		//内配的内存之后一个位置
	static std::allocator<std::string> alloc;	//分配一块存放string的内存（类似vector<string>）
};