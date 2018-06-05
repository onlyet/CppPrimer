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