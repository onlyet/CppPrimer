#include<string>

class String {
public:
	String(const char* s = nullptr);
	String(const String&);
	String(String&&) noexcept;
	String& operator=(const String&);
	String& operator=(String&&) noexcept;
	~String();

	size_t size() const { return strlen(m_data); }
	//const char* begin() const { return m_data[0]; }
	//char* end();
	const char* c_str() const { return m_data; }

	//不检查越界
	char& operator[](size_t n) { return *(m_data + n); }
	const char& operator[](size_t n) const { return *(m_data + n); }
	char& at(size_t n);

	bool operator==(const String& rhs) { return !strcmp(m_data, rhs.m_data); }
	bool operator!=(const String& rhs) { return strcmp(m_data, rhs.m_data); }
	String operator+(const String& rhs);
	String& operator+=(const String& rhs);

	String substr(size_t pos, size_t count);

private:
	char* m_data;
};
