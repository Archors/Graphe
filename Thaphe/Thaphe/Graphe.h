#ifndef GRAPHE_H_INCLUDED	
#define GRAPHE_H_INCLUDED

#include "libraries.h"
#include "Sommet.h"

struct MenuDonnees;

struct graphePareto
{
	std::vector<float> sommePoids;
	std::bitset<nombreMaxAretes> aretes;
};

class Graphe
{
	private:
		std::vector<Sommet*> m_sommets;
		std::vector<Arete*> m_aretes;
		std::list<graphePareto> m_souGraphePareto;
		bool m_avecCycles;
		bool m_oriented;
public:
		std::vector<ALLEGRO_COLOR> m_colors;
		
	public:
		std::bitset<nombreMaxPoids> m_typeTriPareto;

	public:
		Graphe(MenuDonnees); //Nom du fichier sans le .txt

		std::bitset<nombreMaxAretes> Prim(int poids, int sommetDepart);
		std::bitset<nombreMaxAretes> Dijkstra(int poids, int sommetDepart, int sommetArrivée = -1);
		std::list<graphePareto> TriPareto();
		void Colorer(std::bitset<nombreMaxAretes> ssg);

		std::vector<std::bitset<nombreMaxAretes>> DeterminerSousGraphe();
		bool isConnexe(std::bitset<nombreMaxAretes>, Sommet*);
		std::vector<float> sommePoidsCoutMin(std::bitset<nombreMaxAretes>);
		std::vector<float> sommePoidsCoutDist(std::bitset<nombreMaxAretes>);
		void createColors();

		ALLEGRO_BITMAP* DessinerGraphe();
		ALLEGRO_BITMAP* DessinerSousGraphe(std::bitset<nombreMaxAretes> aretes);
		ALLEGRO_BITMAP* DessinerSousGraphePar(graphePareto);
	
		const int getNombreSommets();
		const int getNombreAretes();
		const int getNombreSousGraphe();

		void free();
		~Graphe();
};

struct somOrdre
{
	int ordre;
	Sommet* sommet;
};

bool compGraphesPareto(graphePareto, graphePareto);
bool compSomOrdre(somOrdre, somOrdre);


#endif // GRAPHE_H_INCLUDED
