
///
///\file Coords.h
///
///\brief Declaration de la classe Coords
///\date 21 avril 2019
///

#ifndef COORDS_H_INCLUDED	
#define COORDS_H_INCLUDED

/**
 * \class Coords
 * \brief contient des coordonnes scalaires
 *
 * Renvoie ces coordonnes au besoin mais elles ne sont plus modifiables une fois initialisees
 * Valeurs stockees dans des doubles
 */
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