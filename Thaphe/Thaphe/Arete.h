/**
 * \file Arete.h
 * \brief Declaration de la classe Arete
 * \date 21 avril 2019
 */
#ifndef ARETE_H_INCLUDED	
#define ARETE_H_INCLUDED

#include "libraries.h"
#include "Sommet.h"

class Sommet;
/**
 * \class Arete
 * \brief Classe d'une ar�te contenu dans un graphe
 *Permet avec la classe Sommet de cr�er un graphe
 */
class Arete
{
private:
	const int m_id;
	std::vector<float> m_poids;
	std::pair<Sommet*, Sommet*> m_sommets; //Si oriente, 1er = d�part, 2nd = arriv�e
	bool m_oriente;

public:
	Arete(int id, Sommet* s1, Sommet* s2, std::vector<float> poids, bool oriente);

	void Dessiner(ALLEGRO_BITMAP*);

	std::pair <Sommet*, Sommet*> getSommets();
	const float getPoids(int indice) const;
	const int getNombrePoids();
	const int getId() const;
	
	~Arete();
};

#endif // ARETE_H_INCLUDED