#pragma once
#include<iostream>
#include<regex>
#include<string>

#include<random>
#include<fstream>

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
	//string phone = "\\d[ ]*\\d";
	string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";
	regex r(phone);
	smatch m;
	string s;
	string fmt = "$2.$5.$7";

	//s = "111-2222-3333, 123-134-2134";
	//sregex_iterator a(s.begin(), s.end(), r);
	//sregex_iterator b;
	//if (a == b) {
	//	cout << "a == b" << endl;
	//}
	//else {
	//	cout << a->str() << endl;
	//}

	while (getline(cin, s)) {
		sregex_iterator it(s.begin(), s.end(), r), end_it;
		if (it == end_it) {
			cout << "string s do not match regex" << endl;
			continue;
		}
		for (; it != end_it; ++it) {
			if (valid(*it)) {
				//cout << it->length(7) << endl;
				cout << "valid: [" << it->str() << "]" << endl;
				cout << regex_replace(s, r, fmt) << endl;
			}
			else {
				cout << it->size() << endl;
				cout << "not valid: " << it->str() << endl;
			}
		}
	}
}

void ch_17_4_2()
{
	default_random_engine e;
	normal_distribution<> n(4, 1.5);
	vector<unsigned> vals(9);
	for (size_t i = 0; i != 200; ++i) {
		unsigned v = lround(n(e));
		if (v < vals.size()) {
			++vals[v];
		}
	}
	for (size_t j = 0; j != vals.size(); ++j) {
		cout << j << ": " << string(vals[j], '*') << endl;
	}
}

//为什么最后一行的cnt没有写到end

int ch_17_5()
{
	fstream inOut("copyOut.txt", fstream::ate | fstream::in | fstream::out | fstream::binary);
	if (!inOut) {
		cerr << "Unable to open file!" << endl;
		return EXIT_FAILURE;
	}
	auto end_mark = inOut.tellg();
	inOut.seekg(0, fstream::beg);
	size_t cnt = 0;
	string line;
	while (inOut && inOut.tellg() != end_mark
		&& getline(inOut, line)) {
		cnt += line.size() + 1;
		auto mark = inOut.tellg();
		inOut.seekp(0, fstream::end);
		inOut << cnt;
		if (mark != end_mark) {
			inOut << " ";
		}
		inOut.seekg(mark);
	}
	inOut.seekp(0, fstream::end);
	inOut << "\n";
	return 0;
}