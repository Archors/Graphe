#ifndef ARETE_H_INCLUDED	
#define ARETE_H_INCLUDED

#include "libraries.h"
#include "Sommet.h"

class Sommet;

class Arete
{
private:
	const std::string m_id;
	std::vector<float> m_poids;
	std::pair<const Sommet*, Sommet*> m_sommets; //Si oriente, 1er = départ, 2nd = arrivée
	bool m_oriente;

public:
	Arete();
	Arete(std::string id, const Sommet* s1, Sommet* s2, std::vector<float> poids, bool oriente);
	void Dessiner(ALLEGRO_BITMAP*);
	std::pair<const Sommet*, Sommet*> getSommets();
	const float getPoids(int indice);
	const int getNombrePoids();
	
	~Arete();
};

#endif // ARETE_H_INCLUDED