#include "03.h"
using namespace std;

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