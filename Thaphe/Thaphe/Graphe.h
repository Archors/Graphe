#ifndef GRAPHE_H_INCLUDED	
#define GRAPHE_H_INCLUDED

#include "libraries.h"
#include "Sommet.h"

class Graphe
{
private:
	std::unordered_map<std::string, Sommet*> m_sommets;
	std::unordered_map<std::string, Arete*> m_aretes;
	std::vector<std::string> m_souGraphePareto;
public:
	Graphe(std::string nomFichier, const bool oriented); //Nom du fichier sans le .txt
	ALLEGRO_BITMAP* DessinerGraphe();
	std::vector<std::string> DeterminerSousGraphe();
	ALLEGRO_BITMAP* DessinerSousGraphe(std::string aretes);
	/*std::vector<std::string> TriPareto();
	ALLEGRO_BITMAP DessinerSousGraphePar(std::string id);*/
	const int getNombreSommets();
	const int getNombreAretes();
	const int getNombreSousGraphe();
	~Graphe();
};

#endif // GRAPHE_H_INCLUDED
