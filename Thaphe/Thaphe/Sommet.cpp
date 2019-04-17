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
	std::vector<Arete*> aretePrim;
	std::list<Arete*> areteDecouverte;
	std::vector<Sommet*> sommetPrim;
	sommetPrim.push_back(this);
	/*for (auto x : this->m_voisins)
		std::cout << x.first->m_id;*/
	do
	{
		for (auto arete : sommetPrim.back()->m_voisins)//On check les voisins du dernier sommet ajouté
		{
			//On vérifie que l'arrete n'est pas déjà ajoutée
			bool present = false;
			bool sommet1 = false;
			bool sommet2 = false;
			for (auto sommetDejaAjoute : sommetPrim)
			{
				if (arete.second->getSommets().first == sommetDejaAjoute)
					sommet1 = true;
				if (arete.second->getSommets().second == sommetDejaAjoute)
					sommet2 = true;
				if (sommet1 && sommet2)
				{
					present = true;
					break;
				}
			}

			if (!present) //Si elle ne l'est pas on l'ajoute aux aretes decouvertes
			{
				if (areteDecouverte.empty()) //Si il n'y a pas encore d'arrete decouverte
					areteDecouverte.push_back(arete.second);
				else
				{
					//On classe les arretes par poid
					bool ajout = false;
					for (std::list<Arete*>::iterator it = areteDecouverte.begin(); it != areteDecouverte.end(); ++it)
					{
						if ((*it)->getPoids(indicePoids) > arete.second->getPoids(indicePoids))
						{
							areteDecouverte.insert(it, arete.second);
							ajout = true;
							break;
						}
					}
					if (!ajout)
						areteDecouverte.push_back(arete.second);
				}
			}
		}
		bool sommet1 = false;
		bool sommet2 = false;
		for (auto sommetDansPrim : sommetPrim) //On verifie qu'il n'y a pas de cycle
		{
			if (areteDecouverte.front()->getSommets().first == sommetDansPrim)
				sommet1 = true;
			if (areteDecouverte.front()->getSommets().second == sommetDansPrim)
				sommet2 = true;
			if (sommet1 && sommet2) //Si il y a un cycle on supprimme l'arete
			{
				areteDecouverte.pop_front();
				break;
			}
		}
		if (!sommet1 || !sommet2) //Si il n'y a pas de cycle on ajoute l'arete
		{
			aretePrim.push_back(areteDecouverte.front());
			for (auto sommet : sommetPrim) //On ajoute le nouveau sommet au vecteur
			{
				if (areteDecouverte.front()->getSommets().first == sommet)
					sommetPrim.push_back(areteDecouverte.front()->getSommets().second);
				if(areteDecouverte.front()->getSommets().second == sommet)
					sommetPrim.push_back(areteDecouverte.front()->getSommets().first);
			}
			areteDecouverte.pop_front();
		}
		if (areteDecouverte.empty()) //Si il n'y a plus d'arrete decouverte on quitte
			break;

	} while (!areteDecouverte.empty());


	return aretePrim;
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
