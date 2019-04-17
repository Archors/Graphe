#include "Coords.h"


Coords::Coords(double x, double y)
	:m_x{ x }, m_y{ y }
{}

const double Coords::getX() const
{
	return m_x;
}
const double Coords::getY() const
{
	return m_y;
}


Coords::~Coords()
{
}
