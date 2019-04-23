
///
///\file Coords.cpp
///
///\brief Definition des méthodes de la classe coords
///\date 21 avril 2019
///

#include "Coords.h"

/**
 * \fn Coords::Coords (double x, double y)
 * \brief Constructeur de la classe
 *
 */
Coords::Coords(double x, double y)
	:m_x{ x }, m_y{ y }
{}

/**
 * \fn const double Coords::getX () const
 * \brief Renvoie la coordonee x
 *
 */
const double Coords::getX() const
{
	return m_x;
}

/**
 * \fn const double Coords::getY () const
 * \brief Renvoie la coordonee y
 *
 */
const double Coords::getY() const
{
	return m_y;
}


Coords::~Coords()
{
}
