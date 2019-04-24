///
///\file Sommet.cpp
///
///\brief Appels principaux des fonctions effectuant des actions sur un sommet
///\date 21 avril 2019
///
///		Contient le code de construction d'un sommet
///		Contient l'appel des algorithmes qui se lancent depuis un Sommet tels que Prim ou Dijkstra
///		Contient les fonctions permettant l'affichage d'un sommet sur une bitmap

#include "Sommet.h"


///\fn Sommet::Sommet(int id, double x, double y)
///\brief Fonction constructeur d'un objet de la classe Sommet
///\param id du sommet ainsi que ses coordonnées pour la représentation graphique
Sommet::Sommet(int id, double x, double y)			/// Constructeur de sommet, un sommet a un id, des coords (pour la représentation graphique) et une couleur
	:m_id{ id }, m_coords{ x,y }, m_color{ 0 }
{}

///\fn void Sommet::AjouterVoisin(const Sommet* som, Arete* ar)
///\brief Fonction pour ajouter un voisin à un sommet
///\param som le sommet à ajouter en voisin et ar l'arête liant le sommet actuel et son voisin
void Sommet::AjouterVoisin(const Sommet* som, Arete* ar)
{
	m_voisins.insert({ som,ar });
}

///\fn void Sommet::Dessiner(ALLEGRO_BITMAP* bmp, std::vector<ALLEGRO_COLOR> colors)
///\brief Fonction pour placer un sommet sur une bitmap, sert à la représentation graphique d'un graphe
///\param bmp le bitmap sur laquelle on dessine le sommet, colors la couleur associée au sommet
void Sommet::Dessiner(ALLEGRO_BITMAP* bmp, std::vector<ALLEGRO_COLOR> colors)
{
	ALLEGRO_FONT* font;
	al_set_target_bitmap(bmp);
	font = al_load_font("simple_font.ttf", 28, 0);
	al_draw_filled_circle(m_coords.getX(), m_coords.getY(), 20, colors[m_color]);
	al_draw_text(font, al_map_rgb((1-colors[m_color].r)*255, 255*(1-colors[m_color].g), 255*(1-colors[m_color].b)), m_coords.getX(), m_coords.getY()-14, ALLEGRO_ALIGN_CENTRE, inttostring(m_id).c_str() );
	al_destroy_font(font);
}

///\fn std::string inttostring(int a)
///\brief Fonction permettant de transformer un entier en chaîne de caractères
///\param a Entier que l'on veut transformer en chaîne de caractères
///\return ss Chaîne de caractères crée à partir de l'entier a
std::string inttostring(int a)
{
	std::stringstream ss;
	ss << a;
	return ss.str();
}

std::vector<Arete*> Sommet::Prim(int indicePoids)
{
	//Creation des type de données utiles à l'algorithme de Prim
	std::vector<Arete*> aretePrim; //Vecteur des arretes pour Prim
	std::list<Arete*> areteDecouverte; //Liste des arretes déjà decouvertes
	std::vector<Sommet*> sommetPrim; //Tableau des sommets ou l'on est déjà passé
	sommetPrim.push_back(this); //On ajoute le sommet de depart au vecteur de sommet
	do
	{
		for (auto arete : sommetPrim.back()->m_voisins)//On check les voisins du dernier sommet ajouté
		{
			//
			bool present = false; // Si l'arrete est deja presente dans le graphe
			bool sommet1 = false; //1er sommet de l'arete en cours de verification
			bool sommet2 = false; //2eme sommet de l'arete en cours de verification
			for (auto sommetDejaAjoute : sommetPrim) //On parcours la liste des sommets déjà ajoutée dans le graphe
			{
				if (arete.second->getSommets().first == sommetDejaAjoute) //Si le premier sommet est déjà dans le graphe
					sommet1 = true; //On dit que le sommet 1 est dans le graphe
				if (arete.second->getSommets().second == sommetDejaAjoute) //Si le deuxieme sommet est déjà dans le graphe
					sommet2 = true; //On dit que le sommet 2 est dans le graphe
				if (sommet1 && sommet2) //Si les deux sommets de l'arrete sont dans le graphe alors l'arrete est déjà dans le graphe
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
							ajout = true; //On dit qu'elle a été ajouté pour ne stoper la boucle
							break;
						}
					}
					if (!ajout) //Si elle n'a pas été ajouté à la fin c'est qu'elle est de poid superieur aux autres
						areteDecouverte.push_back(arete.second); //On l'ajoute donc à la fin
				}
			}
		}
		bool sommet1 = false; //On remet les booleen à false une fois utilisés
		bool sommet2 = false;
		for (auto sommetDansPrim : sommetPrim) //On verifie qu'il n'y a pas de cycle
		{
			if (areteDecouverte.front()->getSommets().first == sommetDansPrim) //On verifie si le 1er sommet est dans le graphe
				sommet1 = true;
			if (areteDecouverte.front()->getSommets().second == sommetDansPrim) //On vérifie si le 2ème sommet est dans le graphe
				sommet2 = true;
			if (sommet1 && sommet2) //Il y a un cycle si les deux sommets sont déjà dans le graphe
			{
				areteDecouverte.pop_front(); //Si il y a un cycle on supprimme l'arete
				break;
			}
		}
		if (!sommet1 || !sommet2) //Si il n'y a pas de cycle on ajoute l'arete
		{
			aretePrim.push_back(areteDecouverte.front()); //On ajoute la premiere arrete de la pile dans le graphe
			//On ajoute le nouveau sommet au vecteur
			for (auto sommet : sommetPrim) //On parcourt les sommets déjà present
			{
				if (areteDecouverte.front()->getSommets().first == sommet) //Si le sommet 1 est deja present
					sommetPrim.push_back(areteDecouverte.front()->getSommets().second); //Alors c'est le sommet 2 qui n'y était pas encore
				if(areteDecouverte.front()->getSommets().second == sommet) //Si le sommet 2 est deja present
					sommetPrim.push_back(areteDecouverte.front()->getSommets().first); //Alors c'est le sommet 1 qui n'y était pas encore
			}
			areteDecouverte.pop_front(); //Une fois l'arrete ajouté on l'enleve de la pile
		}
		if (areteDecouverte.empty()) //Si la pile est vide, on sort de la boucle pour gagner du temps
			break;

	} while (!areteDecouverte.empty()); //Tant que la pile n'est pas vide on continu


	return aretePrim; //On retourne un vecteur d'arrete pour parcourir le graphe en faisant le chemin de poid minimal
}

///\fn std::pair<std::vector<const Arete*>, float> Sommet::Dijkstra(int nombreSommets,int indicePoids, const Sommet* arrivee, std::bitset<nombreMaxAretes> grapheDeTravail, int choix2emeRetour) const
///\brief Fonction permettant de faire tourner l'algorithme de Dijkstra à partir d'un sommet donné
///\param nombreSommets Le nombre de Sommets à explorer (nombre de sommets du graphe)
///\param indicePoids L'indice de poids sur lequel on fait Dijkstra, car les arêtes ont plusieurs poids
///\param arrivee Si un sommet d'arrivée est indiqué, la fonction renverra le plus court chemin entre le sommet initial et le sommet arrivee
///\param grapheDeTravail Suite de bits qui renseigne quelles arêtes du graphe complet doivent être prises en compte pour effectuer Dijkstra
///\param choix2emeRetour Permet de choisir si l'on veut récupérer le poids total des arêtes ou le plus long chemin obtenu avec la fonction
///\return Retourne une paire contenant les arêtes en suivant Dijkstra depuis le sommet initial et un float qui peut être le poids total des arêtes ou le plus long chemin
/// choix2emeRetour permet de choisir ce qui sera dans le float de la paire retournée. 1 -> poids total    2 -> plus long des pcc
std::pair<std::vector<const Arete*>, float> Sommet::Dijkstra(int nombreSommets,int indicePoids, const Sommet* arrivee, std::bitset<nombreMaxAretes> grapheDeTravail, int choix2emeRetour) const
{
	std::vector<const Arete*> dijkstraTous = {}, dijkstraArrivee = {}; /// dijkstraTous : arêtes de tous les pcc vers tous les sommets ; dijkstraArrivee : arêtes de this à arrivée
	std::vector<float> distancesFinales = {};
	std::unordered_set<const Sommet*> sommetsMarques = {};
	std::unordered_map<const Sommet*, float> distances = {};		/// second = distance de first par rapport à this
	std::unordered_map<const Sommet*, const Sommet*> predecesseurs = {}; /// second = predecesseur de first
	const Sommet* somMarq = nullptr;	/// Pointeur pour le sommet qui sera marqué à chaque tour 
	const Sommet* pred1, * pred2;		/// Pour le dijkstraArrivee
	std::pair<const Sommet*, float> SomLePlusLoin;			/// Indique le sommet le plus éloigné du this, ainsi que sa distance
	float distanceMin, distance, distanceMax = 0.0;				/// Permet de comparer les distances pour marquer un sommet
	sommetsMarques.insert(this);			/// On marque le sommet de départ
	for (const auto s : m_voisins)				/// On ajoute la distance de chaque voisin du sommet de départ
	{										/// et on renseigne que this est son prédécesseur
	
		if (grapheDeTravail[s.second->getId()]) /// Si l'arête est comprise dans le graphe de travail
		{
			//std::cout << "indice poids : " << indicePoids << "\n";
			distances.insert({ s.first, s.second->getPoids(indicePoids) }); /// On l'ajoute aux distances
			predecesseurs.insert({ s.first, this });	/// et on ajoute le sommet aux predecesseurs
		}
	}

	/// Tous les sommets sont non marqués, sauf le this
	///Sélectionner et marquer le sommet ayant la plus petite distance au sommet initial
	while (sommetsMarques.size() < nombreSommets)  /// Tant qu'il reste des sommets non marqués
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
		//std::cout <<"Distance entre "<< getId() <<" et "<< somMarq->getId() << " : "<< distances.find(somMarq)->second << std::endl;
		if(distances.find(somMarq)->second>SomLePlusLoin.second)
			SomLePlusLoin.first = somMarq;
		distancesFinales.push_back(distances.find(somMarq)->second);
		dijkstraTous.push_back(predecesseurs.find(somMarq)->second->m_voisins.find(somMarq)->second); /// Ajout de l'arête 
		/// On met à jour les distances avec le nouveau sommet marqué
		for (const auto v : somMarq->m_voisins) /// Pour chaque voisin du sommet marqué v est une paire (Sommet *, Arete*)
		{
			if (grapheDeTravail[v.second->getId()])
			{
				/// Mise à jour de la distance de chaque voisin
				/// si d(somMarq) + poids (somMarq - v) < d(v)
				if (sommetsMarques.count(v.first) == 0)
				{
					distance = distances.find(somMarq)->second + somMarq->m_voisins.find(v.first)->second->getPoids(indicePoids);
					if (distances.count(v.first) == 0 || distance < distances.find(v.first)->second)  /// Si le voisin n'a pas de distance dans distances, on l'ajoute
					{
						predecesseurs[v.first] = somMarq;	/// somMarq devient le prédécesseur de v
						distances[v.first] = distance;		/// et on met à jour la distance de v qui vaut alors d(somMarq) + poids (somMarq - v)
					}
				}
			}
		}
		distances.erase(somMarq);			/// Une fois que j'ai marqué un sommet je dois l'enlever de distances, sinon il sera marqué encore
	}

	if (arrivee == nullptr) /// Quand aucun sommet d'arrivée n'est indiqué
	{
		if (choix2emeRetour == 1) /// On retourne toutes les arêtes marquées et le poids total de celles-ci
		{
			return { dijkstraTous, std::accumulate(distancesFinales.cbegin(), distancesFinales.cend(), 0.0) };
		}
		else if (choix2emeRetour == 2) /// Ou uniquement les arêtes du sommet le plus loin au sommet initial ainsi que sa distance
		{
			pred1 = SomLePlusLoin.first;
			pred2 = predecesseurs.find(SomLePlusLoin.first)->second;
			dijkstraArrivee.push_back(pred2->m_voisins.find(pred1)->second);
			while (pred2 != this)
			{
				pred1 = pred2;
				pred2 = predecesseurs.find(pred2)->second;
				dijkstraArrivee.push_back(pred2->m_voisins.find(pred1)->second);
			}
			return { dijkstraArrivee, *std::max_element(distancesFinales.cbegin(), distancesFinales.cend()) };
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
		return { dijkstraArrivee, 0.0 }; /// Pour ce cas on ne s'intéresse pas à la longueur du chemin
	}
}

///\fn float Sommet::Dijtances(std::bitset<nombreMaxAretes> ssg, int indicePoids, int nbSommets)
///\brief Fonction qui calcule la somme des poids des arêtes comprises lorsque l'on effectue Dijkstra depuis un sommet
///\param ssg Suite de bits indiquant le sous graphe de travail issu du graphe complet
///\param indicePoids Indique sur quel poids on effectue les calculs
///\param nbSommets Indique le nombre de sommets du graphe
///\return Renvoie la somme des poids des arêtes
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

///\fn bool compDistDij(std::pair<const Sommet*, float> s1, std::pair<const Sommet*, float> s2)
///\brief Fonction utilisée dans Dijtances pour trier un conteneur
///\param s1 Premier élément à comparer, paire constituée d'un pointeur sur sommet et d'un float
///\param s2 Deuxième élément à comparer, paire constituée d'un pointeur sur sommet et d'un float
///\return Rend un booléen selon quel float est plus grand que l'autre
bool compDistDij(std::pair<const Sommet*, float> s1, std::pair<const Sommet*, float> s2)
{
	return (s1.second < s2.second);
}

///\fn const Coords Sommet::getCoords() const
///\brief Fonction utilisée pour récupérer les coordonnées d'un sommet
///\return Retourne les coordonnées du sommet en question
const Coords Sommet::getCoords() const
{
	return m_coords;
}

///\fn const int Sommet::getId() const
///\brief Fonction utilisée pour récupérer l'id d'un sommet
///\return Retourne l'id du sommet en question
const int Sommet::getId() const
{
	return m_id;
}

///\fn int Sommet::BFSnbAretes(int nbSommets, std::bitset<nombreMaxAretes> ssg)
///\brief Fonction utilisée pour compter le nombre d'arêtes d'une composante connexe, en utilisant l'algorithme du BFS
///\param nbSommets Le nombre de Sommets du graphe
///\param ssg Le sous-graphe de travail
///\return Retourne un entier qui correspond au nombre d'arêtes de la composante connexe
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
			if (!discovered[s.first->m_id] && ssg[s.second->getId()]) //Si le sommet n'est pas découvert et si l'arete est dans le graphe
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

///\fn int Sommet::tailleComposanteConnexe(int nbSommets, std::bitset<nombreMaxAretes> ssg)
///\brief Fonction utilisée pour compter la taille que fait une composante connexe en partant d'un sommet
///\param nbSommets Le nombre de Sommets du graphe
///\param ssg Le sous-graphe de travail
///\return Retourne un entier qui correspond à la taille de la composante connexe du sommet initial
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

///\fn bool Sommet::avoisineCol(int color, std::bitset<nombreMaxAretes> ssg) const
///\brief Fonction utilisée pour savoir si un sommet a la même couleur qu'un de ses voisins
///\param color La couleur à tester
///\param ssg Sous-graphe de travail, toutes les arêtes ne sont pas prises en compte
///\return Retourne un booléen selon si le sommet a la même couleur qu'un de ses voisins
bool Sommet::avoisineCol(int color, std::bitset<nombreMaxAretes> ssg) const
{
	for (auto s : m_voisins)
	{
		if (ssg[s.second->getId()] && s.first->m_color == color)
			return true;
	}
	return false;
}

///\fn const int Sommet::getOrdre() const
///\brief Fonction utilisée pour récupérer l'ordre d'un sommet
///\return Retourne l'ordre du sommet en question
const int Sommet::getOrdre() const
{
	return m_voisins.size();
}

///\fn Sommet::~Sommet()
///\brief Fonction utilisée pour détruire un sommet
Sommet::~Sommet()
{
}
