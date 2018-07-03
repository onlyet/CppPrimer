#pragma once
#include<iostream>
#include<regex>
#include<string>

using namespace std;

void ch17_3_1()
{
	string pattern("[^c]ei");
	pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
	regex r(pattern);
	smatch results;
	string test_str = "receipt freind theif receive";
	if (regex_search(test_str, results, r))
		cout << results.str() << endl;
}

bool valid(const smatch &m)
{
	if (m[1].matched) {
		return m[3].matched && (m[4].matched == 0 || m[4].str() == " ");
	}
	else {
		return !m[3].matched && m[4].str() == m[6].str();
	}
}

void ch17_3_3()
{
	//string phone = "(\\d{3})";
	//(\\d{4})
	//string phone = "(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{2})";

	string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";
	regex r(phone);
	smatch m;
	string s;
	s = "111-2222-3333, 123-134-2134";
	sregex_iterator a(s.begin(), s.end(), r);
	sregex_iterator b;
	if (a == b) {
		cout << "a == b" << endl;
	}
	else {
		cout << a->str() << endl;
	}
	//while (getline(cin, s)) {
	//	sregex_iterator it(s.begin(), s.end(), r), end_it;
	//	if (it == end_it) {
	//		cout << "string s do not match regex" << endl;
	//		continue;
	//	}
	//	for (; it != end_it; ++it) {
	//		if (valid(*it)) {
	//			cout << "valid: " << it->str() << endl;
	//		}
	//		else {
	//			cout << "not valid: " << it->str() << endl;
	//		}
	//	}
	//}
}