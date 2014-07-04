#include <iostream>

using namespace std;

class Time
{
	public:
	Time(int hour = 0, int minute = 0, int second = 0);
	void setHour(int hour);
	void setMinute(int minute);
	void setSecond(int second);
	int getHour();
	int getMinute();
	int getSecond();
	private:
	int _hour;
	int _minute;
	int _second;
};

Time::Time(int hour, int minute, int second)
{
	this->setHour(hour);
	this->setMinute(minute);
	this->setSecond(second);
}

void Time::setHour(int hour)
{
	if (hour < 0 || hour > 23)
	{
		throw new exception("error:hour should be between 0 and 23.");
	}
	_hour = hour;
}

void Time::setMinute(int minute)
{
	if (minute < 0 || minute > 59)
	{
		throw new exception("error:minute should be between 0 and 59.");
	}
	_minute = minute;
}

void Time::setSecond(int second)
{
	if (second < 0 || second > 59)
	{
		throw new exception("error:second should be between 0 and 59.");
	}
	_second = second;
}

int Time::getHour()
{
	return _hour;
}

int Time::getMinute()
{
	return _minute;
}

int Time::getSecond()
{
	return _second;
}

class Date
{
	public:
	Date(int year = 1970, int month = 1, int day = 1);
	void setYear(int year);
	void setMonth(int month);
	void setDay(int day);
	int getYear();
	int getMonth();
	int getDay();
	int isLeapYear();
	private:
	int _year;
	int _month;
	int _day;
};

Date::Date(int year, int month, int day)
{
	this->setYear(year);
	this->setMonth(month);
	this->setDay(day);
}

void Date::setYear(int year)
{
	if (year <= 0)
	{
		throw new exception("error:year should not be minus.");
	}
	_year = year;
}

void Date::setMonth(int month)
{
	if (month < 1 || month > 12)
	{
		throw new exception("error:month should be between 1 and 12.");
	}
	_month = month;
}

void Date::setDay(int day)
{
	switch (_month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (day < 1 || day > 31)
			{
				throw new exception("error:day should be between 1 and 31.");
			}
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			if (day < 1 || day > 30)
			{
				throw new exception("error:day should be between 1 and 30.");
			}
			break;
		case 2:
			if (this->isLeapYear())
			{
				if (day < 1 || day > 29)
				{
					throw new exception("error:day should be between 1 and 29.");
				}
			}
			else
			{
				if (day < 1 || day > 28)
				{
					throw new exception("error:day should be between 1 and 28.");
				}
			}
			break;
		default:
			throw new exception();
			break;
	}
	_day = day;
}

int Date::getYear()
{
	return _year;
}

int Date::getMonth()
{
	return _month;
}

int Date::getDay()
{
	return _day;
}

int Date::isLeapYear()
{
	if (((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

class DateTime
{
	public:
	DateTime(int year = 1970, int month = 1, int day = 1, int hour = 0, int minute = 0, int second = 0);
	Date date;
	Time time;
};

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
{
	date.setYear(year);
	date.setMonth(month);
	date.setDay(day);
	time.setHour(hour);
	time.setMinute(minute);
	time.setSecond(second);
}

int main(int argc, char const *argv[])
{
	int choice;
	int t1, t2, t3, t4, t5, t6;
	cout << "please input the year, month, day, hour, minute and second.(split by space):";
	cin >> t1 >> t2 >> t3 >> t4 >> t5 >> t6;
	DateTime o(t1, t2, t3, t4, t5, t6);
	while (1)
	{
		cout << "1.set Date of the object;" << endl << "2.set Time of the object;" << endl << "3.show the object;" << endl << "please input your choice:";
		cin >> choice;
		try
		{
			switch (choice)
			{
				case 1:
					cout << "pelase input the year, month and day you want set:";
					cin >> t1 >> t2 >> t3;
					o.date.setYear(t1);
					o.date.setMonth(t2);
					o.date.setDay(t3);
					break;
				case 2:
					cout << "please input the hour, minute and second:";
					cin >> t4 >> t5 >> t6;
					o.time.setHour(t4);
					o.time.setMinute(t5);
					o.time.setSecond(t6);
					break;
				case 3:
					cout << o.date.getYear() << "-" << o.date.getMonth() << "-" << o.date.getDay() << " " << o.time.getHour() << ":" << o.time.getMinute() << ":" << o.time.getSecond() << endl;
					break;
				default:
					cout << "Input error!";
					break;
			}
		}
		catch (exception *e)
		{
			cout << e->what() << endl;
		}
	}
	return 0;
}