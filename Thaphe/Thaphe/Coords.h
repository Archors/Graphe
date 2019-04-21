#ifndef COORDS_H_INCLUDED	
#define COORDS_H_INCLUDED

#pragma once
class Coords
{
public:
	//Coords(int x, int y);
	Coords(double x, double y);
	const double getX() const;
	const double getY() const;
	~Coords();
private:
	double m_x;
	double m_y;
};

#endif // COORDS_H_INCLUDED