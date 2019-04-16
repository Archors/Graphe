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

std::vector<Arete*> Sommet::Prim(int indicePoids)
{
	return std::vector<Arete*>();
}

std::vector<Arete*> Sommet::Dijkstra(int indicePoids, const Sommet* arrivee)
{
	return std::vector<Arete*>();
}


Sommet::~Sommet()
{
}