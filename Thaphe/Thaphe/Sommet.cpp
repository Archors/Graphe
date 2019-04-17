#include "Sommet.h"

Sommet::Sommet(std::string id, double x, double y)
	:m_id{id},m_coords{x,y}
{}


void Sommet::AjouterVoisin(const Sommet* som, Arete* ar)
{
	m_voisins.insert({ som,ar });
}

void Sommet::Dessiner(ALLEGRO_BITMAP* bmp)
{
	ALLEGRO_FONT* font;
	al_set_target_bitmap(bmp);
	font = al_load_font("simple_font.ttf", 28, 0);
	al_draw_filled_circle(m_coords.getX(), m_coords.getY(), 20, al_map_rgb(255, 255, 255));
	al_draw_text(font, al_map_rgb(0, 0, 0), m_coords.getX(), m_coords.getY()-14, ALLEGRO_ALIGN_CENTRE, m_id.c_str() );
	al_destroy_font(font);
}

std::vector<Arete*> Sommet::Prim(int indicePoids)
{
	std::vector<Arete*> prim;
	int test=0; //Variable qui sert a rien
	Arete* current = NULL;
	Arete* ajout = NULL;
	for (auto voisin : m_voisins) //Ajout de la 1ère arrete dans le graphe
	{
		if (current == NULL) //Si c'est la premiere on la prend comme test
			current = voisin.second;
		else if (current->getPoids(indicePoids) > voisin.second->getPoids(indicePoids)) //On test avec les autre si l'autre est plus petite, on swap
			current = voisin.second;
	}
	prim.push_back(current); //Ajout de la premiere arete
	current = NULL;

	while (!test)  //Tant qu'on a pas visité tous les sommets
	{
		for (auto x : prim) //On parcourt la liste des aretes déjà ajoutées au graph
		{
			//On parcours la liste des sommets voisins aux sommets déjà dans le graphe
			//On commence par first
			for (auto sommetVoisin : x->getSommets().first->m_voisins)
			{
				bool dejaPresent = false;
				for (auto y : prim) //On reparcours les arrêtes du graphe
				{
					//On vérifie que le sommet voisin n'est pas dans le graphe
					if (y->getSommets().first == sommetVoisin.first || y->getSommets().second == sommetVoisin.first)
						dejaPresent = true;
				}
				if(!dejaPresent) //Si le sommet n'est pas dans le graphe
					for (auto y : sommetVoisin.first->m_voisins) //On parcours toutes ses arretes
					{
						//Pour trouver celle avec le sommet dans le graphe
						if (y.second->getSommets().first == x->getSommets().first || y.second->getSommets().second == x->getSommets().first)
						{
							if (current == NULL) //Si c'est la première arrête on l'ajoute
								current = y.second;
							//Sinon on vérifie que l'arrête de poid le plus faible l'est toujours ou pas
							else if (current->getPoids(indicePoids) > y.second->getPoids(indicePoids))
								current = y.second;
						}
					}
			}
			//On recommence mais avec le second sommet des arretes
			for (auto sommetVoisin : x->getSommets().second->m_voisins) //On parcours la liste des sommets voisins aux sommets déjà dans le graphe
			{
				bool dejaPresent = false;
				for (auto y : prim) //On reparcours les arrêtes du graphe
				{
					//On vérifie que le sommet voisin n'est pas dans le graphe
					if (y->getSommets().first == sommetVoisin.first || y->getSommets().second == sommetVoisin.first)
						dejaPresent = true;
				}
				if (!dejaPresent) //Si le sommet n'est pas dans le graphe
					for (auto y : sommetVoisin.first->m_voisins) //On parcours toutes ses arretes
					{
						//Pour trouver celle avec le sommet dans le graphe
						if (y.second->getSommets().first == x->getSommets().first || y.second->getSommets().second == x->getSommets().first)
						{
							if (current == NULL) //Si c'est la première arrête on l'ajoute
								current = y.second;
							//Sinon on vérifie que l'arrête de poid le plus faible l'est toujours ou pas
							else if (current->getPoids(indicePoids) > y.second->getPoids(indicePoids))
								current = y.second;
						}
					}
			}
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

const Coords Sommet::getCoords() const
{
	return m_coords;
}


Sommet::~Sommet()
{
}
