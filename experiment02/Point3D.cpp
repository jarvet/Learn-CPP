#include <iostream>
#include "Point3D.h"

Point3D::Point3D(double x, double y, double z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

Point3D::~Point3D()
{}

double Point3D::get_z()
{
	return m_z;
}

void Point3D::set_z(double new_z)
{
	m_z = new_z;
}

void Point3D::DisplayPoint()
{
	cout << "The point is: " << "(" << m_x << ", " << m_y << ", " << m_z << " )" << endl;
}

bool Point3D::operator==(Point3D point) const
{
	if (m_x == point.get_x() && m_y == point.get_y() && m_z == point.get_z())
	{
		return true;
	}
	else
	{
		return false;
	}
}