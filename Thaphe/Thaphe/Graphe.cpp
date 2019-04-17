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

std::vector<std::string> Graphe::DeterminerSousGraphe()
{
	std::vector<std::string> tousLesSousGraphes;

	std::cout << "Looking for every graph possible...\n";


	long int minAretes = m_sommets[0]->BFS(getNombreSommets(), (std::bitset<32>(pow(2, getNombreAretes()) - 1).to_string().substr((char)32 - (char)getNombreAretes(), 31))).size();
	minAretes = minAretes * 49 + (getNombreAretes() - minAretes) * 48;
	std::cout << "Min ar : " << minAretes << std::endl;

	int pr = -1;
	for (int i = 0; i < pow(2, getNombreAretes()); i++)
	{
		std::string ssg = (std::bitset<32>(i).to_string()).substr((char)32 - (char)getNombreAretes(), 31);
		if (std::accumulate(ssg.begin(), ssg.end(), 0) >= minAretes)
		{
			if (isConnexe(ssg))
			{
				//std::cout << "Found one !\n";
				tousLesSousGraphes.push_back(ssg);
			}
		}
		

		if ( (int)((100 * i) / (pow(2, getNombreAretes()) - 1)) > pr)
		{
			pr = (100 * i) / (pow(2, getNombreAretes()) - 1);
			std::cout << pr << "%\n";
		}
			
		//std::cout << i << " : " << tousLesSousGraphes.back() << std::endl;
	}

	std::cout << "Done !\n";

	return tousLesSousGraphes;
}


bool Graphe::isConnexe(std::string ssg)
{
	if (m_sommets[0]->tailleComposanteConnexe(getNombreSommets(), ssg) < getNombreSommets())
		return false;
	return true;
}


std::string Graphe::Prim()
{
	std::cout << "Lancement prim depuis le sommet 0...\n";

	std::vector<Arete*> aretePrim = m_sommets[0]->Prim(0);

	std::string ssg = "";
	for (int i = 0; i < getNombreAretes(); i++)
		ssg += "0";
	std::cout << "Nombre d'arretes minimal : " << aretePrim.size() << std::endl;

	for (auto a : aretePrim)
		ssg[a->getId()] = '1';

	std::cout << "Graphe de poids minimal trouve\n";

	return ssg;
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
		if (sommet->getCoords().getX() > width)
			width = sommet->getCoords().getX();
		if (sommet->getCoords().getY() > height)
			height = sommet->getCoords().getY();
	}

	ALLEGRO_BITMAP* dessin = al_create_bitmap(width + 100, height + 100);

	al_set_target_bitmap(dessin);
	al_clear_to_color(al_map_rgb(180, 230, 150));

	int i = 0;
	for (auto arete : m_aretes)
	{
		if (aretes[i] == '1')
			arete->Dessiner(dessin);
		i++;
	}
		
	for (auto sommet : m_sommets)
		sommet->Dessiner(dessin);


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
