#include "Sommet.h"


Sommet::Sommet(std::string id, double x, double y)
	:m_id{ id }, m_coords{ x, y }
{
}

void Sommet::AjouterVoisin(const Sommet* som, const Arete* ar)
{
	std::cout << "nouveu voisin\n";
}


Sommet::~Sommet()
{
}



Arete::Arete(/*std::string id, Sommet* s1, Sommet* s2, std::vector<float> poids, bool oriente*/)

{
	std::cout << "Nouvelle arete\n";
}


Arete::~Arete()
{
}