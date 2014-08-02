#include <iostream>
#include "03.cpp"

int main(int argc, char const *argv[])
{
	int h, m, s;
	time24 start_time(23, 0, 0);
	time24 elapsed_time(1, 2, 3);
	time24 finish_time;
	finish_time = start_time + elapsed_time;
	finish_time.get_time(h, m, s);
	cout << "Finish Time is " << h << ":" << m << ":" << s << endl;
	return 0;
}