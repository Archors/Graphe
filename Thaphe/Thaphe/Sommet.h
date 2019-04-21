#ifndef SOMMET_H_INCLUDED	
#define SOMMET_H_INCLUDED
#include "libraries.h"
#include "Coords.h"
#include "Arete.h"


class Arete;

class Sommet
{
private:
	int m_id;
	Coords m_coords;
	std::unordered_map<const Sommet*, Arete*> m_voisins;

public:
	int m_color;

public:
	Sommet(int id, double x, double y);
	void AjouterVoisin(const Sommet* som, Arete* ar);
	
	int BFSnbAretes(int nbSommets, std::bitset<nombreMaxAretes>); //Renvoie le nombre d'arrete minimal pour que le graphe soit connexe
	int tailleComposanteConnexe(int nbSommets, std::bitset<nombreMaxAretes> ssg); //Renvoie le nombre de sommets présent dans la composante connexe
	bool avoisineCol(int color, std::bitset<nombreMaxAretes> ssg) const;

	std::vector<Arete*> Prim(int indicePoids); //Renvoie les arrêtes du graphe de poids minimal
	//Renvoie les arrêtes pour le trajet le plus court entre 2 sommets ainsi que la somme des trajets de tous les sommets rencontrés 
	std::pair<std::vector<const Arete*>, float> Dijkstra(int nombreSommets, int indicePoids, const Sommet* arrivee=nullptr, std::bitset<nombreMaxAretes> grapheDeTravail = std::bitset<nombreMaxAretes>((pow(2, nombreMaxAretes) - 1)), int choix2emeRetour = 2) const;
	float Dijtances(std::bitset<nombreMaxAretes> ssg, int indicePoidsn, int nbSommets);//Renvoie la somme des distances de tous les points au point de départ

	void Dessiner(ALLEGRO_BITMAP* bmp, std::vector<ALLEGRO_COLOR>); //Dessine le sommet sur la bitmap

	const Coords getCoords() const;
	const int getId() const;
	const int getOrdre() const; //Renvoie le nombre de voisins

	virtual ~Sommet();
};

std::string inttostring(int a);
bool compDistDij(std::pair<const Sommet*, float> s1, std::pair<const Sommet*, float> s2);

#endif // SOMMET_H_INCLUDED