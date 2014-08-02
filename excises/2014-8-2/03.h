using namespace std;
class time24
{
public:
	time24(int h = 0, int m = 0, int s = 0);

	void set_time(int h = 0,int m = 0,int s = 0);
	void get_time(int& h, int& m, int& s) const;
	time24 operator+(int secs) const;
	time24 operator+(const time24& t) const;
private:
	int hours;
	int minutes;
	int seconds;
};