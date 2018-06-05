#include"string_.h"
#include"HasPtr.h"
#include"str_vec.h"
#include"17_3_1.h"

#include<iostream>
#include <utility>
#include <vector>

using namespace std;

String foo()
{
	return String("five");
}

//int main()
//{
//	{
//		//String s0;
//		//String s1("one");
//		//String s2 = "two";
//		//String s3(s1);
//		//String s4 = s1;
//		//s3 = s1;
//
//		//String s5 = String("three");
//		//String s6 = (String)"four";
//		//String s7 = foo();
//		//s5 = String("six");
//		////s7 = foo();	//为什么报错
//
//		//String s8(String("seven"));
//		//String s9 = std::move(s1);	//move之后s1就变为空了，不能再调用了
//		//cout << s1.c_str() << endl;
//		//String s10(std::move(s2));
//		//s8 = std::move(s3);
//
//		String s11(std::move(String()));
//
//		//vector<int> v{ 1,2,3 };
//		//vector<int> v2 = std::move(v);
//
//		//const char *p = "abc";
//		//cout << *p << endl;
//	}
//	system("pause");
//	return 0;
//}

void has_ptr_tt()
{
	HasPtr hp("hello");
	HasPtr hp2("world");
	hp = std::move(hp2);
}

void str_vec_tt()
{
	StrVec sv({ "hello", "world" });
	string str("!!");
	//sv.push_back(std::move("!!"));
	sv.push_back(str);
	sv.print();
}

int main()
{
	{
		//has_ptr_tt();
		//str_vec_tt();

		ch17_3_1();
	}
	system("pause");
	return 0;
}