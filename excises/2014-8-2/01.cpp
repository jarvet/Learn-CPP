#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	const int MAX_CHARACTERS = 20;
	char student_name[MAX_CHARACTERS + 1];
	int student_number;
	cout << "Enter student number:";
	cin >> student_number;
	cout << "Enter student first name and surname(maximum" << MAX_CHARACTERS << " characters)";
	cin.ignore(80,'\n');
	cin.getline(student_name, MAX_CHARACTERS + 1);
	cout << endl << "Data Entered:" << endl << "Student Number:" << student_number << endl << "Student Name:" << student_name << endl;
	return 0;
}