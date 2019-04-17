#include "Sommet.h"

Sommet::Sommet(int id, double x, double y)
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
	al_draw_text(font, al_map_rgb(0, 0, 0), m_coords.getX(), m_coords.getY()-14, ALLEGRO_ALIGN_CENTRE, inttostring(m_id).c_str() );
	al_destroy_font(font);
}

std::string inttostring(int a)
{
	std::stringstream ss;
	ss << a;
	return ss.str();
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
		for (auto i : prim) //On parcourt la liste des aretes déjà ajoutées au graph
		{
			int ajout = 0;
			for (auto j : prim) //On parcourt la liste de chaque voisin des aretes deja ajoutées
			{
				bool sommet1 = true; //Booleen si le sommet 1 est déjà dans le graphe
				bool sommet2 = true; //Booleen si le sommet 2 est déjà dans le graphe
				for (auto voisin : i->getSommets().first->m_voisins) //On test la liste des voisins des arretes pour vérifier qu'il y ait pas déjà
				{
					if (j->getSommets().first == voisin.first) //On vérifie si le sommet 1 est dans le graphe
						sommet1 = false;
					if (j->getSommets().second == voisin.first) //On vérifie si le sommet 2 est dans le graphe
						sommet2 = false;
					if (!sommet1 && !sommet2) //Si les deux sont déjà dans le graphe, on s'arrete
					{
						ajout = -1;
						break;
					}
				}
				if (ajout == -1)
					break;
				if (sommet1)
					ajout = 1;
				if (sommet2)
					ajout = 2;
				
			}
			/*if (ajout == 1) //Un voisin de i n'est pas dans le graphe
				current = i->getSommets().first->m_voisins;*/

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

const int Sommet::getId() const
{
	return m_id;
}

std::vector<const Arete*> Sommet::BFS(int nbSommets, std::string ssg)
{
	std::vector<int> discovered;
	discovered.resize(nbSommets);
	std::queue<const Sommet*> file;
	std::vector<const Arete*> path;

	discovered[0] = 1;
	file.push(this);

	while (!(file.empty()))
	{

		for (auto s : file.front()->m_voisins)
		{
			if (!discovered[s.first->m_id] && ssg[s.second->getId()] == '1')
			{
				file.push(s.first);
				discovered[s.first->m_id] = 1;
				path.push_back(s.second);
			}
		}
		file.pop();
	}

	return path;
}
int Sommet::tailleComposanteConnexe(int nbSommets, std::string ssg)
{
	std::vector<int> discovered;
	discovered.resize(nbSommets);
	std::queue<const Sommet*> file;

	discovered[0] = 1;
	file.push(this);

	while (!(file.empty()))
	{

		for (auto s : file.front()->m_voisins)
		{
			if (!discovered[s.first->m_id] && ssg[s.second->getId()] == '1')
			{
				file.push(s.first);
				discovered[s.first->m_id] = 1;
			}
		}
		file.pop();
	}

	return std::accumulate(discovered.begin(), discovered.end(), 0);
}


Sommet::~Sommet()
{
}
