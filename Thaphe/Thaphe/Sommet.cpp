#include "Sommet.h"

Sommet::Sommet(std::string id, Coords coords)
	:m_id{id},m_coords{coords}
{}

Sommet::~Sommet()
{}

void Dessiner(ALLEGRO_BITMAP*)
{

}
/*
std::vector<const Arete*> Prim(int indicePoids)
{

}

std::vector<const Arete*> Dijkstra(int indicePoids, const Sommet* arrivee)
{
	
}
*/