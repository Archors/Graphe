#include "libraries.h"

#define KEY_SEEN     1
#define KEY_RELEASED 2
//Structure de toutes les varaibles utilisés dans le menu

//int nombreMaxPoids = 3;

struct MenuDonnees
{
	std::string graphe;
	std::string poid;
	int quelPoid;
	bool oriente;
	int algoChoix; //1=dijkstra 2=Prim 3=Pareto
	int depart;
	int arrivee;
	bool cycle; //Pareto
	std::bitset<nombreMaxPoids> poids;
};

void leMenu(MenuDonnees &menudonnees, ALLEGRO_DISPLAY * display);
void vline(int x1, int y1, ALLEGRO_COLOR couleur);

void chargerChoixMenu(MenuDonnees& choix);
