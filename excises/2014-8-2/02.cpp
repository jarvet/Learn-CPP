#include <iostream>
#include <string>
using namespace std;
int main(int argc, char const *argv[])
{
	string str1 = "ABCDEFGHI";
	string str2(11,'-');
	string str3 = "This is the first part"
	              "and this is the second part";
	string str4 = str2;
	string str5;
	cout << "After initialisations:" << endl
	<< " str1=" << str1 << endl
	<< " str2=" << str2 << endl
	<< " str3=" << str3 << endl
	<< " str4=" << str4 << endl
	<< " str5=" << str5 << endl;
	str1 = "ABCD";
	str2.assign(3,'.');
	cout << "After the 1st and 2nd assignments:" << endl
	<< " str1=" << str1 << endl
	<< " str2=" << str2 << endl;
	str5.assign(str1,1,3);
	cout << "After the 3rd assignments:" << endl
	<< " str5=" << str5 << endl;
	cout << "Before swapping str1 and str2:" << endl
	<< " str1=" << str1 << endl
	<< " str2=" << str2 << endl;
	str1.swap(str2);
	cout << "After swapping str1 and str2:" << endl
	<< " str1=" << str1 << endl
	<< " str2=" << str2 << endl;
	return 0;
}