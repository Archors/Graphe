#ifndef GRAPHE_H_INCLUDED	
#define GRAPHE_H_INCLUDED

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <allegro5/allegro.h>
//#include "Sommet.h"
#include "Coords.h"

class Arete;

class Sommet
{
private:
	std::string m_id;
	Coords m_coords;
	std::unordered_map<const Sommet*, Arete*> m_voisins;
public:
	Sommet(std::string id, double x, double y);
	void AjouterVoisin(const Sommet*, const Arete*);
	void Dessiner(ALLEGRO_BITMAP*);
	std::vector<Arete*> Prim(int indicePoids);
	std::vector<Arete*> Dijkstra(int indicePoids, const Sommet* arrivee);
	virtual ~Sommet();
};

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
	void Dessiner();
	std::pair<const Sommet*, Sommet*> getSommets();
	const float getPoids(int indice);
	const int getNombrePoids();

	~Arete();
};

class Graphe
{
private:
	std::unordered_map<std::string, Sommet*> m_sommets;
	std::unordered_map<std::string, Arete*> m_aretes;
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
