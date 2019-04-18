#include "Graphe.h"

//Fonction originaire du code du TP2 fourni par M. Fercoq puis modifiée
Graphe::Graphe(std::string nomFichier, const bool oriented, std::bitset<nombreMaxPoids> typeTriPareto)
	: m_typeTriPareto{ typeTriPareto }
{
	std::ifstream ifs{ nomFichier+".txt" };


	if (!ifs)
		throw std::runtime_error("Impossible d'ouvrir en lecture " + nomFichier);

	std::ifstream ifs2{ nomFichier + "_weights_0.txt" };
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
		std::cout << m_sommets[i]->getId() << std::endl;
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
		}

		m_aretes.push_back( new Arete{ id_ar, m_sommets[id], m_sommets[id_voisin], vectPoids, oriented } );

		if (!oriented)
		{
			std::cout << id << " <--> " << id_voisin << std::endl;
			m_sommets[id]->AjouterVoisin( m_sommets[id_voisin], m_aretes[id_ar] );
			m_sommets[id_voisin]->AjouterVoisin( m_sommets[id], m_aretes[id_ar] );
		}
		else
			m_sommets[id]->AjouterVoisin(m_sommets[id_voisin], m_aretes[id_ar]);
		
	}

	ifs.close();
	ifs2.close();
}

std::vector<std::bitset<nombreMaxAretes>> Graphe::DeterminerSousGraphe(bool avecCycles)
{
	std::vector<std::bitset<nombreMaxAretes>> tousLesSousGraphes;

	std::cout << "Looking for every graph possible...\n";

	int minAretes = (int)m_sommets[0]->BFS(getNombreSommets(), (std::bitset<nombreMaxAretes>(pow(2, getNombreAretes()) - 1).to_string().substr((size_t) nombreMaxAretes - (size_t)getNombreAretes(), nombreMaxAretes-1))).size();
	std::cout << "Min ar : " << minAretes << std::endl;

	int pr = -1;
	for (int i = 0; i < pow(2, getNombreAretes()); i++)
	{
		std::bitset<nombreMaxAretes> ssg = std::bitset<nombreMaxAretes>(i);
		
		int nbar = ssg.count();
		if ( (nbar >= minAretes && avecCycles) || (nbar == minAretes && !avecCycles) )
		{
			//std::cout << ssg.count() << std::endl;
			if (isConnexe(ssg))
			{
				//std::cout << ssg << " Found one !\n";
				tousLesSousGraphes.push_back(ssg);
			}
		}
		
		
		if ( (int)(((int)100 * i) / (int)(pow(2, getNombreAretes()) - 1)) > pr)
		{
			pr = ((int)100 * i) / (int)(pow(2, getNombreAretes()) - 1);
			std::cout << pr << "%\n";
		}
			
		//std::cout << i << " : " << tousLesSousGraphes.back() << std::endl;
	}

	std::cout << "Done !\n";

	return tousLesSousGraphes;
}


bool Graphe::isConnexe(std::bitset<nombreMaxAretes> ssg)
{
	if (m_sommets[0]->tailleComposanteConnexe(getNombreSommets(), ssg) < getNombreSommets())
		return false;
	return true;
}


std::bitset<nombreMaxAretes> Graphe::Prim()
{
	std::cout << "Lancement prim depuis le sommet 0...\n";

	std::vector<Arete*> aretePrim = m_sommets[0]->Prim(0);

	std::bitset<nombreMaxAretes> ssg;

	std::cout << "Nombre d'arretes minimal : " << aretePrim.size() << std::endl;

	for (auto a : aretePrim)
		ssg[a->getId()] = 1;

	std::cout << "Graphe de poids minimal trouve\n";

	return ssg;
}


std::bitset<nombreMaxAretes> Graphe::Dijkstra()
{
	std::cout << "Lancement de dijkstra depuis le sommet 0...\n";

	std::vector<const Arete*> areteDijkstra = m_sommets[0]->Dijkstra(getNombreSommets(), 0);

	std::bitset<nombreMaxAretes> ssg;

	std::cout << "Nombre d'arretes minimal pour tout relier en partant de 0 : " << areteDijkstra.size() << std::endl;

	for (auto a : areteDijkstra)
		ssg[a->getId()] = 1;

	std::cout << "Graphe de poids minimal trouve\n";

	return ssg;
}


std::vector<std::bitset<nombreMaxAretes>> Graphe::TriPareto()
{
	bool avecCycle = false;
	if (m_typeTriPareto.count() > 0)
		avecCycle = true;

	std::vector<std::bitset<nombreMaxAretes>> tousSsG = DeterminerSousGraphe(avecCycle);
	std::list<graphePareto> tousGraphePareto;

	const int nbPoids = m_aretes[0]->getNombrePoids();

	for (auto ssg : tousSsG)
	{
		std::vector<float> sommePoids;
		if (m_typeTriPareto.count() == 0)
			sommePoids = sommePoidsCoutMin(ssg);
		else
			sommePoids = sommePoidsCoutDist(ssg);

		tousGraphePareto.push_back(graphePareto{ ssg, sommePoids });
	}

	tousGraphePareto.sort(compGraphesPareto);
	/*for (auto g : tousGraphePareto)
	{
		std::cout << g.aretes;
		std::cout << " (" << g.sommePoids[0] << "; " << g.sommePoids[1] << ")\n";
	}*/

	std::vector<float> min;
	for (auto f : tousGraphePareto.front().sommePoids)
		min.push_back(f);

	std::list<graphePareto>::iterator i = tousGraphePareto.begin();
	std::list<graphePareto>::iterator lastmin = i;

	while (i != tousGraphePareto.end())
	{
		//std::cout << i->aretes << " : " << i->sommePoids[0] << " " << i->sommePoids[1] << std::endl;

		bool supp = true;

		for (int k = 1; k < nbPoids; k++)
		{
			//std::cout << i->sommePoids[k] << " - " << min[k] << std::endl;
			if (i->sommePoids[k] < min[k])
			{
				min[k] = i->sommePoids[k];
				supp = false;
				if (lastmin->sommePoids[0] == i->sommePoids[0])
				{
					tousGraphePareto.erase(lastmin);
				}
				lastmin = i;
			}
		}

		if (supp && i != tousGraphePareto.begin()) tousGraphePareto.erase(i++);
		else 
		{
			if (i->sommePoids[0] == tousGraphePareto.begin()->sommePoids[0] && i != tousGraphePareto.begin())
			{
				tousGraphePareto.erase(tousGraphePareto.begin());
				std::cout << "First has been erased from existence \n";
			}
				
			//std::cout << i->aretes << std::endl;
			++i;
		}		
	}

	std::cout << "Les optimums de Pareto trouves : \n";
	for (auto g : tousGraphePareto)
	{
		std::cout << g.aretes << " : " << g.sommePoids[0] << " " << g.sommePoids[1] << std::endl;
		m_souGraphePareto.push_back(g.aretes);
	}
		
	std::cout << tousGraphePareto.size() << " graphes (sur " << tousSsG.size() << ")\n";
		
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
				std::vector<const Arete*> grapheDijkstra = m_sommets[i]->Dijkstra(getNombreSommets(), j, ssg);
				
				for (auto a : grapheDijkstra)
					sommePoids[j] += a->getPoids(j);
			}
		}
		
	}

	return sommePoids;
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
	al_clear_to_color(al_map_rgb(180, 230, 150));

	int i = 0;
	for (auto arete : m_aretes)
	{
		if (aretes[i])
			arete->Dessiner(dessin);
		i++;
	}
		
	for (auto sommet : m_sommets)
		sommet->Dessiner(dessin);


	return dessin;
}

ALLEGRO_BITMAP* Graphe::DessinerSousGraphePar(int id)
{
	if (id < m_souGraphePareto.size())
		DessinerSousGraphe(m_souGraphePareto[id]);
	else
		throw std::runtime_error("Sous graphe inexistant");
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


Graphe::~Graphe()
{
}
/*
00000000110111011010001011101101
00000000110111011010101011001101
00000000010111011010101011101101
*/