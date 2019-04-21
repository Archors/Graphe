
///
///\file Graphe.cpp
///
///\brief Appels principaux des fonctions effectuant des actions sur un graphe
///\date 21 avril 2019
///
///		Contient le code de chargement d'un graphe depuis un fichier
///		Contient l'appel des algorithmes comme Prime et Dijkstra
///		Contient l'algorithme de Pareto et ses trois calculs de couts (normal, distance optimise, plus long chemin optimise)
///		Contient tout ce qui a attrait au graphe en surface comme les affichages sur des bitmaps


#include "Graphe.h"
#include "Menu.h"

///\fn Graphe::Graphe (MenuDonnees choix)
///\brief charge un graphe depuiz un fichier
///\param choix effectues dans le menu concernant le graphe et l'algo choisi
///
///Fonction originaire du code du TP2 fourni par M. Fercoq puis modifiée
Graphe::Graphe(MenuDonnees choix)
{
	std::cout << "\n\n\n ===== " << choix.graphe << " =====\n";
	std::ifstream ifs{ choix.graphe+".txt" };

	if (!ifs)
		throw std::runtime_error("Impossible d'ouvrir en lecture " + choix.graphe);

	std::ifstream ifs2{ choix.graphe + "_weights_" + choix.poid + ".txt" };
	if (ifs2.fail())
		throw std::runtime_error("Probleme lecture taille du graphe");


	int ordre;
	ifs >> ordre;
	
	if (ifs.fail())
		throw std::runtime_error("Probleme lecture ordre du graphe");


	int id;
	double x, y;

	//lecture des sommets
	for (int i = 0; i < ordre; ++i)
	{
		ifs >> id; if (ifs.fail()) throw std::runtime_error("Probleme lecture id");
		ifs >> x; if (ifs.fail()) throw std::runtime_error("Probleme lecture x");
		ifs >> y; if (ifs.fail()) throw std::runtime_error("Probleme lecture y");
		m_sommets.push_back(new Sommet{id,x,y});
		//std::cout << m_sommets[i]->getId() << std::endl;
	}

	int taille;
	ifs >> taille;
	if (ifs.fail())
		throw std::runtime_error("Probleme lecture taille du graphe");

	int taille2;
	ifs2 >> taille2;
	if (ifs2.fail())
		throw std::runtime_error("Probleme lecture nombre d'aretes");

	if (taille != taille)
		throw std::runtime_error("Incompatibilité entre les données des sommets et des aretes");

	int nbPoids;
	ifs2 >> nbPoids;
	if (ifs2.fail())
		throw std::runtime_error("Probleme lecture nombre de poids");

	int id_voisin;
	int id_ar;
	double poids;

	//lecture des aretes
	for (int i = 0; i < taille; ++i)
	{
		std::vector<float> vectPoids;
		//lecture des ids des deux extrémités
		ifs >> id; if (ifs.fail()) throw std::runtime_error("Probleme lecture id arete");
		ifs2 >> id_ar; if (ifs.fail()) throw std::runtime_error("Probleme lecture id arete");
		if (id != id_ar) throw std::runtime_error("Probleme aretes non correspondantes");

		ifs >> id; if (ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
		ifs >> id_voisin; if (ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");

		for (int j=0; j<nbPoids; ++j)
		{
			ifs2 >> poids; if (ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
			vectPoids.push_back(poids);
			//std::cout << poids << " ";
		}
		//std::cout << "\n";

		m_aretes.push_back( new Arete{ id_ar, m_sommets[id], m_sommets[id_voisin], vectPoids, choix.oriente } );

		if (!choix.oriente)
		{
			//std::cout << id << " <--> " << id_voisin << std::endl;
			m_sommets[id]->AjouterVoisin( m_sommets[id_voisin], m_aretes[id_ar] );
			m_sommets[id_voisin]->AjouterVoisin( m_sommets[id], m_aretes[id_ar] );
		}
		else
			m_sommets[id]->AjouterVoisin(m_sommets[id_voisin], m_aretes[id_ar]);
		
	}

	m_typeTriPareto = choix.poids;
	m_avecCycles = choix.cycle;
	m_oriented = choix.oriente;
	m_diametre = choix.diametre;
	m_colors.push_back(al_map_rgb(255, 255, 255));

	ifs.close();
	ifs2.close();
}

///\fn std::vector<<std::bitset<nombreMaxAretes>> Graphe::DeterminerSousGraphe ()
///\brief trouve tous les sous graphe connexe avec ou sans cycle du graphe chargé
///\param aucun
///\return renvoie tous les sous graphes trouvés
///
std::vector<std::bitset<nombreMaxAretes>> Graphe::DeterminerSousGraphe()
{
	std::vector<std::bitset<nombreMaxAretes>> grapheResults;
	double start = al_get_time();

	std::cout << "Looking for every graph possible...\n";

	int minAretes = m_sommets[0]->BFSnbAretes( getNombreSommets(), std::bitset<nombreMaxAretes>(pow(2, getNombreAretes()) - 1) );
	//std::cout << "Min ar : " << minAretes << std::endl;

	int imax = pow(2, getNombreAretes());
	int i = pow(2, minAretes) - 1;
	while (i < imax)
	{
		std::bitset<nombreMaxAretes> ssg;

		int nbar = (int)(ssg = std::bitset<nombreMaxAretes>(++i)).count();

		if ((nbar >= minAretes && m_avecCycles) || (nbar == minAretes && !m_avecCycles))
		{
			if (!m_oriented)
			{
				if (isConnexe(ssg, m_sommets[0]))
					grapheResults.push_back(ssg);
			}
			else
			{
				bool fortementConnexe = true;
				for (auto s : m_sommets)
				{
					if (!isConnexe(ssg, s))
					{
						fortementConnexe = false;
						break;
					}
				}
				if (fortementConnexe)
					grapheResults.push_back(ssg);
			}
			
		}
	}

	std::cout << "Done ! (" << al_get_time() - start << " sec)\n";

	return grapheResults;
}


bool Graphe::isConnexe(std::bitset<nombreMaxAretes> ssg, Sommet* depart)
{
	return !(depart->tailleComposanteConnexe(getNombreSommets(), ssg) < getNombreSommets());
}


std::bitset<nombreMaxAretes> Graphe::Prim(int poids, int sommetDepart)
{
	if (sommetDepart < 0 || sommetDepart > getNombreSommets() - 1)
		sommetDepart = 0;
	if (poids < 0 || poids > m_aretes[0]->getNombrePoids() - 1)
		poids = 0;

	std::cout << "Lancement prim depuis le sommet " << sommetDepart << " selon le poids " << poids << "...\n";

	std::vector<Arete*> aretePrim = m_sommets[sommetDepart]->Prim(poids);

	std::cout << "Nombre d'arretes minimal : " << aretePrim.size() << std::endl;

	std::bitset<nombreMaxAretes> ssg;

	for (auto a : aretePrim)
		ssg[a->getId()] = 1;

	std::cout << "Graphe de poids minimal trouve\n";

	return ssg;
}


std::bitset<nombreMaxAretes> Graphe::Dijkstra(int poids, int sommetDepart, int sommetArrivée, std::bitset<nombreMaxAretes> ssg, bool trajetMax)
{
	//std::cout << "Dijkstra : " << sommetDepart << "->" << sommetArrivée << "\n";
	if (sommetDepart < 0 || sommetDepart > getNombreSommets() - 1)
		sommetDepart = 0;
	if (sommetArrivée < 0 || sommetArrivée > getNombreSommets() - 1)
		sommetArrivée = -1;
	if (poids < 0 || poids > m_aretes[0]->getNombrePoids() - 1)
		poids = 0;

	//std::cout << "Lancement Dijkstra depuis le sommet " << sommetDepart << "jusqu'au sommet (-1 pour tous) " << sommetArrivée << " selon le poids " << poids << "...\n";

	std::vector<const Arete*> areteDijkstra = m_sommets[sommetDepart]->Dijkstra(getNombreSommets(), poids, ((sommetArrivée!=-1)?m_sommets[sommetArrivée]:nullptr), ssg, ((trajetMax)?2:1)).first;

	std::bitset<nombreMaxAretes> ssg2;

	for (auto a : areteDijkstra) 
		ssg2[a->getId()] = 1;

	return ssg2;
}


std::list<graphePareto> Graphe::TriPareto()
{
	std::vector<std::bitset<nombreMaxAretes>> tousSsG = DeterminerSousGraphe();

	const int nbPoids = m_aretes[0]->getNombrePoids();
	//std::cout << "Nombre de poids : " << nbPoids << "\n";

	for (auto ssg : tousSsG)
	{
		std::vector<float> sommePoids;
		if (m_typeTriPareto.count() == 0)
			sommePoids = sommePoidsCoutMin(ssg);
		else if (m_diametre)
			sommePoids = sommePoidsDiametre(ssg);
		else
			sommePoids = sommePoidsCoutDist(ssg);

		m_souGraphePareto.push_back(graphePareto{ sommePoids, ssg });
	}

	m_souGraphePareto.sort(compGraphesPareto);
	
	/*for (auto g : m_souGraphePareto)
	{
		std::cout << g.aretes;
		std::cout << " (" << g.sommePoids[0] << "; " << g.sommePoids[1] << "; " << g.sommePoids[2] << ")\n";
	}*/

	std::vector<float> min;
	for (auto f : m_souGraphePareto.front().sommePoids)
			min.push_back(f);	

	std::list<graphePareto>::iterator i = m_souGraphePareto.begin();
	std::vector<std::list<graphePareto>::iterator> lastmin;
	for (int m = 1; m<nbPoids; m++)
		lastmin.push_back(i);

	while (i != m_souGraphePareto.end())
	{
		//std::cout << i->aretes << " : " << i->sommePoids[0] << " " << i->sommePoids[1] << " " << i->sommePoids[2] << std::endl;

		bool supp = true;
		for (int k = 1; k < nbPoids; k++)
		{
			//for (int c = 0; c < nombreMaxPoids; c++)
			//	std::cout << i->sommePoids[c] << " ";
			//std::cout << "\n" << k << " : " << i->sommePoids[k] << " - " << min[k] << std::endl;


			if (i->sommePoids[k] < min[k]) //On a trouvé un poids minimal (c'est le graphe qui a le plus petit poids k, c'est donc un optima de Pareto
			{
				int km = k - 1;
				min[k] = i->sommePoids[k];
				supp = false;
				if (lastmin[km]->sommePoids[0] == i->sommePoids[0]) //Si on a trouvé un minimal et que le premier poids est le même que le précedent graphe avec ce poids minimal il faut effacer l'ancien graphe
				{
					if (nbPoids > 2) //Pour passer tout ça comme c'est impossible d'avoir un double si il n'y a qu'une valeur dans le vector
					{
						int multipleMin = 0;
						for (auto m : lastmin) //On check si le graphe avec ce poids minimal n'a pas un autre poids minimal
						{
							if (m == lastmin[km])
								multipleMin++;
						}
						if (multipleMin < 1) //Si c'est son seul poids minimal on peut l'effacer
							m_souGraphePareto.erase(lastmin[km]);
					}
					else
						m_souGraphePareto.erase(lastmin[0]);
				}
					
				lastmin[km] = i; //Le graphe détenteur du poids minimal k est le graphe actuel (i pointe sur lui)
			}
		}

		

		if (supp && i != m_souGraphePareto.begin()) m_souGraphePareto.erase(i++);
		else ++i;
	}

	
	/*
	std::cout << "Les optimums de Pareto trouves : \n";
	for (auto g : m_souGraphePareto)
	{
		std::cout << g.aretes << " :";
		for (auto p : g.sommePoids)
			std::cout << " " << p;
		std::cout << "\n";
	}
	*/
		
	std::cout << m_souGraphePareto.size() << " graphes (sur " << tousSsG.size() << ")\n";
		
	return m_souGraphePareto;
}

bool compGraphesPareto(graphePareto g1, graphePareto g2)
{
	if (g1.sommePoids.size() > 0 && g2.sommePoids.size() > 0)
	{
		if (g1.sommePoids[0] < g2.sommePoids[0])
			return true;
	}
	
	return false;
}


std::vector<float> Graphe::sommePoidsCoutMin(std::bitset<nombreMaxAretes> ssg)
{
	const int nbPoids = m_aretes[0]->getNombrePoids();

	std::vector<float> sommePoids;
	sommePoids.resize(nbPoids);

	for (int i = 0; i < getNombreAretes(); i++)
	{
		if (ssg[i])
		{
			for (int j = 0; j < nbPoids; j++)
				sommePoids[j] += m_aretes[i]->getPoids(j);
		}

	}

	return sommePoids;
}


std::vector<float> Graphe::sommePoidsDiametre(std::bitset<nombreMaxAretes> ssg)
{
	const int nbPoids = m_aretes[0]->getNombrePoids();

	std::vector<float> sommePoids;
	sommePoids.resize(nbPoids);

	for (int j = 0; j < nbPoids; j++)
	{
		if (!m_typeTriPareto[j])
		{
			for (int i = 0; i < getNombreAretes(); i++)
			{
				if (ssg[i])
				{
					sommePoids[j] += m_aretes[i]->getPoids(j);
				}
			}
		}
		else
		{
			sommePoids[j] = 0;
			for (int i = 0; i < getNombreSommets(); i++)
			{
				float dist = m_sommets[i]->Dijkstra(getNombreSommets(), j, nullptr, ssg, 2).second;
				if (dist > sommePoids[j])
					sommePoids[j] = dist;
			}
		}

	}

	return sommePoids;
}

std::vector<float> Graphe::sommePoidsCoutDist(std::bitset<nombreMaxAretes> ssg)
{
	const int nbPoids = m_aretes[0]->getNombrePoids();

	std::vector<float> sommePoids;
	sommePoids.resize(nbPoids);
	
	for (int j = 0; j < nbPoids; j++)
	{
		if (!m_typeTriPareto[j])
		{
			for (int i = 0; i < getNombreAretes(); i++)
			{
				if (ssg[i])
				{
					sommePoids[j] += m_aretes[i]->getPoids(j);
				}
			}
		}
		else
		{
			for (int i = 0; i < getNombreSommets(); i++)
			{
				sommePoids[j] += m_sommets[i]->Dijtances(ssg, j, getNombreSommets());
			}
		}
		
	}

	return sommePoids;
}


void Graphe::Colorer(std::bitset<nombreMaxAretes> ssg)
{
	if (!m_oriented)
	{
		std::list<somOrdre> sommets;
		for (auto s : m_sommets)
		{
			sommets.push_back(somOrdre{ s->getOrdre(), s });
			s->m_color = 0;
		}
			

		sommets.sort(compSomOrdre);

		for (auto s : sommets)
		{
			int col = 0;
			do
			{
				col++;
			} while (s.sommet->avoisineCol(col, ssg));
			s.sommet->m_color = col;
		}
	}
}

bool compSomOrdre(somOrdre s1, somOrdre s2)
{
	return (s1.ordre > s2.ordre);
}


void Graphe::createColors()
{
	srand(time(NULL));

	for (int i = 0; i < getNombreSommets(); i++)
		m_colors.push_back(al_map_rgb(rand() % 255, rand() % 255, rand() % 255));

}


ALLEGRO_BITMAP* Graphe::DessinerGraphe()
{
	std::bitset<nombreMaxAretes> aretes = std::bitset<nombreMaxAretes>(pow(2,getNombreAretes())-1);

	return DessinerSousGraphe(aretes);
}

ALLEGRO_BITMAP* Graphe::DessinerSousGraphe(std::bitset<nombreMaxAretes> aretes)
{
	int width = 0;
	int min = m_sommets[0]->getCoords().getX();
	for (auto sommet : m_sommets)
	{
		if (sommet->getCoords().getX() > width)
			width = sommet->getCoords().getX();
		if (sommet->getCoords().getY() > width)
			width = sommet->getCoords().getY();
		if (sommet->getCoords().getX() < min)
			min = sommet->getCoords().getX();
		if (sommet->getCoords().getY() < min)
			min = sommet->getCoords().getY();
	}

	ALLEGRO_BITMAP* dessin = al_create_bitmap(width + min, width + min);

	al_set_target_bitmap(dessin);
	al_clear_to_color(al_map_rgb(255, 210, 180));

	int i = 0;
	for (auto arete : m_aretes)
	{
		if (aretes[i])
			arete->Dessiner(dessin);
		i++;
	}
		
	for (auto sommet : m_sommets)
		sommet->Dessiner(dessin, m_colors);


	return dessin;
}

ALLEGRO_BITMAP* Graphe::DessinerSousGraphePar(graphePareto ssg)
{
	ALLEGRO_BITMAP* bmp = DessinerSousGraphe(ssg.aretes);
	ALLEGRO_FONT* font;
	font = al_load_font("simple_font.ttf", 40, 0);

	al_set_target_bitmap(bmp);

	std::string toAff="";
	int i = 0;
	for (auto poids : ssg.sommePoids)
	{
		std::ostringstream strs;
		strs << poids;
		toAff = toAff + ((i) ? "; " : "") + strs.str();
		i = 1;
	}

	al_draw_text(font, al_map_rgb(50, 50, 50), 5, 5, ALLEGRO_ALIGN_LEFT, toAff.c_str());

	al_destroy_font(font);

	return bmp;
}

ALLEGRO_BITMAP* Graphe::DessinerPlusLongDiametre(std::bitset<nombreMaxAretes> ssg)
{
	const int nbPoids = m_aretes[0]->getNombrePoids();

	float distMax = 0;
	int indiceDuGraphe;
	std::bitset<nombreMaxAretes> grapheAafficher;
	//std::bitset<nombreMaxAretes> graphePlusLongTrajet;

	for (int j = 0; j < nbPoids; j++)
	{
		if (m_typeTriPareto[j])
		{
			distMax = 0;
			for (int i = 0; i < getNombreSommets(); i++)
			{
				float dist = m_sommets[i]->Dijkstra(getNombreSommets(), j, nullptr, ssg, 2).second;
				if (dist > distMax)
				{
					distMax = dist;
					grapheAafficher = Dijkstra(j, i, -1, ssg, true);
				}
					
			}
		}

	}

	return DessinerSousGraphe(grapheAafficher);
}




const int Graphe::getNombreSommets()
{
	return (int)m_sommets.size();
}

const int Graphe::getNombreAretes()
{
	return (int)m_aretes.size();
}

const int Graphe::getNombreSousGraphe()
{
	return (int)m_souGraphePareto.size();
}


void Graphe::free()
{
	std::vector<Sommet*> freeS;

	for (auto s : m_sommets)
		delete s;
	m_sommets.swap(freeS);
	m_sommets.clear();
	freeS.clear();

	std::vector<Arete*> freeA;

	for (auto a : m_aretes)
		delete a;
	m_aretes.swap(freeA);

	m_aretes.clear();
	freeA.clear();

	std::list<graphePareto> freeG;
	m_souGraphePareto.swap(freeG);

	m_souGraphePareto.clear();
	freeA.clear();
}


Graphe::~Graphe()
{
}