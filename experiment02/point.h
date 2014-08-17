#if !defined  CPP_2014_POINT
#define CPP_2014_POINT

using namespace std;

class Point
{
	public:
	Point(double x = 0.0, double y = 0.0);
	~Point();
	double get_x();
	double get_y();
	void set_x(double new_x);
	void set_y(double new_y);
	virtual void DisplayPoint();

	protected:
	double m_x;
	double m_y;
};

#endif