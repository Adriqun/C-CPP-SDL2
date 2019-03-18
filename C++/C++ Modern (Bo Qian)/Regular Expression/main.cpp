#include <iostream>
#include <regex>
using namespace std;

// Example 1
/*int main()
{
	string str;
	while (true) {
		cin >> str;
		regex a("abc.", regex_constants::icase); // . any character except new line
		regex b("abc?"); // Zero or 1 preceding character
		regex c("abc*"); // Zero or more preceding characters
		regex d("abc+"); // One or more preceding characters
		regex e("a[bc]*"); // Any character inside the [...]
		regex f("ab[^cd]*"); // Any character not inside the [...]
		regex g("ab[cd]{3}"); // Exact 3 appearences of preceding rule ([cd])
		regex h("ab[cd]{3,}"); // Exact 3 or more appearences of preceding rule ([cd])
		regex i("ab[cd]{3,}"); // Exact 3-5 appearences of preceding rule ([cd])
		regex j("abc|d[ef]"); // | means "or"
		regex k("(abc)|de+\\1"); // (...) <- group 1, \\1 <- will be replaced with 1 group
		regex l("(abc)c(de+)\\2\\1"); // Use with 2 groups
		regex m("[[:w:]]+@[[:w:]]+\.com"); // [[:w:]] word character: digit, number, or underscore

		// regex_search(str, a); // cares about substring
		cout << "\"abc.\" " << (regex_match(str, a) ? "Matched" : "Not matched") << std::endl;
		cout << "\"abc?\" " << (regex_match(str, b) ? "Matched" : "Not matched") << std::endl;
		cout << "\"abc*\" " << (regex_match(str, c) ? "Matched" : "Not matched") << std::endl;
		cout << "\"abc+\" " << (regex_match(str, d) ? "Matched" : "Not matched") << std::endl;
		cout << "\"a[bc]*\" " << (regex_match(str, e) ? "Matched" : "Not matched") << std::endl;
		cout << "\"ab[^cd]*\" " << (regex_match(str, f) ? "Matched" : "Not matched") << std::endl;
		cout << "\"ab[cd]{3}\" " << (regex_match(str, g) ? "Matched" : "Not matched") << std::endl;
		cout << "\"ab[cd]{3,}\" " << (regex_match(str, h) ? "Matched" : "Not matched") << std::endl;
		cout << "\"ab[cd]{3,5}\" " << (regex_match(str, i) ? "Matched" : "Not matched") << std::endl;
		cout << "\"abc|d[ef]\" " << (regex_match(str, j) ? "Matched" : "Not matched") << std::endl;
		cout << "\"(abc)|de+\\1\" " << (regex_match(str, k) ? "Matched" : "Not matched") << std::endl;
		cout << "\"(abc)c(de+)\\2\\1\" " << (regex_match(str, l) ? "Matched" : "Not matched") << std::endl;
		cout << "\"[[:w:]]+@[[:w:]]+\.com\" " << (regex_match(str, m) ? "Matched" : "Not matched") << std::endl;
	}
	
	return 0;
}*/

// Example 2
/*int main()
{
	string str;
	while (true) {
		cin >> str;

		smatch _smatch;
		regex m("([[:w:]]+)@([[:w:]]+)\.com");
		bool mbool = regex_match(str, _smatch, m);

		cout << "\"[[:w:]]+@[[:w:]]+\.com\" " << (mbool ? "Matched" : "Not matched") << std::endl;
		cout << "_smatch.size() = " << _smatch.size() << endl;
		for (int n = 0; n < _smatch.size(); ++n)
			cout << "_smatch[" << n << "]: str() = " << _smatch[n].str() << endl;

		cout << "_smatch.prefix() = " << _smatch.prefix() << endl;
		cout << "_smatch.suffix() = " << _smatch.prefix() << endl;
	}

	return 0;
}*/

// Example 3
// Regex Iterator
/*int main()
{
	string str = "boq@gmail.com;	boqian@hotmai.com;;		bo_qian2000@163.com";
	regex e("([[:w:]]+)@([[:w:]]+)\.com");
	sregex_iterator pos(str.cbegin(), str.cend(), e);
	sregex_iterator end; // default constructor defines past-the-end iterator
	for (; pos != end; ++pos) {
		cout << "Matched: " << pos->str(0) << endl;
		cout << "User name: " << pos->str(1) << endl;
		cout << "Domain: " << pos->str(2) << endl;
		cout << endl;
	}
	cout << "---\n";
	cin >> str;
}*/

// Example 4
// Regex Token Iterator
int main()
{
	string str = "boq@gmail.com;	boqian@hotmai.com;;		bo_qian2000@163.com";
	regex e("([[:w:]]+)@([[:w:]]+)\.com");
	sregex_token_iterator pos(str.cbegin(), str.cend(), e, 1); // 0, 1, 2 or -1 -> part which is not extracted
	sregex_token_iterator end; // default constructor defines past-the-end iterator
	for (; pos != end; ++pos) {
		cout << "Matched: " << pos->str() << endl;
		cout << endl;
	}
	cout << "---\n";
	cin >> str;
}