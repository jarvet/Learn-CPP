#if !defined  CPP_2014_POINT3D
#define CPP_2014_POINT3D

#include "point.h"

class Point3D :public Point
{
	public:
	Point3D(double x = 0.0, double y = 0.0, double z = 0.0);
	~Point3D();
	void set_z(double new_z);
	double get_z();
	virtual void DisplayPoint();
	bool operator==(Point3D point) const;

	protected:
	double m_z;
};

#endif