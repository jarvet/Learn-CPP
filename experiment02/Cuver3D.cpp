#include <iostream>
#include <iomanip>
#include <fstream>
#include "Curve3D.h"

using namespace std;

double LenOfTwoPoints(Point3D a, Point3D b)
{
	return sqrt((a.get_x() - b.get_x()) * (a.get_x() - b.get_x()) + (a.get_y() - b.get_y()) * (a.get_y() - b.get_y()) + (a.get_z() - b.get_z()) *(a.get_z() - b.get_z()));
}

Curve3D::Curve3D(Point3D point)
{
	NODE *temp = new NODE;
	temp->next = NULL;
	temp->point = point;
	head = temp;
	tail = temp;
	num = 1;
}

Curve3D::~Curve3D()
{
	NODE *temp = head;
	NODE *t = NULL;
	while (temp != NULL)
	{
		t = temp->next;
		delete temp;
		temp = t;
	}
}

void Curve3D::DisplayCurve()
{
	NODE *temp = head;
	while (temp != NULL)
	{
		printf("(%.2lf, %.2lf, %.2lf)\n", temp->point.get_x(), temp->point.get_y(), temp->point.get_z());
		temp = temp->next;
	}
}

void Curve3D::CurveLen()
{
	double sum = 0;
	NODE *temp = head;
	while (temp->next != NULL)
	{
		sum += LenOfTwoPoints(temp->point, temp->next->point);
		temp = temp->next;
	}
	cout << "The lenth of the curve is: " << fixed << setprecision(2) << sum << endl;
}

const Curve3D& Curve3D::operator=(const Curve3D& curve)
{
	if (this != &curve)
	{
		num = curve.num;
		NODE *temp = new NODE;
		head = temp;
		NODE *cur_temp = curve.head;
		while (cur_temp != NULL)
		{
			temp->point = cur_temp->point;
			if (cur_temp->next != NULL)
			{
				temp->next = new NODE;
			}
			else
			{
				temp->next = NULL;
				tail = temp;
			}
			temp = temp->next;
			cur_temp = cur_temp->next;
		}
	}
	return *this;
}

Curve3D Curve3D::operator+(Point3D point) const
{
	NODE *temp = new NODE;
	temp->point = point;
	temp->next = NULL;
	Curve3D *temp_curve = new Curve3D;
	*temp_curve = *this;
	temp_curve->num += 1;
	temp_curve->tail->next = temp;
	temp_curve->tail = temp;
	return *temp_curve;
}

Curve3D Curve3D::operator-(Point3D point) const
{
	Curve3D *temp = new Curve3D;
	*temp = *this;
	NODE *temp_node = temp->head;
	if (head->point == point)
	{
		temp->head = temp->head->next;
		delete temp_node;
	}
	else
	{
		while (temp_node->next != NULL)
		{
			if (temp_node->next->point == point)
			{
				NODE *temp_del = temp_node->next;
				temp_node->next = temp_del->next;
				delete temp_del;
				break;
			}
			else
			{
				temp_node = temp_node->next;
			}
		}
	}
	return *temp;
}

void Curve3D::write_txt(ofstream &tos)
{
	NODE *temp = head;
	while (temp != NULL)
	{
		tos << temp->point.get_x() << " " << temp->point.get_y() << " " << temp->point.get_z() << endl;
		temp = temp->next;
	}
}

void Curve3D::read_txt(ifstream &tis)
{
	double x, y, z;
	while (!tis.eof())
	{
		tis >> x >> y >> z;
		*this = *this + Point3D(x, y, z);
	}
}

void Curve3D::write_bin(ofstream &bos)
{
	NODE *temp = head;
	while (temp != NULL)
	{
		bos << temp->point.get_x() << " " << temp->point.get_y() << " " << temp->point.get_z() << endl;
		temp = temp->next;
	}
}

void Curve3D::read_bin(ifstream &bis)
{
	double x, y, z;
	while (!bis.eof())
	{
		bis >> x >> y >> z;
		*this = *this + Point3D(x, y, z);
	}
}