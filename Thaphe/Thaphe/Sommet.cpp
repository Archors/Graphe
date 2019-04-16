#include "Sommet.h"

Sommet::Sommet(std::string id, double x, double y)
	:m_id{id},m_coords{x,y}
{}


void Sommet::AjouterVoisin(const Sommet* som, const Arete* ar)
{
	std::cout << "nouveau voisin\n";
}

void Sommet::Dessiner(ALLEGRO_BITMAP* bmp)
{}

std::vector<const Arete*> Sommet::Prim(int indicePoids)
{
	std::vector<const Arete*> prim;
	return prim;
}

std::vector<const Arete*> Sommet::Dijkstra(int indicePoids, const Sommet* arrivee)
{
	std::vector<const Arete*> dijkstra;
	return dijkstra;
}


Sommet::~Sommet()
{
}
