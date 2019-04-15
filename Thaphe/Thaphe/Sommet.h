#ifndef SOMMET_H_INCLUDED	
#define SOMMET_H_INCLUDED

#pragma
#include "Coords.h"
#include <string>

class Sommet 
{
	private:
		std::string m_id;
		Coords m_coord;
	public:
		Sommet();
		virtual ~Sommet();
};

#endif // SOMMET_H_INCLUDED