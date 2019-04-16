#include "Graphe.h"

//Fonction originaire du code du TP2 fourni par M. Fercoq puis modifiée
Graphe::Graphe(std::string nomFichier, const bool oriented)
{
	std::ifstream ifs{ nomFichier };

	if (!ifs)
		throw std::runtime_error("Impossible d'ouvrir en lecture " + nomFichier);

	int ordre;
	ifs >> ordre;

	if (ifs.fail())
		throw std::runtime_error("Probleme lecture ordre du graphe");


	std::string id;
	double x, y;

	//lecture des sommets
	for (int i = 0; i < ordre; ++i)
	{
		ifs >> id; if (ifs.fail()) throw std::runtime_error("Probleme lecture id");
		ifs >> x; if (ifs.fail()) throw std::runtime_error("Probleme lecture x");
		ifs >> y; if (ifs.fail()) throw std::runtime_error("Probleme lecture y");
		m_sommets.insert( { id, new Sommet{id,x,y} } );
	}

	int taille;
	ifs >> taille;
	if (ifs.fail())
		throw std::runtime_error("Probleme lecture taille du graphe");

	std::string id_voisin;

	//lecture des aretes
	for (int i = 0; i < taille; ++i) 
	{
		//lecture des ids des deux extrémités
		ifs >> id; if (ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
		ifs >> id_voisin; if (ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
		//ajouter chaque extrémité à la liste des voisins de l'autre (graphe non orienté)
		//(m_sommets.find(id))->second->AjouterVoisin((m_sommets.find(id_voisin))->second);
		(m_sommets.find(id_voisin))->second->AjouterVoisin((m_sommets.find(id))->second);//remove si graphe orienté
	}
}


/*
std::unordered_map<const std::string,const Sommet*> m_sommets()
{}

std::unordered_map<const std::string, const Arete> m_Aretes()
{}

std::unorderedmap<std::string> TriPareto()
{}

ALLEGRO_BITMAP DessinerGraphe()
{}

ALLEGRO_BITMAP DessinerSousGraphe()
{}

ALLEGRO_BITMAP DessinerSousGraphePar()
{}

const int getNombreSommets()
{}

const int getNombreAretes()
{}

const int getNombreSousGraphe()
{}*/


Graphe::~Graphe()
{
}
