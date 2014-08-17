#include <iostream>
#include "point.h"

Point::Point(double x, double y)
{
	m_x = x;
	m_y = y;
}

Point::~Point()
{}

double Point::get_x()
{
	return m_x;
}

double Point::get_y()
{
	return m_y;
}

void Point::set_x(double new_x)
{
	m_x = new_x;
}

void Point::set_y(double new_y)
{
	m_y = new_y;
}

void Point::DisplayPoint()
{
	cout << "The point is: " << "(" << m_x << ", " << m_y << " )" << endl;
}