#ifndef SOMMET_H_INCLUDED	
#define SOMMET_H_INCLUDED

#include <iostream>
#include <vector>
#include <unordered_map>
#include <allegro5/allegro.h>

#include "Sommet.h"

//class Sommet;

class Arete
{
private:
	const std::string m_id;
	std::vector<float> m_poids;
	std::pair<const Sommet*, const Sommet*> m_sommets; //Si oriente, 1er = d�part, 2nd = arriv�e
	bool m_oriente;
public:
	Arete();
	Arete(std::string id, const Sommet* s1, const Sommet* s2, std::vector<float> poids, bool oriente);
	void Dessiner();
	std::pair<const Sommet*, const Sommet*> getSommets();
	const float getPoids(int indice);
	const int getNombrePoids();

	~Arete();
};

#endif // SOMMET_H_INCLUDED