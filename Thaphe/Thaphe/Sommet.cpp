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

std::vector<Arete*> Sommet::Prim(int indicePoids)
{
	std::vector<Arete*> prim;
	int test=0;
	Arete* current = NULL;
	Arete* ajout = NULL;
	for (auto voisin : m_voisins) //Ajout de la 1ère arrete dans le graphe
	{
		if (current == NULL) //Si c'est la premiere on la prend comme test
			current = voisin.second;
		else if (current->getPoids(indicePoids) > voisin.second->getPoids(indicePoids)) //On test avec les autre si l'autre est plus petite, on swap
			current = voisin.second;
	}
	prim.push_back(current);
	current = NULL;
	while (!test)  //Tant qu'on a pas visité tous les sommets
	{
		for (auto i : prim) //On parcourt la liste des arrete déjà ajoutées au graph
		{
			bool ajout = true;
			for (auto j : prim) //On verifie que l'arrete qu'on ajoute n'est pas deja dans le graphe
			{
				bool sommet1 = true; //Booleen si le sommet 1 est déjà dans le graphe
				bool sommet2 = true; //Booleen si le sommet 2 est déjà dans le graphe
				for (auto voisin : j->getSommets().first->m_voisins)
				{
					if (i->getSommets().first == voisin.first) //On vérifie si le sommet 1 est dans le graphe
						sommet1 = false;
					if (i->getSommets().second == voisin.first) //On vérifie si le sommet 2 est dans le graphe
						sommet2 = false;
					if (!sommet1 && !sommet2) //Si les deux sont déjà dans le graphe, on s'arrete
					{
						ajout = false;
						break;
					}
				}
				if (!ajout)
					break;
				
			}
			//if(ajout)
				//if(current == NULL)

		}
		prim.push_back(ajout); //On ajoute l'arrete la plus courte

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
