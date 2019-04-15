#include <vector>
#include <string>
#include <unordered_map>
#include <allegro5/allegro.h>
#include "Sommet.h"
#include "Arrete.h"

class Graphe
{
private:
	std::unordered_map<const std::string,const Sommet*> m_sommets;
	std::unordered_map<const std::string, const Arrete> m_arretes;
	std::vector<std::string> m_souGraphePareto;
public:
	Graphe(std::string nomFichier);
	std::vector<std::string> DeterminerSousGraphe();
	std::vector<std::string> TriPareto();
	ALLEGRO_BITMAP DessinerGraphe();
	ALLEGRO_BITMAP DessinerSousGraphe(std::string id);
	ALLEGRO_BITMAP DessinerSousGraphePar(std::string id);
	const int getNombreSommets();
	const int getNombreArretes();
	const int getNombreSousGraphe();
	~Graphe();
};

