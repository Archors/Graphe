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
	Arete* curent = NULL;
	int test=0;
	while (!test) { //Tant qu'on a pas visité tous les sommets
		for (auto x : m_voisins) //Parcourir tous les sommets adjacents au sommet actuelle
		{
			if (curent == NULL) //Si c'est le premier on l'enregistre
				curent = x.second;
			else if (curent->getPoids(indicePoids) < x.second->getPoids(indicePoids)) //Sinon on vérifie que c'est le plus proche
			{
				for (auto y : prim) //On parcourt les arretes déjà ajoutées
					//if (y->getSommets().) //On vérifie que le sommet n'est pas déjà dedans
						curent = x.second; //Si c'est le plus proche on l'ajoute au potentiel nouveau sommet
			}
		
		}
		prim.push_back(curent); //On ajoute l'arrete la plus courte


	}
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
