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
		for (auto arete : sommetPrim.back()->m_voisins)//On check les voisins du dernier sommet ajout�
		{
			//On v�rifie que l'arrete n'est pas d�j� ajout�e
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

std::pair<std::vector<const Arete*>, float> Sommet::Dijkstra(int nombreSommets,int indicePoids, std::bitset<nombreMaxAretes> grapheDeTravail, const Sommet* arrivee) const
{
	//std::cout << "Dijkstra depuis le sommet : " << this->getId() << " ,  nombre de sommets : " << nombreSommets << " ,  indice de poids : " << indicePoids << std::endl;
	/*
	std::cout << "Voisins de " << this->getId() << " : ";
	for (auto s : m_voisins)
	{
		std::cout << s.first->getId() << "  ";
	}std::cout << std::endl;
	*/
	std::vector<const Arete*> dijkstraTous, dijkstraArrivee; /// dijkstraTous : ar�tes de tous les pcc vers tous les sommets ; dijkstraArrivee : ar�tes de this � arriv�e
	float distancesTotales=0.0;
	std::unordered_set<const Sommet*> sommetsMarques;
	std::unordered_map<const Sommet*, float> distances;		/// second = distance de first par rapport � this
	std::unordered_map<const Sommet*, const Sommet*> predecesseurs; /// second = predecesseur de first
	const Sommet* somMarq=nullptr;	/// Pointeur pour le sommet qui sera marqu� � chaque tour 
	const Sommet* pred1, *pred2;		/// Pour le dijkstraArrivee
	float distanceMin,distance;				/// Permet de comparer les distances pour marquer un sommet
	sommetsMarques.insert(this);			/// On marque le sommet de d�part
	//predecesseurs.insert({ this, nullptr });	/// Le sommet de d�part n'a pas de pr�d�cesseur   <-- a verifier mais inutile je crois, fait planter le programme
	for (auto s : m_voisins)				/// On ajoute la distance de chaque voisin du sommet de d�part
	{										/// et on renseigne que this est son pr�d�cesseur
		/*std::cout << "Arete voisine de this : " << s.second->getId() << "   Poids : " << s.second->getPoids(indicePoids)
				<< " |  relie " <<s.second->getSommets().first->getId() << "   et " << s.second->getSommets().second->getId() << std::endl;*/
		if (grapheDeTravail[s.second->getId()]) /// Si l'ar�te est comprise dans le graphe de travail
		{
			distances.insert({ s.first, s.second->getPoids(indicePoids) }); /// On l'ajoute aux distances
			predecesseurs.insert({s.first, this});	/// et on ajoute le sommet aux predecesseurs
		}
	}
	/*for (auto s : distances)
	{
		std::cout << "VOISINS : (" << s.first->getId() << ")  "<<std::endl;
	}*/
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
				distanceMin = distance;				
				somMarq=s.first;												
			}
		}
		/*for (auto s : distances)
		{
			std::cout << "d(" << s.first->getId() << ") = " << s.second << std::endl;
		}*/
		sommetsMarques.insert(somMarq);
		//std::cout << "Sommet marqu� : " << somMarq->getId() <<std::endl;
		distancesTotales += distances.find(somMarq)->second; /// Une fois qu'on marque sommet on ajoute sa distance � la somme de toutes les distances
		//std::cout << "valeur ajoutee a distancesTotales : " << distances.find(somMarq)->second << std::endl;
		dijkstraTous.push_back(predecesseurs.find(somMarq)->second->m_voisins.find(somMarq)->second); /// Ajout de l'ar�te 
											   /// On met � jour les distances avec le nouveau sommet marqu�
		for (const auto v : somMarq->m_voisins) /// Pour chaque voisin du sommet marqu� v est une paire (Sommet *, Arete*)
		{
			if (grapheDeTravail[v.second->getId()])
			{
				/// Mise � jour de la distance de chaque voisin
				/// si d(somMarq) + poids (somMarq - v) < d(v)
				if (sommetsMarques.count(v.first) == 0)
				{
					if (distances.count(v.first) == 0)  /// Si le voisin n'a pas de distance dans distances, on l'ajoute
					{
						predecesseurs.insert({ v.first, somMarq });
						distance = distances.find(somMarq)->second + somMarq->m_voisins.find(v.first)->second->getPoids(indicePoids);
						distances.insert({ v.first , distance });

					}
					else if (distances.find(somMarq)->second + somMarq->m_voisins.find(v.first)->second->getPoids(indicePoids) < distances.find(v.first)->second)
					{
						predecesseurs[v.first] = somMarq;	/// somMarq devient le pr�d�cesseur de v
						distances[v.first] = distances.find(somMarq)->second + somMarq->m_voisins.find(v.first)->second->getPoids(indicePoids);
						/// et on met � jour la distance de v qui vaut alors d(somMarq) + poids (somMarq - v)
					}
				}
			}
		}
		distances.erase(somMarq);			/// Une fois que j'ai marqu� un sommet je dois le d�gager de distances, sinon il sera marqu� encore
	}
	
	//std::cout << "somme des distances : " << distancesTotales<<std::endl;
	//std::cout << std::endl; // a tej

	if (arrivee == nullptr)
	{
		return std::make_pair(dijkstraTous, distancesTotales);
	}
	else
	{
		pred1 = arrivee;
		pred2 = predecesseurs.find(arrivee)->second;
		dijkstraArrivee.push_back(pred2->m_voisins.find(pred1)->second);
		while (pred2 != this)
		{
			pred1 = pred2;
			pred2 = predecesseurs.find(pred2)->second;
			dijkstraArrivee.push_back(pred2->m_voisins.find(pred1)->second);
		}
		return std::make_pair(dijkstraArrivee, distancesTotales);
	}
}

float Sommet::Dijtances(std::bitset<nombreMaxAretes> ssg, int indicePoids, int nbSommets)
{
	std::list<std::pair<const Sommet*, float>> file;
	std::vector<float> dist;
	dist.resize(nbSommets, 30000000000000000000000000000000000000.0);//Taille max float = 3.10^38 ~ infini
	int length = 0;
	std::vector<bool> sommets;
	sommets.resize(nbSommets);

	file.push_back(std::make_pair( this, 0 ));
	dist[m_id] = 0;
	sommets[m_id] = true;

	for (int i = 0; i < nbSommets; i++)
	{
		for (auto s : file.front().first->m_voisins)
		{
			if (ssg[s.second->getId()] && !sommets[s.first->m_id])
			{
				if (dist[s.first->m_id] > file.front().second + s.second->getPoids(indicePoids))
				{
					file.push_back( std::make_pair(s.first, file.begin()->second + s.second->getPoids(indicePoids)) );
					dist[s.first->m_id] = file.front().second + s.second->getPoids(indicePoids);
				}
					
			}
		}
		sommets[file.begin()->first->m_id] = true;
		length += file.begin()->second;
		file.pop_front();
		if (file.empty())
			break;
		file.sort(compDistDij);
		while (sommets[file.begin()->first->m_id])
		{
			file.pop_front();
			if (file.empty())
				break;
		}
	}

	return length;

}

bool compDistDij(std::pair<const Sommet*, float> s1, std::pair<const Sommet*, float> s2)
{
	return (s1.second < s2.second);
}

const Coords Sommet::getCoords() const
{
	return m_coords;
}

const int Sommet::getId() const
{
	return m_id;
}

int Sommet::BFSnbAretes(int nbSommets, std::bitset<nombreMaxAretes> ssg)
{
	std::vector<int> discovered;
	discovered.resize(nbSommets);
	std::queue<const Sommet*> file;
	int nbAr = 0;

	discovered[0] = 1;
	file.push(this);

	while (!(file.empty()))
	{

		for (auto s : file.front()->m_voisins)
		{
			if (!discovered[s.first->m_id] && ssg[s.second->getId()])
			{
				file.push(s.first);
				discovered[s.first->m_id] = 1;
				nbAr++;
			}
		}
		file.pop();
	}

	return nbAr;
}
int Sommet::tailleComposanteConnexe(int nbSommets, std::bitset<nombreMaxAretes> ssg)
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
			if (!discovered[s.first->m_id] && ssg[s.second->getId()])
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
