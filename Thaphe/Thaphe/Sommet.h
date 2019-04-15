#include <string>
#include "Coords.h"

class Sommet
{
private:
	std::string m_id;
	Coords m_coord;
public:
	Sommet();
	virtual ~Sommet();
};

