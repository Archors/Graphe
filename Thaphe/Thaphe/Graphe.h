#ifndef GRAPHE_H_INCLUDED	
#define GRAPHE_H_INCLUDED

#include <vector>
#include <string>
#include <unordered_map>
#include <allegro5/allegro.h>
#include "Sommet.h"
#include "Arete.h"

class Graphe
{
private:
	std::unordered_map<const std::string,const Sommet*> m_sommets;
	std::unordered_map<const std::string, const Arete> m_Aretes;
	std::vector<std::string> m_souGraphePareto;
public:
	Graphe(std::string nomFichier);
	std::vector<std::string> DeterminerSousGraphe();
	std::vector<std::string> TriPareto();
	ALLEGRO_BITMAP DessinerGraphe();
	ALLEGRO_BITMAP DessinerSousGraphe(std::string id);
	ALLEGRO_BITMAP DessinerSousGraphePar(std::string id);
	const int getNombreSommets();
	const int getNombreAretes();
	const int getNombreSousGraphe();
	~Graphe();
};

#endif // GRAPHE_H_INCLUDED
