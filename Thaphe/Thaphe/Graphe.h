#ifndef GRAPHE_H_INCLUDED	
#define GRAPHE_H_INCLUDED

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <allegro5/allegro.h>
#include "Primitives.h"

class Graphe
{
private:
	std::unordered_map<std::string,const Sommet*> m_sommets;
	std::unordered_map<std::string, const Arete*> m_aretes;
	std::vector<std::string> m_souGraphePareto;
public:
	Graphe(std::string nomFichier, const bool oriented); //Nom du fichier sans le .txt
	/*
	std::vector<std::string> DeterminerSousGraphe();
	//std::vector<std::string> TriPareto();
	ALLEGRO_BITMAP DessinerGraphe();
	ALLEGRO_BITMAP DessinerSousGraphe(std::string id);
	ALLEGRO_BITMAP DessinerSousGraphePar(std::string id);
	const int getNombreSommets();
	const int getNombreAretes();
	const int getNombreSousGraphe();*/
	~Graphe();
};

#endif // GRAPHE_H_INCLUDED
