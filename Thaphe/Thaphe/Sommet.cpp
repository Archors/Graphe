#include "Sommet.h"

Sommet::Sommet(int id, double x, double y)
	:m_id{ id }, m_coords{ x,y }, m_color{ 0 }
{}


void Sommet::AjouterVoisin(const Sommet* som, Arete* ar)
{
	m_voisins.insert({ som,ar });
}

void Sommet::Dessiner(ALLEGRO_BITMAP* bmp, std::vector<ALLEGRO_COLOR> colors)
{
	ALLEGRO_FONT* font;
	al_set_target_bitmap(bmp);
	font = al_load_font("simple_font.ttf", 28, 0);
	al_draw_filled_circle(m_coords.getX(), m_coords.getY(), 20, colors[m_color]);
	al_draw_text(font, al_map_rgb((1-colors[m_color].r)*255, 255*(1-colors[m_color].g), 255*(1-colors[m_color].b)), m_coords.getX(), m_coords.getY()-14, ALLEGRO_ALIGN_CENTRE, inttostring(m_id).c_str() );
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
	//Creation des type de donn�es utiles � l'algorithme de Prim
	std::vector<Arete*> aretePrim; //Vecteur des arretes pour Prim
	std::list<Arete*> areteDecouverte; //Liste des arretes d�j� decouvertes
	std::vector<Sommet*> sommetPrim; //Tableau des sommets ou l'on est d�j� pass�
	sommetPrim.push_back(this); //On ajoute le sommet de depart au vecteur de sommet
	do
	{
		for (auto arete : sommetPrim.back()->m_voisins)//On check les voisins du dernier sommet ajout�
		{
			//
			bool present = false; // Si l'arrete est deja presente dans le graphe
			bool sommet1 = false; //1er sommet de l'arete en cours de verification
			bool sommet2 = false; //2eme sommet de l'arete en cours de verification
			for (auto sommetDejaAjoute : sommetPrim) //On parcours la liste des sommets d�j� ajout�e dans le graphe
			{
				if (arete.second->getSommets().first == sommetDejaAjoute) //Si le premier sommet est d�j� dans le graphe
					sommet1 = true; //On dit que le sommet 1 est dans le graphe
				if (arete.second->getSommets().second == sommetDejaAjoute) //Si le deuxieme sommet est d�j� dans le graphe
					sommet2 = true; //On dit que le sommet 2 est dans le graphe
				if (sommet1 && sommet2) //Si les deux sommets de l'arrete sont dans le graphe alors l'arrete est d�j� dans le graphe
				{
					present = true; //On dit que l'arrete est dans le graphe
					break;
				}
			}

			if (!present) //Si l'arete n'est pas dans le graphe, on l'ajoute aux aretes decouvertes
			{
				if (areteDecouverte.empty()) //Si il n'y a pas encore d'arrete decouverte
					areteDecouverte.push_back(arete.second); //On peut ajouter l'arrete directement en 1er
				else
				{
					//On classe les arretes par poid
					bool ajout = false;
					for (std::list<Arete*>::iterator it = areteDecouverte.begin(); it != areteDecouverte.end(); ++it) //On parcours les arretes par poid
					{
						if ((*it)->getPoids(indicePoids) > arete.second->getPoids(indicePoids)) //Si l'arrete en cours d'ajout est de poid plus faible que celle parcouru
						{
							areteDecouverte.insert(it, arete.second); //On l'ajoute avant
							ajout = true; //On dit qu'elle a �t� ajout� pour ne stoper la boucle
							break;
						}
					}
					if (!ajout) //Si elle n'a pas �t� ajout� � la fin c'est qu'elle est de poid superieur aux autres
						areteDecouverte.push_back(arete.second); //On l'ajoute donc � la fin
				}
			}
		}
		bool sommet1 = false; //On remet les booleen � false une fois utilis�s
		bool sommet2 = false;
		for (auto sommetDansPrim : sommetPrim) //On verifie qu'il n'y a pas de cycle
		{
			if (areteDecouverte.front()->getSommets().first == sommetDansPrim) //On verifie si le 1er sommet est dans le graphe
				sommet1 = true;
			if (areteDecouverte.front()->getSommets().second == sommetDansPrim) //On v�rifie si le 2�me sommet est dans le graphe
				sommet2 = true;
			if (sommet1 && sommet2) //Il y a un cycle si les deux sommets sont d�j� dans le graphe
			{
				areteDecouverte.pop_front(); //Si il y a un cycle on supprimme l'arete
				break;
			}
		}
		if (!sommet1 || !sommet2) //Si il n'y a pas de cycle on ajoute l'arete
		{
			aretePrim.push_back(areteDecouverte.front()); //On ajoute la premiere arrete de la pile dans le graphe
			//On ajoute le nouveau sommet au vecteur
			for (auto sommet : sommetPrim) //On parcourt les sommets d�j� present
			{
				if (areteDecouverte.front()->getSommets().first == sommet) //Si le sommet 1 est deja present
					sommetPrim.push_back(areteDecouverte.front()->getSommets().second); //Alors c'est le sommet 2 qui n'y �tait pas encore
				if(areteDecouverte.front()->getSommets().second == sommet) //Si le sommet 2 est deja present
					sommetPrim.push_back(areteDecouverte.front()->getSommets().first); //Alors c'est le sommet 1 qui n'y �tait pas encore
			}
			areteDecouverte.pop_front(); //Une fois l'arrete ajout� on l'enleve de la pile
		}
		if (areteDecouverte.empty()) //Si la pile est vide, on sort de la boucle pour gagner du temps
			break;

	} while (!areteDecouverte.empty()); //Tant que la pile n'est pas vide on continu


	return aretePrim; //On retourne un vecteur d'arrete pour parcourir le graphe en faisant le chemin de poid minimal
}

/// choix2emeRetour permet de choisir ce qui sera dans le float de la paire retourn�e. 1 -> poids total    2 -> plus long des pcc
std::pair<std::vector<const Arete*>, float> Sommet::Dijkstra(int nombreSommets,int indicePoids, const Sommet* arrivee, std::bitset<nombreMaxAretes> grapheDeTravail, int choix2emeRetour) const
{
	std::vector<const Arete*> dijkstraTous = {}, dijkstraArrivee = {}; /// dijkstraTous : ar�tes de tous les pcc vers tous les sommets ; dijkstraArrivee : ar�tes de this � arriv�e
	std::vector<float> distancesFinales = {};
	std::unordered_set<const Sommet*> sommetsMarques = {};
	std::unordered_map<const Sommet*, float> distances = {};		/// second = distance de first par rapport � this
	std::unordered_map<const Sommet*, const Sommet*> predecesseurs = {}; /// second = predecesseur de first
	const Sommet* somMarq = nullptr;	/// Pointeur pour le sommet qui sera marqu� � chaque tour 
	const Sommet* pred1, * pred2;		/// Pour le dijkstraArrivee
	float distanceMin, distance, distanceMax = 0.0;				/// Permet de comparer les distances pour marquer un sommet
	sommetsMarques.insert(this);			/// On marque le sommet de d�part
	for (const auto s : m_voisins)				/// On ajoute la distance de chaque voisin du sommet de d�part
	{										/// et on renseigne que this est son pr�d�cesseur
		if (grapheDeTravail[s.second->getId()]) /// Si l'ar�te est comprise dans le graphe de travail
		{
			distances.insert({ s.first, s.second->getPoids(indicePoids) }); /// On l'ajoute aux distances
			predecesseurs.insert({ s.first, this });	/// et on ajoute le sommet aux predecesseurs
		}
	}

	/// Tous les sommets sont non marqu�s, sauf le this
	///S�lectionner et marquer le sommet ayant la plus petite distance au sommet initial
	while (sommetsMarques.size() < nombreSommets)  /// Tant qu'il reste des sommets non marqu�s
	{
		/// Marquer le sommet avec la plus petite distance
		distanceMin = distances.cbegin()->second;
		somMarq = distances.cbegin()->first;
		for (const auto s : distances)
		{
			distance = s.second;
			if (distance < distanceMin)
			{
				distanceMin = distance;
				somMarq = s.first;
			}
		}
		sommetsMarques.insert(somMarq);
		distancesFinales.push_back(distances.find(somMarq)->second);
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
					distance = distances.find(somMarq)->second + somMarq->m_voisins.find(v.first)->second->getPoids(indicePoids);
					if (distances.count(v.first) == 0 || distance < distances.find(v.first)->second)  /// Si le voisin n'a pas de distance dans distances, on l'ajoute
					{
						predecesseurs[v.first] = somMarq;	/// somMarq devient le pr�d�cesseur de v
						distances[v.first] = distance;		/// et on met � jour la distance de v qui vaut alors d(somMarq) + poids (somMarq - v)
					}
				}
			}
		}
		distances.erase(somMarq);			/// Une fois que j'ai marqu� un sommet je dois le d�gager de distances, sinon il sera marqu� encore
	}

	if (arrivee == nullptr)
	{
		if (choix2emeRetour == 1)
		{
			return { dijkstraTous, std::accumulate(distancesFinales.cbegin(), distancesFinales.cend(), 0.0) };
		}
		else if (choix2emeRetour == 2)
		{
			return { dijkstraTous, *std::max_element(distancesFinales.cbegin(), distancesFinales.cend()) };
		}
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
		return { dijkstraArrivee, 0.0 }; /// Pour ce cas on ne s'int�resse pas � la longueur du chemin
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
			if (!discovered[s.first->m_id] && ssg[s.second->getId()]) //Si le sommet n'est pas d�couvert et si l'arete est dans le graphe
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

	discovered[m_id] = 1;
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


bool Sommet::avoisineCol(int color, std::bitset<nombreMaxAretes> ssg) const
{
	for (auto s : m_voisins)
	{
		if (ssg[s.second->getId()] && s.first->m_color == color)
			return true;
	}
	return false;
}

const int Sommet::getOrdre() const
{
	return m_voisins.size();
}


Sommet::~Sommet()
{
}
