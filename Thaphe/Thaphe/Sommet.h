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
	Sommet(int id, double x, double y);
	void AjouterVoisin(const Sommet* som, Arete* ar);
	void Dessiner(ALLEGRO_BITMAP* bmp);
	std::vector<Arete*> Prim(int indicePoids);
	int BFSnbAretes(int nbSommets, std::bitset<nombreMaxAretes>);
	int tailleComposanteConnexe(int nbSommets, std::bitset<nombreMaxAretes> ssg);
	const Coords getCoords() const;
	const int getId() const;
	std::pair<std::vector<const Arete*>, float> Dijkstra(int nombreSommets, int indicePoids, const Sommet* arrivee=nullptr, std::bitset<nombreMaxAretes> grapheDeTravail = std::bitset<nombreMaxAretes>((pow(2, nombreMaxAretes) - 1))) const;
	float Dijtances(std::bitset<nombreMaxAretes> ssg, int indicePoidsn, int nbSommets);

	virtual ~Sommet();
};

std::string inttostring(int a);
bool compDistDij(std::pair<const Sommet*, float> s1, std::pair<const Sommet*, float> s2);

#endif // SOMMET_H_INCLUDED