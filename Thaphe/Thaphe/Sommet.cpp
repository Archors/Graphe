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
	std::unordered_map<const Sommet*, const float> distances;		/// second = distance de first par rapport à this
	std::unordered_map<const Sommet*, const Sommet*> predecesseurs; /// second = predecesseur de first
	const Sommet* somMarq;	/// Pointeur pour le sommet qui sera marqué à chaque tour 
	//const Sommet* pred;		
	float distanceMin,distance;				/// Permet de comparer les distances pour marquer un sommet
	sommetsMarques.insert(this);			/// On marque le sommet de départ
	//distances.insert({ this, 0.0 });		// Fausse les calculs ensuite car distance inférieure à toutes les autres
	predecesseurs.insert(this, nullptr);	/// Le sommet de départ n'a pas de prédécesseur
	for (auto s : m_voisins)				/// On ajoute la distance de chaque voisin du sommet de départ
	{										/// et on renseigne que this est son prédécesseur
		distances.insert(s.first, s.second->getPoids(indicePoids));
		predecesseurs.insert(s.first, this);
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
			dijkstra.insert(predecesseurs.find(somMarq)->second->m_voisins.find(somMarq)->second); /// Ajout de l'arête 

																								   /// On met à jour les distances avec le nouveau sommet marqué
			for (auto v : somMarq->m_voisins) /// Pour chaque voisin du sommet marqué
			{
				/// Mise à jour de la distance de chaque voisin
				/// si d(somMarq) + poids (somMarq - v) < d(v)
				if (distances.find(v) == nullptr)
				{
					predecesseurs.insert(v, somMarq);
					distances.find(v).second = distances.find(somMarq) + somMarq->m_voisins.find(v).second->getPoids(indicePoids);
				}
				else if (distances.find(somMarq).second+somMarq->m_voisins.find(v).second->getPoids(indicePoids)<distances.find(v)->second)
				{ 
					predecesseurs.find(v) = (v, somMarq);	/// somMarq devient le prédécesseur de v
					distances.find(v).second = distances.find(somMarq).second + somMarq->m_voisins.find(v).second->getPoids(indicePoids);
					/// et on met à jour la distance de v qui vaut alors d(somMarq) + poids (somMarq - v)
				}
			}
			
			distances.erase(somMarq);			// Note : une fois que j'ai marqué un sommet je dois le dégager de distances
		}
	}
	else
	{
		/// Dijkstra vers un seul sommet
	}
	return dijkstra;
}


Sommet::~Sommet()
{
}
