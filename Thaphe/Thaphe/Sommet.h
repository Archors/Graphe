#ifndef SOMMET_H_INCLUDED	
#define SOMMET_H_INCLUDED

#pragma
#include "Coords.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <allegro5/allegro.h>


class Arete
{
private:
	const std::string m_id;/*
	std::vector<float> m_poids;
	std::pair<const Sommet*, const Sommet*> m_sommets; //Si oriente, 1er = départ, 2nd = arrivée
	bool m_oriente;*/
public:
	Arete();
	//Arete(std::string id, Sommet* s1, Sommet* s2, std::vector<float> poids, bool oriente);
	/*
		void Dessiner();
		std::pair<const Sommet*, const Sommet*> getSommets();
		const float getPoids(int indice);
		const int getNombrePoids();*/

	~Arete();
};



class Sommet 
{
	private:
		std::string m_id;
		Coords m_coords;
	public:
		Sommet(std::string id, double x, double y);
		void AjouterVoisin(const Sommet* som, const Arete* ar);
		virtual ~Sommet();
};

/*
class Arete
{
private:
	const std::string m_id;
	std::vector<float> m_poids;
	std::pair<const Sommet*, const Sommet*> m_sommets; //Si oriente, 1er = départ, 2nd = arrivée
	bool m_oriente;
public:
	Arete(std::string id, Sommet* s1, Sommet* s2, std::vector<float> poids, bool oriente);
/*
	void Dessiner();
	std::pair<const Sommet*, const Sommet*> getSommets();
	const float getPoids(int indice);
	const int getNombrePoids();

	~Arete();
};*/

#endif // SOMMET_H_INCLUDED