

class String {
public:
	String(const char* s = "");
	String(const String&);
	String& operator=(const String&);
	String(String&&);
	String& operator=(String&&);
	~String();
private:
	char* m_data;
};
