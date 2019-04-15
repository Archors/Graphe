#pragma
#include <string>
#include <vector>
#include <unordered_map>
#include <allegro5/allegro.h>
#include "Sommet.h"

class Arrete
{
private:
	const std::string m_id;
	std::vector<float> m_poids;
	std::pair<const Sommet*, const Sommet*> m_sommets; //Si oriente, 1er = départ, 2nd = arrivée
	bool oriente;
public:
	Arrete(std::string id, Sommet* s1, Sommet* s2, std::vector<const float>, bool);
	Arrete();
	void Dessiner();
	std::pair<const Sommet*, const Sommet*> getSommets();
	const float getPoids(int indice);
	const int getNombrePoids();

	~Arrete();
};

