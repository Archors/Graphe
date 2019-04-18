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
	int ordreTriPoid;
	int algoChoix;
	int depart;
	int arrivee;
	bool cycle;
};

void leMenu(MenuDonnees menudonnees, ALLEGRO_DISPLAY * display);