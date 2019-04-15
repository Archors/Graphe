#ifndef SOMMET_H_INCLUDED	
#define SOMMET_H_INCLUDED

#pragma
#include "Coords.h"
#include "Arete.h"
#include <string>
#include <unordered_map>
#include <allegro5/allegro.h>

class Arete;

class Sommet 
{
	private:
		std::string m_id;
		Coords m_coords;
		std::unordered_map<const Sommet*, const Arete*> m_voisins();
	public:
		Sommet(std::string id, Coords coords);
		virtual ~Sommet();
		void Dessiner(ALLEGRO_BITMAP*);
		std::vector<const Arete*> Prim(int indicePoids);
		std::vector<const Arete*> Dijkstra(int indicePoids, const Sommet* arrivee);
};

#endif // SOMMET_H_INCLUDED