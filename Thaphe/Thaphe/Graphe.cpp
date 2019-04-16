#include "Graphe.h"

//Fonction originaire du code du TP2 fourni par M. Fercoq puis modifiée
Graphe::Graphe(std::string nomFichier, const bool oriented)
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

	//lecture des aretes
	for (int i = 0; i < taille; ++i) 
	{
		//lecture des ids des deux extrémités
		ifs >> id; if (ifs.fail()) throw std::runtime_error("Probleme lecture id arete");
		ifs2 >> id_ar; if (ifs.fail()) throw std::runtime_error("Probleme lecture id arete");
		if (id != id_ar) throw std::runtime_error("Probleme aretes non correspondantes");

		ifs >> id; if (ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
		ifs >> id_voisin; if (ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");

		std::vector<float> vectPoids;

		for (int j=0; j<nbPoids; ++j)
		{
			ifs2 >> poids; if (ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
			vectPoids.push_back(poids);
		}

		m_aretes.insert({ id_ar, new Arete{ id_ar, m_sommets.find(id)->second, m_sommets.find(id_voisin)->second, vectPoids, oriented } });

		if (!oriented)
		{
			std::cout << id << " <--> " << id_voisin << std::endl;
			m_sommets.find(id)->second->AjouterVoisin( (m_sommets.find(id_voisin))->second, m_aretes.find(id_ar)->second );
			m_sommets.find(id_voisin)->second->AjouterVoisin( (m_sommets.find(id))->second, m_aretes.find(id_ar)->second );
		}
		else
			(m_sommets.find(id))->second->AjouterVoisin((m_sommets.find(id_voisin))->second, m_aretes.find(id_ar)->second);
		
	}

	ifs.close();
	ifs2.close();
}

std::vector<std::string> Graphe::DeterminerSousGraphe()
{
	std::vector<std::string> tousLesSousGraphes;
	
	for (int i = 0; i < pow(2, getNombreAretes()); i++)
	{
		tousLesSousGraphes.push_back((std::bitset<32>(i).to_string()).substr(32 - getNombreAretes(), 31));
		//std::cout << i << " : " << tousLesSousGraphes.back() << std::endl;
	}

	return tousLesSousGraphes;
}

ALLEGRO_BITMAP* Graphe::DessinerGraphe()
{
	std::string aretes = "";
	for (int i = 0; i < getNombreAretes(); i++)
		aretes += "1";
	

	return DessinerSousGraphe(aretes);
}

ALLEGRO_BITMAP* Graphe::DessinerSousGraphe(std::string aretes)
{
	int width = 0, height = 0;
	for (auto sommet : m_sommets)
	{
		if (sommet.second->getCoords().getX() > width)
			width = sommet.second->getCoords().getX();
		if (sommet.second->getCoords().getY() > height)
			height = sommet.second->getCoords().getY();
	}

	ALLEGRO_BITMAP* dessin = al_create_bitmap(width + 100, height + 100);

	al_set_target_bitmap(dessin);
	al_clear_to_color(al_map_rgb(180, 230, 150));

	int i = 0;
	for (auto arete : m_aretes)
	{
		if (aretes[i] == '1')
			arete.second->Dessiner(dessin);
		i++;
	}
		
	for (auto sommet : m_sommets)
		sommet.second->Dessiner(dessin);


	return dessin;
}

/*

std::unorderedmap<std::string> TriPareto()
{}



ALLEGRO_BITMAP DessinerSousGraphe()
{}

ALLEGRO_BITMAP DessinerSousGraphePar()
{}*/

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
