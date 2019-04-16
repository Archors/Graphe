#include "Arete.h"

Arete::Arete()
{}

Arete::Arete(std::string id, const Sommet* s1, Sommet* s2, std::vector<float> poids, bool oriente) : m_id(id), m_oriente(oriente), m_poids(poids)
{
	m_sommets = std::make_pair(s1, s2);
}

void Arete::Dessiner()
{
}

std::pair<const Sommet*, Sommet*> Arete::getSommets()
{
	return std::pair<const Sommet*, Sommet*>();
}


const int Arete::getNombrePoids()
{
	return 0;
}

Arete::~Arete()
{
}