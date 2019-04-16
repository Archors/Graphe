#include "Sommet.h"

Sommet::Sommet(std::string id, double x, double y)
	:m_id{ id }, m_coords{ x, y }
{
}

void Sommet::AjouterVoisin(const Sommet* som, const Arete* ar)
{
	std::cout << "nouveu voisin\n";
}

void Sommet::Dessiner(ALLEGRO_BITMAP*)
{
}

std::vector<const Arete*> Sommet::Prim(int indicePoids)
{
	return std::vector<const Arete*>();
}

std::vector<const Arete*> Sommet::Dijkstra(int indicePoids, const Sommet* arrivee)
{
	return std::vector<const Arete*>();
}


Sommet::~Sommet()
{
}