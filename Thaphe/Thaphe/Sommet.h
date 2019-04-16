#include <iostream>
#include <vector>
#include <unordered_map>
#include <allegro5/allegro.h>

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
	void Dessiner(ALLEGRO_BITMAP*);
	std::vector<Arete*> Prim(int indicePoids);
	std::vector<Arete*> Dijkstra(int indicePoids, const Sommet* arrivee);
	virtual ~Sommet();
};