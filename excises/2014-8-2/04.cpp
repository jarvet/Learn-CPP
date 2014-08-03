#include <iostream>
#include <iomanip>
using namespace std;
class time24
{
public:
	time24(int h = 0, int m = 0, int s = 0);
	void set_time(int h, int m, int s);
	void get_time(int& h, int& m, int& s) const;
	time24 operator+(int secs) const;
	time24 operator+(const time24& t) const;
	time24& operator++();
	time24 operator++(int);
	bool operator==(const time24& t) const;
	operator int();
private:
	int hours;
	int minutes;
	int seconds;
};

time24::time24(int h, int m, int s): hours(h), minutes(m), seconds(s) {}

void time24::set_time(int h,int m, int s)
{
	hours = h;
	minutes = m;
	seconds = s;
}

void time24::get_time(int& h, int& m, int& s) const
{
	h = hours;
	m = minutes;
	s = seconds;
}

time24 time24::operator+(int secs) const
{
	time24 temp;
	temp.seconds = seconds + secs;
	temp.minutes = minutes + temp.seconds / 60;
	temp.seconds %= 60;
	temp.hours = hours + temp.minutes / 60;
	temp.minutes %= 60;
	temp.hours %= 24;
	return temp;
}

time24 time24::operator+(const time24& t) const
{
	time24 temp;
	int secs = t.hours * 3600 + t.minutes * 60 + t.seconds;
	temp.seconds = seconds + secs;
	temp.minutes = minutes + temp.seconds / 60;
	temp.seconds %= 60;
	temp.hours = hours + temp.minutes / 60;
	temp.minutes %= 60;
	temp.hours %= 24;
	return temp;
}

time24 operator+(int secs, const time24& t)
{
	time24 temp;
	temp = t + secs;
	return temp;
}

time24& time24::operator++()
{
	*this = *this + 1;
	return *this;
}

time24 time24::operator++(int)
{
	time24 temp;
	temp = *this;
	*this = *this + 1;
	return temp;
}

bool time24::operator==(const time24& t) const
{
	if (hours == t.hours && minutes == t.minutes && seconds == t.seconds)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ostream& operator<<(ostream& os, const time24& t)
{
	int h, m, s;
	t.get_time(h, m, s);
	os<< setfill('0')
	<< setw(2) << h << ":"
	<< setw(2) << m << ":"
	<< setw(2) << s << endl;
	return os;
}

istream& operator>>(istream& is, time24& t)
{
	int h, m, s;
	do
	{
		is >> h;
	}
	while(h < 0 || h > 23);
	is.ignore(1);
	do
	{
		is >> m;
	}
	while(m < 0 || m > 60);
	is.ignore(1);
	do
	{
		is >> s;
	}
	while(s < 0 || s > 60);
	t.set_time(h, m, s);
	return is;
}

time24::operator int()
{
	int no_of_seconds = hours * 3600 + minutes * 60 + seconds;
	return no_of_seconds;
}

int main(int argc, char const *argv[])
{
	time24 t(1, 2, 3);
	int s;
	s = t;
	cout << "Time = " << t << "Equivalent number of seconds = " << s <<endl;
	return 0;
}

// int main(int argc, char const *argv[])
// {
// 	time24 t1(1, 2, 3);
// 	time24 t2(10, 10, 10);
// 	cout << t1 << t2;
// 	time24 t3;
// 	cin >> t3;
// 	cout << t3;
// 	return 0;
// }

// int main(int argc, char const *argv[])
// {
// 	int h, m, s;
// 	time24 t1(23, 59, 57);
// 	time24 t2;
// 	t2 = t1++;
// 	t1.get_time(h, m, s);
// 	cout << "Using postfix ++:" << "time t1 is:" << h << ":" << m << ":" << s;
// 	t2.get_time(h, m, s);
// 	cout << ", time t2 is: " << h << ":" << m << ":" << s << endl;
// 	t1.set_time(23, 59, 57);
// 	t2 = ++t1;
// 	t1.get_time(h, m, s);
// 	cout << "Using prefix ++:" << "time t1 is:" << h << ":" << m << ":" << s;
// 	t2.get_time(h, m, s);
// 	cout << ", time t2 is:" << h << ":" << m << ":" << s << endl;
// 	if (t1 == t2)
// 	{
// 		cout << "t1 and t2 are equal.Prefix ++ is working." << endl;
// 	}
// 	else
// 	{
// 		cout << "t1 and t2 are not equal. Prefix ++ is not working." << endl;
// 	}
// 	return 0;
// }