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
	do
	{
		for (auto arete : sommetPrim.back()->m_voisins)
		{
			//On vérifie que l'arrete n'est pas déjà ajoutée
			bool present = false;
			for (auto x : aretePrim)
			{
				if (arete.second == x)
					present = true;
			}
			if (!present) //Si elle ne l'est pas on l'ajoute aux aretes decouvertes
			{
				if (areteDecouverte.empty())
					areteDecouverte.push_back(arete.second);
				else
				{
					//On classe les arretes par poid
					for (std::list<Arete*>::iterator it = areteDecouverte.begin(); it != areteDecouverte.end(); ++it)
					{
						if ((*it)->getPoids(indicePoids) > arete.second->getPoids(indicePoids))
						{
							areteDecouverte.insert(it, arete.second);
							break;
						}
					}
				}
			}
		}
		bool sommet1 = false;
		bool sommet2 = false;
		for (auto sommetDansPrim : sommetPrim) //On verifie qu'il n'y a pas de cycle
		{
			if (areteDecouverte.front()->getSommets().first == sommetDansPrim )
				sommet1 = true;
			if (areteDecouverte.front()->getSommets().second == sommetDansPrim)
				sommet1 = true;
			if (sommet1 & sommet2) //Si il y a un cycle on supprimme l'arete
			{
				areteDecouverte.pop_front();
				break;
			}
		}
		if (!sommet1 || !sommet2) //Si il n'y a pas de cycle on ajoute l'arete
		{
			aretePrim.push_back(areteDecouverte.front());
			areteDecouverte.pop_front();
			for (auto sommet : sommetPrim) //On ajoute le nouveau sommet au vecteur
			{
				if (sommet != aretePrim.back()->getSommets().first)
				{
					sommetPrim.push_back(aretePrim.back()->getSommets().first);
				}
				else
				{
					sommetPrim.push_back(aretePrim.back()->getSommets().second);
				}
			}
		}
		if (areteDecouverte.empty()) //Si il n'y a plus d'arrete decouverte on quitte
			break;
		

	} while (!areteDecouverte.empty());


	return aretePrim;
}

std::vector<const Arete*> Sommet::Dijkstra(int nombreSommets,int indicePoids, const Sommet* arrivee) const
{
	std::vector<const Arete*> dijkstra;
	std::unordered_set<const Sommet*> sommetsMarques;
	std::unordered_map<const Sommet*, float> distances;		/// second = distance de first par rapport à this
	std::unordered_map<const Sommet*, const Sommet*> predecesseurs; /// second = predecesseur de first
	const Sommet* somMarq=nullptr;	/// Pointeur pour le sommet qui sera marqué à chaque tour 
	float distanceMin,distance;				/// Permet de comparer les distances pour marquer un sommet
	sommetsMarques.insert(this);			/// On marque le sommet de départ
	predecesseurs.insert({ this, somMarq });	/// Le sommet de départ n'a pas de prédécesseur
	for (auto s : m_voisins)				/// On ajoute la distance de chaque voisin du sommet de départ
	{										/// et on renseigne que this est son prédécesseur
		distances.insert({ s.first, s.second->getPoids(indicePoids) });
		predecesseurs.insert({s.first, this});
	}
	if (arrivee == nullptr)			/// Dijkstra vers tous les sommets, tous les PCC
	{
		/// Tous les sommets sont non marqués, sauf le this
		///Sélectionner et marquer le sommet ayant la plus petite distance au sommet initial
		while (sommetsMarques.size()<nombreSommets)  /// Tant qu'il reste des sommets non marqués
		{
			/// Marquer le sommet avec la plus petite distance
			distanceMin = distances.cbegin()->second;
			somMarq = distances.cbegin()->first;
			for (auto s : distances)			
			{
				distance = s.second;
				if (distance < distanceMin)
				{
					distanceMin = distance;											// J'ai oublié quelque part d'ajouter la distance
					somMarq=s.first;												// de somMarq, ainsi que son prédécesseur (?)
				}
			}
			sommetsMarques.insert(somMarq);
			dijkstra.push_back(predecesseurs.find(somMarq)->second->m_voisins.find(somMarq)->second); /// Ajout de l'arête 
			
																								   /// On met à jour les distances avec le nouveau sommet marqué
			for (const auto v : somMarq->m_voisins) /// Pour chaque voisin du sommet marqué v est une paire (Sommet *, Arete*)
			{
				/// Mise à jour de la distance de chaque voisin
				/// si d(somMarq) + poids (somMarq - v) < d(v)
				if (distances.count(v.first) == 0)  /// Si le voisin n'a pas de distance dans distances, on l'ajoute
				{
					predecesseurs.insert({ v.first, somMarq });
					distance = distances.find(somMarq)->second + somMarq->m_voisins.find(v.first)->second->getPoids(indicePoids); 
					distances.insert({ v.first , distance });
				}
				else if (distances.find(somMarq)->second + somMarq->m_voisins.find(v.first)->second->getPoids(indicePoids)<distances.find(v.first)->second)
				{ 
					predecesseurs[v.first] = somMarq;	/// somMarq devient le prédécesseur de v
					distances[v.first] = distances.find(somMarq)->second + somMarq->m_voisins.find(v.first)->second->getPoids(indicePoids);
					/// et on met à jour la distance de v qui vaut alors d(somMarq) + poids (somMarq - v)
				}
			}
			
			distances.erase(somMarq);			/// Une fois que j'ai marqué un sommet je dois le dégager de distances, sinon il sera marqué encore
		}
	}
	else
	{
		/// Dijkstra vers un seul sommet
	}
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
