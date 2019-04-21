#include "libraries.h"

#define KEY_SEEN     1
#define KEY_RELEASED 2
//Structure de toutes les variables utilis�s dans le menu

//int nombreMaxPoids = 3;

struct MenuDonnees
{
	std::string graphe;
	std::string poid;
	int quelPoid; 
	bool oriente; //Graphe orient� ou non
	int algoChoix; //1=dijkstra 2=Prim 3=Pareto 4=
	int depart; //Sommet de depart
	int arrivee; //Sommet d'arriv�
	bool cycle; //Pareto
	std::bitset<nombreMaxPoids> poids;
	bool colorG; //Graphe color�
	bool diametre; //Pareto en fonction du diametre
	bool parcourirTout;
};

void leMenu(MenuDonnees &menudonnees, ALLEGRO_DISPLAY * display);
void vline(int x1, int y1, ALLEGRO_COLOR couleur);

void chargerChoixMenu(MenuDonnees& choix);
