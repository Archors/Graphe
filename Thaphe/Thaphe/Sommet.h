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
	std::vector<const Arete*> BFS(int nbSommets, std::string ssg);
	int tailleComposanteConnexe(int nbSommets, std::bitset<32> ssg);
	const Coords getCoords() const;
	const int getId() const;
	std::vector<const Arete*> Dijkstra(int nombreSommets, int indicePoids, const Sommet* arrivee=nullptr ) const;

	virtual ~Sommet();
};

std::string inttostring(int a);

#endif // SOMMET_H_INCLUDED