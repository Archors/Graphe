#ifndef GRAPHE_H_INCLUDED	
#define GRAPHE_H_INCLUDED

#include "libraries.h"
#include "Sommet.h"

class Graphe
{
private:
	std::vector<Sommet*> m_sommets;
	std::vector<Arete*> m_aretes;
	std::vector<std::string> m_souGraphePareto;
public:
	Graphe(std::string nomFichier, const bool oriented); //Nom du fichier sans le .txt

	std::vector<std::string> DeterminerSousGraphe();
	bool isConnexe(std::string);
	std::string Prim();
	std::string Dijkstra();

	std::vector<std::string> TriPareto();

	ALLEGRO_BITMAP* DessinerGraphe();
	ALLEGRO_BITMAP* DessinerSousGraphe(std::string aretes);
	ALLEGRO_BITMAP* DessinerSousGraphePar(int id);
	
	const int getNombreSommets();
	const int getNombreAretes();
	const int getNombreSousGraphe();
	~Graphe();
};


struct graphePareto
{
	std::string aretes;
	std::vector<float> sommePoids;
};

bool compGraphesPareto(graphePareto, graphePareto);

#endif // GRAPHE_H_INCLUDED
