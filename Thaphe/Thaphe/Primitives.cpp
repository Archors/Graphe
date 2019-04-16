#include "Primitives.h"

//Methodes de Sommet

Sommet::Sommet(std::string id, double x, double y)
	:m_id{ id }, m_coords{ x, y }
{
}

void Sommet::AjouterVoisin(const Sommet* som, const Arete* ar)
{
	std::cout << "nouveu voisin\n";
}

void Sommet::Dessiner(ALLEGRO_BITMAP*)
{
}

std::vector<const Arete*> Sommet::Prim(int indicePoids)
{
	return std::vector<const Arete*>();
}

std::vector<const Arete*> Sommet::Dijkstra(int indicePoids, Sommet* arrivee)
{
	return std::vector<const Arete*>();
}


Sommet::~Sommet()
{
}

//Methodes d'aretes

Arete::Arete()
{}

Arete::Arete(std::string id, Sommet* s1, Sommet* s2, std::vector<float> poids, bool oriente) : m_id(id), m_oriente(oriente), m_poids(poids)
{
	m_sommets = std::make_pair(s1, s2);
}

void Arete::Dessiner()
{
}

std::pair<const Sommet*, const Sommet*> Arete::getSommets()
{
	return std::pair<const Sommet*, const Sommet*>();
}


const int Arete::getNombrePoids()
{
	return 0;
}

Arete::~Arete()
{
}