#include <vector>
#include <string>
#include <allegro5/allegro.h>

class Graphe
{
private:
	std::vector<int> m_sommets;
	std::vector<int> m_arretes;
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

