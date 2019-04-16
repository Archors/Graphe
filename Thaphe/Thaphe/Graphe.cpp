#include "Graphe.h"

//Fonction originaire du code du TP2 fourni par M. Fercoq puis modifiée
Graphe::Graphe(std::string nomFichier, const bool oriented)
{
	std::ifstream ifs{ nomFichier+".txt" };


	if (!ifs)
		throw std::runtime_error("Impossible d'ouvrir en lecture " + nomFichier);

	std::ifstream ifs2{ nomFichier + "weights_0.txt" };
	if (ifs2.fail())
		throw std::runtime_error("Probleme lecture taille du graphe");


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
		m_sommets.insert({ id, new Sommet{id,x,y} });
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

	std::string id_voisin;
	std::string id_ar;
	double poids;
	std::vector<float> vectPoids;

	//lecture des aretes
	for (int i = 0; i < taille; ++i) 
	{
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

		m_aretes.insert({ id_ar, new Arete{ id_ar, m_sommets.find(id)->second, m_sommets.find(id)->second, vectPoids, oriented } });

		//ajouter chaque extrémité à la liste des voisins de l'autre (graphe non orienté)
		if (!oriented)
		{
			m_sommets.find(id)->second->AjouterVoisin( (m_sommets.find(id_voisin))->second, m_aretes.find(id_ar)->second );
			m_sommets.find(id_voisin)->second->AjouterVoisin( (m_sommets.find(id))->second, m_aretes.find(id_ar)->second );
		}
		else
			(m_sommets.find(id))->second->AjouterVoisin((m_sommets.find(id_voisin))->second, m_aretes.find(id_ar)->second);
		
	}

	ifs.close();
	ifs2.close();
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
