#ifndef SOMMET_H_INCLUDED	
#define SOMMET_H_INCLUDED
#include "libraries.h"
#include "Coords.h"
#include "Arete.h"


class Arete;

class Sommet
{
private:
	std::string m_id;
	Coords m_coords;
	std::unordered_map<const Sommet*, Arete*> m_voisins;
public:
	Sommet(std::string id, double x, double y);
	void AjouterVoisin(const Sommet* som, const Arete* ar);
	void Dessiner(ALLEGRO_BITMAP* bmp);
	std::vector<const Arete*> Prim(int indicePoids);
	std::vector<const Arete*> Dijkstra(int indicePoids, const Sommet* arrivee);
	const Coords getCoords() const;
	virtual ~Sommet();
};

#endif // SOMMET_H_INCLUDED