#if !defined  CPP_2014_Curve3D
#define CPP_2014_Curve3D

#include "Point3D.h"
using namespace std;

typedef struct node
{
	Point3D point;
	struct node *next;
} NODE;

class Curve3D
{
	public:
	Curve3D(Point3D point = Point3D(0, 0, 0));
	~Curve3D();
	void DisplayCurve();
	void CurveLen();
	const Curve3D& operator=(const Curve3D& curve);
	Curve3D operator+(Point3D point) const;
	Curve3D operator-(Point3D point) const;
	void write_txt(ofstream &tos);
	void read_txt(ifstream &tis);
	void write_bin(ofstream &bos);
	void read_bin(ifstream &bis);

	private:
	NODE *head;
	NODE *tail;
	int num;
};

#endif