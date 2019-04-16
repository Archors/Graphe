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

std::vector<const Arete*> Sommet::Dijkstra(int nombreSommets,int indicePoids, const Sommet* arrivee=nullptr)
{
	std::vector<const Arete*> dijkstra;
	std::unordered_set<const Sommet*> sommetsMarques;
	std::unordered_map<const Sommet*, float> distances;
	std::unordered_map<const Sommet*, const Sommet*> predecesseurs; // second = predecesseur de first
	float distanceMin,distance;
	sommetsMarques.insert(this);
	distances.insert({ this, 0.0 });
	if (arrivee == nullptr)			// Dijkstra vers tous les sommets, tous les PCC
	{
		// Tous les sommets sont non marqués
		//Sélectionner et marquer le sommet ayant la plus petite distance au sommet initial
		while (sommetsMarques.size()!=nombreSommets)
		{
			// Marquer le sommet avec la plus petite distance
			for (auto s : distances)
			{
				distance = s.second;
				if (distance < distanceMin) distanceMin = distance;
			}
		}
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
