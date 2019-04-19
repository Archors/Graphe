#include "libraries.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#define KEY_SEEN     1
#define KEY_RELEASED 2
//Structure de toutes les varaibles utilisés dans le menu

const int width = 1800;
const int height = 1000;

struct MenuDonnees
{
	std::string graphe;
	std::string poid;
	bool oriente;
	int ordreTriPoid; // 1=choix individuel 2=croissant 3=decroissant
	int algoChoix; //1=dijkstra 2=Prim 3=Pareto
	int depart;
	int arrivee;
	bool cycle;
};

void leMenu(MenuDonnees menudonnees, ALLEGRO_DISPLAY * display);
void vline(int x1, int y1, ALLEGRO_COLOR couleur);