#include<string>
#include<initializer_list>

class StrVec {
public:
	StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec(std::initializer_list<std::string> il);
	StrVec(const StrVec&);
	StrVec(StrVec&&) noexcept;
	StrVec& operator=(const StrVec&);
	StrVec& operator=(StrVec&&) noexcept;
	StrVec& operator=(std::initializer_list<std::string>);
	~StrVec() { free(); }

	void push_back(const std::string&);
	void push_back(std::string&&);

	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	std::string* begin() const { return elements; }
	std::string* end() const { return first_free; }

	std::string& operator[](size_t n) { return elements[n]; }
	const std::string& operator[](size_t n) const { return elements[n]; }
	//重新分配内存，避免不必要的分配
	void reserve(size_t);
	void resize(size_t);
	void resize(size_t, const std::string&);

	void print();

private:
	//保证至少能分配一个元素，如果不能则调用reallocate
	void chk_n_alloc() { if (size() == capacity()) reallocate(); }
	//分配空间，并且拷贝给定范围元素到新分配的空间
	std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);	
	//销毁已构造的元素，并释放内存
	void free();
	//分配给定空间，并且移动
	void alloc_n_move(size_t new_cap);
	//空间不够的时候重新分配足够的内存
	void reallocate();

private:
	std::string* elements;	//首元素指针
	std::string* first_free;//尾后元素
	std::string* cap;		//分配的内存之后一个位置
	/*static*/ std::allocator<std::string> alloc;	//分配一块存放string的内存（类似vector<string>）
};