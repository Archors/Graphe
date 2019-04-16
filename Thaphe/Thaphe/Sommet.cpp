#include "Sommet.h"

Sommet::Sommet(std::string id, double x, double y)
	:m_id{id},m_coords{x,y}
{}


void Sommet::AjouterVoisin(const Sommet* som, Arete* ar)
{
	m_voisins.insert({ som,ar });
}

void Sommet::Dessiner(ALLEGRO_BITMAP* bmp)
{}

std::vector<const Arete*> Sommet::Prim(int indicePoids)
{
	std::vector<const Arete*> prim;
	return prim;
}

std::vector<const Arete*> Sommet::Dijkstra(int indicePoids, const Sommet* arrivee=nullptr)
{
	std::vector<const Arete*> dijkstra;
	if (arrivee = nullptr)
	{
		// Dijkstra vers tous les sommets, tous les PCC
	}
	else
	{
		// Dijkstra vers un seul sommet
	}
	return dijkstra;
}


Sommet::~Sommet()
{
}
