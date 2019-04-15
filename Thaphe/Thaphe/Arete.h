#ifndef ARETE_H_INCLUDED	
#define ARETE_H_INCLUDED

#include <string>
#include <vector>
#include <utility> 
#include <unordered_map>
#include <allegro5/allegro.h>
#include "Sommet.h"

class Arete
{
private:
	const std::string m_id;
	std::vector<float> m_poids;
	std::pair<const Sommet*, const Sommet*> m_sommets; //Si oriente, 1er = départ, 2nd = arrivée
	bool m_oriente;
public:
	Arete();
	Arete(std::string id, Sommet* s1, Sommet* s2,std::vector<float> poids, bool oriente);
	void Dessiner();
	std::pair<const Sommet*, const Sommet*> getSommets();
	const float getPoids(int indice);
	const int getNombrePoids();

	~Arete();
};

#endif // ARETE_H_INCLUDED