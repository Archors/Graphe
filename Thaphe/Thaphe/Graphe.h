
///
///\file Graphe.h
///
///\brief Déclaration de la classe graphe
///\date 21 avril 2019
///
///Contient aussi les structures graphePareto et somOrdre

#ifndef GRAPHE_H_INCLUDED	
#define GRAPHE_H_INCLUDED

#include "libraries.h"
#include "Sommet.h"

struct MenuDonnees;

/**
 * \struct graphePareto
 * \brief Fait correspondre un optimum de pareto et la somme inidividuel de ses poids
 *
 */
struct graphePareto
{
	std::vector<float> sommePoids;
	std::bitset<nombreMaxAretes> aretes;
};

/**
 * \class Graphe
 * \brief Contient tous les sommets et aretes charges depuis un fichier
 *
 *Toutes les operations effectues sur des graphes et sous graphe se lancent depuis cette classe pour avoir acces aux sommets et aretes
 */
class Graphe
{
	private:
		std::vector<Sommet*> m_sommets;
		std::vector<Arete*> m_aretes;
		std::list<graphePareto> m_souGraphePareto;
		bool m_avecCycles;
		bool m_oriented;
		bool m_diametre;
		std::vector<ALLEGRO_COLOR> m_colors;
		
	public:
		std::bitset<nombreMaxPoids> m_typeTriPareto;
		
	public:
		Graphe(MenuDonnees); //Nom du fichier sans le .txt

		std::bitset<nombreMaxAretes> Prim(int poids, int sommetDepart);
		std::bitset<nombreMaxAretes> Dijkstra(int poids, int sommetDepart, int sommetArrivée = -1, std::bitset<nombreMaxAretes> ssg = std::bitset<nombreMaxAretes>(pow(2,nombreMaxAretes)-1), bool trajetMax=false);
		std::list<graphePareto> TriPareto();
		void Colorer(std::bitset<nombreMaxAretes> ssg);

		std::vector<std::bitset<nombreMaxAretes>> DeterminerSousGraphe();
		bool isConnexe(std::bitset<nombreMaxAretes>, Sommet*);
		std::vector<float> sommePoidsCoutMin(std::bitset<nombreMaxAretes>);
		std::vector<float> sommePoidsCoutDist(std::bitset<nombreMaxAretes>);
		std::vector<float> sommePoidsDiametre(std::bitset<nombreMaxAretes>);
		void createColors();

		ALLEGRO_BITMAP* DessinerGraphe();
		ALLEGRO_BITMAP* DessinerSousGraphe(std::bitset<nombreMaxAretes> aretes);
		ALLEGRO_BITMAP* DessinerSousGraphePar(graphePareto);
		ALLEGRO_BITMAP* DessinerPlusLongDiametre(std::bitset<nombreMaxAretes> ssg);
	
		const int getNombreSommets();
		const int getNombreAretes();
		const int getNombreSousGraphe();

		void free();
		~Graphe();
};

/**
 * \struct somOrdre
 * \brief Fait correspondre un sommet et son ordre (son degré)
 *
 */
struct somOrdre
{
	int ordre;
	Sommet* sommet;
};

bool compGraphesPareto(graphePareto, graphePareto);
bool compSomOrdre(somOrdre, somOrdre);


#endif // GRAPHE_H_INCLUDED
