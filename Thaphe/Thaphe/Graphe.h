#ifndef GRAPHE_H_INCLUDED	
#define GRAPHE_H_INCLUDED

#include "libraries.h"
#include "Sommet.h"

class Graphe
{
private:
	std::vector<Sommet*> m_sommets;
	std::vector<Arete*> m_aretes;
	std::vector<std::bitset<nombreMaxAretes>> m_souGraphePareto;
public:
	Graphe(std::string nomFichier, const bool oriented); //Nom du fichier sans le .txt

	std::vector<std::bitset<nombreMaxAretes>> DeterminerSousGraphe();
	bool isConnexe(std::bitset<nombreMaxAretes>);
	std::bitset<nombreMaxAretes> Prim();
	std::bitset<nombreMaxAretes> Dijkstra();


	std::vector<std::bitset<nombreMaxAretes>> TriPareto();

	ALLEGRO_BITMAP* DessinerGraphe();
	ALLEGRO_BITMAP* DessinerSousGraphe(std::bitset<nombreMaxAretes> aretes);
	ALLEGRO_BITMAP* DessinerSousGraphePar(int id);
	
	const int getNombreSommets();
	const int getNombreAretes();
	const int getNombreSousGraphe();
	~Graphe();
};


struct graphePareto
{
	std::bitset<nombreMaxAretes> aretes;
	std::vector<float> sommePoids;
};

bool compGraphesPareto(graphePareto, graphePareto);

#endif // GRAPHE_H_INCLUDED
