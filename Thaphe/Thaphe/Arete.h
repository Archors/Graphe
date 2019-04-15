#ifndef ARETE_H_INCLUDED	
#define ARETE_H_INCLUDED

#include <string>
#include <vector>
#include <unordered_map>
#include <allegro5/allegro.h>
#include "Sommet.h"

class Sommet;

class Arete
{
private:
	const std::string m_id;
	std::vector<float> m_poids;
	std::pair<const Sommet*, const Sommet*> m_sommets; //Si oriente, 1er = d�part, 2nd = arriv�e
	bool oriente;
public:
	Arete(std::string id, Sommet* s1, Sommet* s2, std::vector<const float>, bool);
	Arete();
	void Dessiner();
	std::pair<const Sommet*, const Sommet*> getSommets();
	const float getPoids(int indice);
	const int getNombrePoids();

	~Arete();
};

#endif // ARETE_H_INCLUDED