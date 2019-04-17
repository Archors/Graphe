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

std::vector<const Arete*> Sommet::Dijkstra(int nombreSommets,int indicePoids, const Sommet* arrivee=nullptr) const
{
	std::vector<const Arete*> dijkstra;
	std::unordered_set<const Sommet*> sommetsMarques;
	std::unordered_map<const Sommet*, const float> distances;		/// second = distance de first par rapport � this
	std::unordered_map<const Sommet*, const Sommet*> predecesseurs; /// second = predecesseur de first
	const Sommet* somMarq=nullptr;	/// Pointeur pour le sommet qui sera marqu� � chaque tour 
	float distanceMin,distance;				/// Permet de comparer les distances pour marquer un sommet
	sommetsMarques.insert(this);			/// On marque le sommet de d�part
	predecesseurs.insert(this, somMarq);	/// Le sommet de d�part n'a pas de pr�d�cesseur
	for (auto s : m_voisins)				/// On ajoute la distance de chaque voisin du sommet de d�part
	{										/// et on renseigne que this est son pr�d�cesseur
		distances.insert(s.first, s.second->getPoids(indicePoids));
		predecesseurs.insert(s.first, this);
	}
	if (arrivee == nullptr)			/// Dijkstra vers tous les sommets, tous les PCC
	{
		/// Tous les sommets sont non marqu�s, sauf le this
		///S�lectionner et marquer le sommet ayant la plus petite distance au sommet initial
		while (sommetsMarques.size()<nombreSommets)  /// Tant qu'il reste des sommets non marqu�s
		{
			/// Marquer le sommet avec la plus petite distance
			distanceMin = distances.cbegin()->second;
			somMarq = distances.cbegin()->first;
			for (auto s : distances)			
			{
				distance = s.second;
				if (distance < distanceMin)
				{
					distanceMin = distance;											// J'ai oubli� quelque part d'ajouter la distance
					somMarq=s.first;												// de somMarq, ainsi que son pr�d�cesseur (?)
				}
			}
			sommetsMarques.insert(somMarq);
			dijkstra.push_back(predecesseurs.find(somMarq)->second->m_voisins.find(somMarq)->second); /// Ajout de l'ar�te 

																								   /// On met � jour les distances avec le nouveau sommet marqu�
			for (const auto v : somMarq->m_voisins) /// Pour chaque voisin du sommet marqu� v est une paire (Sommet *, Arete*)
			{
				/// Mise � jour de la distance de chaque voisin
				/// si d(somMarq) + poids (somMarq - v) < d(v)
				if (distances.find(v.first) == nullptr)
				{
					predecesseurs.insert(v.first, somMarq);
					distance = distances.find(somMarq)->second + somMarq->m_voisins.find(v.first)->second->getPoids(indicePoids); //somMarq->getAreteVoisin(v)->getPoids(indicePoids);
					distances.insert( v.first , distance );
				}
				else if (distances.find(somMarq)->second + somMarq->m_voisins.find(v.first)->second->getPoids(indicePoids)<distances.find(v.first)->second)
				{ 
					predecesseurs.find(v.first) = (v.first, somMarq);	/// somMarq devient le pr�d�cesseur de v
					distances.find(v.first)=(v.first, distances.find(somMarq)->second + somMarq->m_voisins.find(v.first)->second->getPoids(indicePoids));
					/// et on met � jour la distance de v qui vaut alors d(somMarq) + poids (somMarq - v)
				}
			}
			
			distances.erase(somMarq);			// Note : une fois que j'ai marqu� un sommet je dois le d�gager de distances
		}
	}
	else
	{
		/// Dijkstra vers un seul sommet
	}
	return dijkstra;
}
/*
Arete* Sommet::getAreteVoisin(const Sommet* voisin) const
{
	return m_voisins.find(voisin)->second;
}
*/
Sommet::~Sommet()
{
}
