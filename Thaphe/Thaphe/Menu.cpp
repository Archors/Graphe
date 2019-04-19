#include "Menu.h"

using namespace std;

float FPS = 10;

int number_text_boxes = 5;	// the number of textboxes 

int* switch_text_boxes;
string* text_boxes;
int* command_prompt;

ALLEGRO_KEYBOARD_STATE keyboard;
ALLEGRO_FONT* font8;
ALLEGRO_MOUSE_STATE mouse;

int NombreMaxPoids = 3;

void textbox(int coordinate_x, int coordinate_y, int number_signs, int coordinate_command_prompt, int number_text_box);

void leMenu(MenuDonnees menudonnees,ALLEGRO_DISPLAY* display)
{
	ALLEGRO_BITMAP* imagepresentation;
	ALLEGRO_BITMAP* imagechoix;
	ALLEGRO_BITMAP* choix1;
	ALLEGRO_DISPLAY_MODE   disp_data;
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	bool boucle = true;
	bool pres = true;
	bool choix = false;
	bool choixcase = false;
	bool primDijkstra=false;
	bool pareto = false;
	menudonnees.oriente = false;
	menudonnees.cycle = false;
	menudonnees.algoChoix = 0;
	for (int i = 0; i < NombreMaxPoids ; i++)
	{
		menudonnees.poids.push_back(false);
	}
	if (!al_init_image_addon())
	{
		cout<<"couldn't initialize image addon\n";
	}

	//Chargement de l'image de garde
	imagepresentation = al_load_bitmap("presentation.png");
	if (!imagepresentation)
	{
		cout << "L'image de presentation ne peut pas etre charge" << endl;
		al_destroy_bitmap(imagepresentation);
		exit;
	}

	//Chargement de l'image sous les choix
	imagechoix = al_load_bitmap("choix.png");
	if (!imagechoix)
	{
		cout << "L'image du choix ne peut pas etre charge" << endl;
		al_destroy_bitmap(imagechoix);
		exit;
	}

	//Initialisation de la gestion d'evenements
	ALLEGRO_EVENT_QUEUE* queue;
	queue = al_create_event_queue();
	al_install_keyboard();
	al_install_mouse();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());

	//Chargement de la police d'ecriture
	ALLEGRO_FONT* fontMatrix;
	fontMatrix = al_load_font("Matrix.ttf", 100, 0);
	ALLEGRO_FONT* fontMatrixPetit;
	fontMatrixPetit = al_load_font("simple_font.ttf", 40, 0);

	//Initialisation des TextBox
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	ALLEGRO_EVENT event;
	ALLEGRO_TIMER* timer = NULL;
	timer = al_create_timer(1.0 / FPS);
	al_start_timer(timer);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	switch_text_boxes = new int[number_text_boxes];
	for (int i = 0; i < number_text_boxes; i++)
	{
		switch_text_boxes[i] = 0; // the textboxes are inactive 
	}
	font8 = al_load_font("simple_font.ttf", 25, 0);
	bool redraw = true;

	text_boxes = new string[number_text_boxes];

	command_prompt = new int[number_text_boxes];
	for (int i = 0; i < number_text_boxes; i++)
	{
		command_prompt[i] = 25;	// the initial coordinates command prompts are the same as the coordinates x
	}

	//Options
	ALLEGRO_COLOR colorcase = al_map_rgb(150, 0, 0); //Choisir la couleur des cases à cocher


	while (boucle)
	{
		al_flip_display();
		
		//Page de presentation/de garde
		if (pres)
		{
			ALLEGRO_EVENT event;
			al_wait_for_event(queue, &event);
			al_draw_scaled_bitmap(imagepresentation, 0, 0, al_get_bitmap_width(imagepresentation), al_get_bitmap_height(imagepresentation), 0, 0, disp_data.width, disp_data.height, 0);
			al_draw_text(fontMatrix, al_map_rgb(0, 255, 0), disp_data.width / 2, disp_data.height / 6, ALLEGRO_ALIGN_CENTRE, "Theorie des graphes");
			al_draw_rounded_rectangle(disp_data.width / 4 + 20, disp_data.height / 2 + 50, 3 * disp_data.width / 4 - 20, disp_data.height / 2 + 200, 50, 50, al_map_rgb(255, 0, 0), 10);
			//Ecriture de nos nom en bas de la page de garde
			al_draw_text(fontMatrixPetit, al_map_rgb(150, 0, 0), 20, disp_data.height - 130, ALLEGRO_ALIGN_LEFT, "Combe Antoine");
			al_draw_text(fontMatrixPetit, al_map_rgb(150, 0, 0), 20, disp_data.height - 90, ALLEGRO_ALIGN_LEFT, "De Malliard Jean");
			al_draw_text(fontMatrixPetit, al_map_rgb(150, 0, 0), 20, disp_data.height - 50, ALLEGRO_ALIGN_LEFT, "Gaucher Matthieu");

			if (event.mouse.x >= disp_data.width / 4 + 20 && event.mouse.x < 3 * disp_data.width / 4 - 20 && event.mouse.y >= disp_data.height / 2 + 50 && event.mouse.y < disp_data.height / 2 + 200)
			{
				al_draw_rounded_rectangle(disp_data.width / 4 + 20, disp_data.height / 2 + 50, 3 * disp_data.width / 4 - 20, disp_data.height / 2 + 200, 50, 50, al_map_rgb(255, 0, 0), 10);
				al_draw_text(fontMatrix, al_map_rgb(255, 0, 0), disp_data.width / 2, ((disp_data.height / 2 + 50) + (disp_data.height / 2 + 200)) / 2 - 32, ALLEGRO_ALIGN_CENTRE, "Start");
			}
			else 
			{
				al_draw_rounded_rectangle(disp_data.width / 4 + 20, disp_data.height / 2 + 50, 3 * disp_data.width / 4 - 20, disp_data.height / 2 + 200, 50, 50, al_map_rgb(0, 255, 0), 10);
				al_draw_text(fontMatrix, al_map_rgb(0, 255, 0), disp_data.width / 2, ((disp_data.height / 2 + 50) + (disp_data.height / 2 + 200)) / 2 - 32, ALLEGRO_ALIGN_CENTRE, "Start");
			}
			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				if (event.mouse.x >= disp_data.width / 4 + 20 && event.mouse.x < 3 * disp_data.width / 4 - 20 && event.mouse.y >= disp_data.height / 2 + 50 && event.mouse.y < disp_data.height / 2 + 200)
				{
					pres = false;
					choix = true;
				}
			}

		}

		//1ere page des options
		if (choix)
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(queue, &event);
			al_draw_scaled_bitmap(imagechoix, 0, 0, al_get_bitmap_width(imagechoix), al_get_bitmap_height(imagechoix), 0, 0, disp_data.width, disp_data.height, 0);
			al_get_next_event(event_queue, &ev);

			al_get_mouse_state(&mouse);
			al_get_keyboard_state(&keyboard);

			al_draw_text(fontMatrix, al_map_rgb(100, 0, 0), disp_data.width / 2, disp_data.height / 8, ALLEGRO_ALIGN_CENTRE, "OPTIONS");
			al_draw_text(font8, al_map_rgb(100, 0, 0), disp_data.width/6, disp_data.height / 3, ALLEGRO_ALIGN_CENTRE, "GRAPHE :");
			al_draw_text(font8, al_map_rgb(100, 0, 0), disp_data.width/6, disp_data.height / 2, ALLEGRO_ALIGN_CENTRE, "POIDS :");
			//Creation des endroits pour écrire
			textbox(disp_data.width/4, disp_data.height/3, 15, 25, 0);
			textbox(disp_data.width/4, disp_data.height/2, 15, 25, 1);
			//On recupere ce qui est écrit
			menudonnees.graphe = text_boxes[0].c_str();
			menudonnees.poid = text_boxes[1].c_str();
			ALLEGRO_EVENT event;
			al_wait_for_event(queue, &event);
			
			if (event.mouse.x >= 5 * disp_data.width / 8 && event.mouse.x < 7 * disp_data.width / 8 + 20 && event.mouse.y >= 7 * disp_data.height / 8 - 50 && event.mouse.y < 7 * disp_data.height / 8 + 50)
			{
				al_draw_rounded_rectangle(5 * disp_data.width / 8, 7 * disp_data.height / 8 - 50, 7 * disp_data.width / 8 + 20, 7 * disp_data.height / 8 + 50, 50, 50, al_map_rgb(255, 0, 0), 10);
				al_draw_text(font8, al_map_rgb(255, 0, 0), ((5 * disp_data.width / 8)+ (7 * disp_data.width / 8 + 20))/2,((7 * disp_data.height / 8 - 50)+(7 * disp_data.height / 8 + 50))/2-10, ALLEGRO_ALIGN_CENTRE, "SUITE ->");
				if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && menudonnees.graphe.empty() != true && menudonnees.poid.empty()!= true)
				{
					choix = false;
					choixcase = true;
				}
			}
			else
			{
				al_draw_rounded_rectangle(5 * disp_data.width / 8, 7 * disp_data.height / 8 - 50, 7 * disp_data.width / 8 + 20, 7 * disp_data.height / 8 + 50, 50, 50, al_map_rgb(0, 255, 0), 10);
				al_draw_text(font8, al_map_rgb(0, 255, 0), ((5 * disp_data.width / 8) + (7 * disp_data.width / 8 + 20)) / 2, ((7 * disp_data.height / 8 - 50) + (7 * disp_data.height / 8 + 50)) / 2-10, ALLEGRO_ALIGN_CENTRE, "SUITE ->");
			}


		}

		//2eme page des options
		if (choixcase)
		{
			int hauteurTRI = disp_data.height / 4 + 160;
			int hauteurAlgo = hauteurTRI + 80;
			int hauteurOriente = hauteurTRI - 80;
			ALLEGRO_EVENT event;
			al_wait_for_event(queue, &event);
			al_draw_scaled_bitmap(imagechoix, 0, 0, al_get_bitmap_width(imagechoix), al_get_bitmap_height(imagechoix), 0, 0, disp_data.width, disp_data.height, 0);
			al_draw_text(fontMatrix, al_map_rgb(100, 0, 0), disp_data.width / 2, disp_data.height / 8, ALLEGRO_ALIGN_CENTRE, "OPTIONS");

			//Choix orienté ou non
			al_draw_text(font8, al_map_rgb(100, 0, 0), 1 * disp_data.width / 7, hauteurOriente, ALLEGRO_ALIGN_LEFT, "ORIENTE :");
			al_draw_rectangle(1 * disp_data.width / 5 + 100, hauteurOriente, 1 * disp_data.width / 5 + 130, hauteurOriente+30, colorcase, 2);
			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				if (event.mouse.x >= 1 * disp_data.width / 5 + 100 && event.mouse.x < 1 * disp_data.width / 5 + 130 && event.mouse.y >= hauteurOriente && event.mouse.y < hauteurOriente + 30)
				{
					if (!menudonnees.oriente)
						menudonnees.oriente = true;
					else
						menudonnees.oriente = false;
				}
			}
			if (menudonnees.oriente)
				vline(((1 * disp_data.width / 5 + 100) + (1 * disp_data.width / 5 + 130)) / 2, (hauteurOriente + hauteurOriente + 30) / 2 + 5, colorcase);

			//Choix de l'ordre de tri des poids
			al_draw_text(font8, al_map_rgb(100, 0, 0), 1 * disp_data.width / 7, hauteurTRI, ALLEGRO_ALIGN_LEFT, "ORDRE DE TRI :");

			al_draw_text(font8, al_map_rgb(100, 0, 0), 2 * disp_data.width / 7, hauteurTRI, ALLEGRO_ALIGN_LEFT, "choix individuel");
			al_draw_rectangle(2 * disp_data.width / 7 - 50, hauteurTRI, 2 * disp_data.width / 7 -20 , hauteurTRI +30, colorcase, 2);

			al_draw_text(font8, al_map_rgb(100, 0, 0), 3 * disp_data.width / 7, hauteurTRI, ALLEGRO_ALIGN_LEFT, "croissant");
			al_draw_rectangle(3 * disp_data.width / 7 -52, hauteurTRI, 3 * disp_data.width / 7 - 22, hauteurTRI+30, colorcase, 2);

			al_draw_text(font8, al_map_rgb(100, 0, 0), 4 * disp_data.width / 7-60, hauteurTRI, ALLEGRO_ALIGN_LEFT, "decroissant");
			al_draw_rectangle(4 * disp_data.width / 7 -90, hauteurTRI, 4 * disp_data.width / 7 -120, hauteurTRI+30, colorcase, 2);

			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				if (event.mouse.x >= 2 * disp_data.width / 7 - 50 && event.mouse.x < 2 * disp_data.width / 7 - 20 && event.mouse.y >= hauteurTRI && event.mouse.y < hauteurTRI + 30)
				{
					if (menudonnees.ordreTriPoid != 1)
						menudonnees.ordreTriPoid = 1;
					else
						menudonnees.ordreTriPoid = 0;
				}
				if (event.mouse.x >= 3 * disp_data.width / 7 - 52 && event.mouse.x < 3 * disp_data.width / 7 - 22 && event.mouse.y >= hauteurTRI && event.mouse.y < hauteurTRI + 30)
				{
					if (menudonnees.ordreTriPoid != 2)
						menudonnees.ordreTriPoid = 2;
					else
						menudonnees.ordreTriPoid = 0;
				}
				if (event.mouse.x >= 4 * disp_data.width / 7 - 120 && event.mouse.x < 4 * disp_data.width / 7 - 90 && event.mouse.y >= hauteurTRI && event.mouse.y < hauteurTRI + 30)
				{
					if (menudonnees.ordreTriPoid != 3)
						menudonnees.ordreTriPoid = 3;
					else
						menudonnees.ordreTriPoid = 0;
				}
			}
			if (menudonnees.ordreTriPoid == 1)
				vline(((2 * disp_data.width / 7 - 50) + (2 * disp_data.width / 7 - 20)) / 2, (hauteurTRI + hauteurTRI+30) / 2 + 5, colorcase);
			else if (menudonnees.ordreTriPoid == 2)
				vline(((3 * disp_data.width / 7 - 52) + (3 * disp_data.width / 7 - 22)) / 2, (hauteurTRI + hauteurTRI + 30) / 2 + 5, colorcase);
			else if (menudonnees.ordreTriPoid == 3)
				vline(((4 * disp_data.width / 7 - 90) + (4 * disp_data.width / 7 - 120)) / 2, (hauteurTRI + hauteurTRI + 30) / 2 + 5, colorcase);

			//Choix de l'algorithme
			al_draw_text(font8, al_map_rgb(100, 0, 0), 1 * disp_data.width / 7, hauteurAlgo, ALLEGRO_ALIGN_LEFT, "ALGORITHME :");

			al_draw_text(font8, al_map_rgb(100, 0, 0), 2 * disp_data.width / 7, hauteurAlgo, ALLEGRO_ALIGN_LEFT, "Dijkstra");
			al_draw_rectangle(2 * disp_data.width / 7 - 50, hauteurAlgo, 2 * disp_data.width / 7 - 20, hauteurAlgo + 30, colorcase, 2);

			al_draw_text(font8, al_map_rgb(100, 0, 0), 3 * disp_data.width / 7, hauteurAlgo, ALLEGRO_ALIGN_LEFT, "Prim");
			al_draw_rectangle(3 * disp_data.width / 7 - 52, hauteurAlgo, 3 * disp_data.width / 7 - 22, hauteurAlgo + 30, colorcase, 2);

			al_draw_text(font8, al_map_rgb(100, 0, 0), 4 * disp_data.width / 7 - 60, hauteurAlgo, ALLEGRO_ALIGN_LEFT, "Pareto");
			al_draw_rectangle(4 * disp_data.width / 7 - 90, hauteurAlgo, 4 * disp_data.width / 7 - 120, hauteurAlgo + 30, colorcase, 2);

			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				if (event.mouse.x >= 2 * disp_data.width / 7 - 50 && event.mouse.x < 2 * disp_data.width / 7 - 20 && event.mouse.y >= hauteurAlgo && event.mouse.y < hauteurAlgo + 30)
				{
					if (menudonnees.algoChoix != 1)
						menudonnees.algoChoix = 1;
					else
						menudonnees.algoChoix = 0;
				}
				if (event.mouse.x >= 3 * disp_data.width / 7 - 52 && event.mouse.x < 3 * disp_data.width / 7 - 22 && event.mouse.y >= hauteurAlgo && event.mouse.y < hauteurAlgo + 30)
				{
					if (menudonnees.algoChoix != 2)
						menudonnees.algoChoix = 2;
					else
						menudonnees.algoChoix = 0;
				}
				if (event.mouse.x >= 4 * disp_data.width / 7 - 120 && event.mouse.x < 4 * disp_data.width / 7 - 90 && event.mouse.y >= hauteurAlgo && event.mouse.y < hauteurAlgo + 30)
				{
					if (menudonnees.algoChoix != 3)
						menudonnees.algoChoix = 3;
					else
						menudonnees.algoChoix = 0;
				}
			}
			if (menudonnees.algoChoix == 1)
				vline(((2 * disp_data.width / 7 - 50) + (2 * disp_data.width / 7 - 20)) / 2, (hauteurAlgo + hauteurAlgo + 30) / 2 + 5, colorcase);
			else if (menudonnees.algoChoix == 2)
				vline(((3 * disp_data.width / 7 - 52) + (3 * disp_data.width / 7 - 22)) / 2, (hauteurAlgo + hauteurAlgo + 30) / 2 + 5, colorcase);
			else if (menudonnees.algoChoix == 3)
				vline(((4 * disp_data.width / 7 - 90) + (4 * disp_data.width / 7 - 120)) / 2, (hauteurAlgo + hauteurAlgo + 30) / 2 + 5, colorcase);

			//Aller au menu suivant
			if (event.mouse.x >= 5 * disp_data.width / 8 && event.mouse.x < 7 * disp_data.width / 8 + 20 && event.mouse.y >= 7 * disp_data.height / 8 - 50 && event.mouse.y < 7 * disp_data.height / 8 + 50)
			{
				al_draw_rounded_rectangle(5 * disp_data.width / 8, 7 * disp_data.height / 8 - 50, 7 * disp_data.width / 8 + 20, 7 * disp_data.height / 8 + 50, 50, 50, al_map_rgb(255, 0, 0), 10);
				al_draw_text(font8, al_map_rgb(255, 0, 0), ((5 * disp_data.width / 8) + (7 * disp_data.width / 8 + 20)) / 2, ((7 * disp_data.height / 8 - 50) + (7 * disp_data.height / 8 + 50)) / 2 - 10, ALLEGRO_ALIGN_CENTRE, "SUITE ->");
				if (menudonnees.algoChoix != 0)
				{
					if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && menudonnees.ordreTriPoid != 0 && menudonnees.algoChoix != 0)
					{
						choixcase = false;
						if (menudonnees.algoChoix == 1 || menudonnees.algoChoix == 2)
							primDijkstra = true;
						else if (menudonnees.algoChoix == 3)
							pareto = true;
					}
				}
			}
			else
			{
				al_draw_rounded_rectangle(5 * disp_data.width / 8, 7 * disp_data.height / 8 - 50, 7 * disp_data.width / 8 + 20, 7 * disp_data.height / 8 + 50, 50, 50, al_map_rgb(0, 255, 0), 10);
				al_draw_text(font8, al_map_rgb(0, 255, 0), ((5 * disp_data.width / 8) + (7 * disp_data.width / 8 + 20)) / 2, ((7 * disp_data.height / 8 - 50) + (7 * disp_data.height / 8 + 50)) / 2 - 10, ALLEGRO_ALIGN_CENTRE, "SUITE ->");
			}

			//Revenir au menu precedent
			if (event.mouse.x >= 1 * disp_data.width / 8 -20 && event.mouse.x < 3 * disp_data.width / 8 && event.mouse.y >= 7 * disp_data.height / 8 - 50 && event.mouse.y < 7 * disp_data.height / 8 + 50)
			{
				al_draw_rounded_rectangle(1 * disp_data.width / 8-20, 7 * disp_data.height / 8 - 50, 3 * disp_data.width / 8 , 7 * disp_data.height / 8 + 50, 50, 50, al_map_rgb(255, 0, 0), 10);
				al_draw_text(font8, al_map_rgb(255, 0, 0), ((3 * disp_data.width / 8) + (1 * disp_data.width / 8 - 20)) / 2, ((7 * disp_data.height / 8 - 50) + (7 * disp_data.height / 8 + 50)) / 2 - 10, ALLEGRO_ALIGN_CENTRE, "<-- PRECEDENT");
				if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{
					choix = true;
					choixcase = false;
				}
			}
			else
			{
				al_draw_rounded_rectangle(1 * disp_data.width / 8-20, 7 * disp_data.height / 8 - 50, 3 * disp_data.width / 8, 7 * disp_data.height / 8 + 50, 50, 50, al_map_rgb(0, 255, 0), 10);
				al_draw_text(font8, al_map_rgb(0, 255, 0), ((3 * disp_data.width / 8) + (1 * disp_data.width / 8 - 20)) / 2, ((7 * disp_data.height / 8 - 50) + (7 * disp_data.height / 8 + 50)) / 2 - 10, ALLEGRO_ALIGN_CENTRE, "<-- PRECEDENT");
			}
		}

		//3eme page des options
		//Si PrimoOu Dijkstra est selectionné
		if (primDijkstra)
		{
			int hauteurArrivee = disp_data.height / 4 + 160;
			int hauteurDepart = hauteurArrivee + 80;
			int hauteurordre = hauteurArrivee - 80;
			ALLEGRO_EVENT ev;
			al_wait_for_event(queue, &event);
			al_draw_scaled_bitmap(imagechoix, 0, 0, al_get_bitmap_width(imagechoix), al_get_bitmap_height(imagechoix), 0, 0, disp_data.width, disp_data.height, 0);
			al_get_next_event(event_queue, &ev);

			al_get_mouse_state(&mouse);
			al_get_keyboard_state(&keyboard);
			al_draw_text(fontMatrix, al_map_rgb(100, 0, 0), disp_data.width / 2, disp_data.height / 8, ALLEGRO_ALIGN_CENTRE, "OPTIONS");
				al_draw_text(font8, al_map_rgb(100, 0, 0), disp_data.width / 6, hauteurDepart, ALLEGRO_ALIGN_CENTRE, "DEPART :");

				//Si Dijkstra est selectionnée
				if (menudonnees.algoChoix == 1)
					al_draw_text(font8, al_map_rgb(100, 0, 0), disp_data.width / 6, hauteurArrivee, ALLEGRO_ALIGN_CENTRE, "ARRIVEE :");
				al_draw_text(font8, al_map_rgb(100, 0, 0), disp_data.width / 6, hauteurordre, ALLEGRO_ALIGN_CENTRE, "QUELS POIDS :");
				//Creation des endroits pour écrire
				textbox(disp_data.width / 4, hauteurDepart, 5, 25, 2);
				if (menudonnees.algoChoix == 1)
					textbox(disp_data.width / 4, hauteurArrivee, 5, 25, 3);
				textbox(disp_data.width / 4, hauteurordre, 5, 25, 4);
				//On recupere ce qui est écrit
				menudonnees.depart = text_boxes[2].c_str();
				menudonnees.arrivee = text_boxes[3].c_str();
				menudonnees.quelPoid = text_boxes[4].c_str();
			ALLEGRO_EVENT event;
			al_wait_for_event(queue, &event);

			if (event.mouse.x >= 5 * disp_data.width / 8 && event.mouse.x < 7 * disp_data.width / 8 + 20 && event.mouse.y >= 7 * disp_data.height / 8 - 50 && event.mouse.y < 7 * disp_data.height / 8 + 50)
			{
				al_draw_rounded_rectangle(5 * disp_data.width / 8, 7 * disp_data.height / 8 - 50, 7 * disp_data.width / 8 + 20, 7 * disp_data.height / 8 + 50, 50, 50, al_map_rgb(255, 0, 0), 10);
				al_draw_text(font8, al_map_rgb(255, 0, 0), ((5 * disp_data.width / 8) + (7 * disp_data.width / 8 + 20)) / 2, ((7 * disp_data.height / 8 - 50) + (7 * disp_data.height / 8 + 50)) / 2 - 10, ALLEGRO_ALIGN_CENTRE, "FIN");
				if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{
					break;
					boucle=false;
					primDijkstra = false;
				}
			}
			else
			{
				al_draw_rounded_rectangle(5 * disp_data.width / 8, 7 * disp_data.height / 8 - 50, 7 * disp_data.width / 8 + 20, 7 * disp_data.height / 8 + 50, 50, 50, al_map_rgb(0, 255, 0), 10);
				al_draw_text(font8, al_map_rgb(0, 255, 0), ((5 * disp_data.width / 8) + (7 * disp_data.width / 8 + 20)) / 2, ((7 * disp_data.height / 8 - 50) + (7 * disp_data.height / 8 + 50)) / 2 - 10, ALLEGRO_ALIGN_CENTRE, "FIN");
			}

			//Revenir au menu precedent
			if (event.mouse.x >= 1 * disp_data.width / 8 - 20 && event.mouse.x < 3 * disp_data.width / 8 && event.mouse.y >= 7 * disp_data.height / 8 - 50 && event.mouse.y < 7 * disp_data.height / 8 + 50)
			{
				al_draw_rounded_rectangle(1 * disp_data.width / 8 - 20, 7 * disp_data.height / 8 - 50, 3 * disp_data.width / 8, 7 * disp_data.height / 8 + 50, 50, 50, al_map_rgb(255, 0, 0), 10);
				al_draw_text(font8, al_map_rgb(255, 0, 0), ((3 * disp_data.width / 8) + (1 * disp_data.width / 8 - 20)) / 2, ((7 * disp_data.height / 8 - 50) + (7 * disp_data.height / 8 + 50)) / 2 - 10, ALLEGRO_ALIGN_CENTRE, "<-- PRECEDENT");
				if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{
					primDijkstra = false;
					choixcase = true;
				}
			}
			else
			{
				al_draw_rounded_rectangle(1 * disp_data.width / 8 - 20, 7 * disp_data.height / 8 - 50, 3 * disp_data.width / 8, 7 * disp_data.height / 8 + 50, 50, 50, al_map_rgb(0, 255, 0), 10);
				al_draw_text(font8, al_map_rgb(0, 255, 0), ((3 * disp_data.width / 8) + (1 * disp_data.width / 8 - 20)) / 2, ((7 * disp_data.height / 8 - 50) + (7 * disp_data.height / 8 + 50)) / 2 - 10, ALLEGRO_ALIGN_CENTRE, "<-- PRECEDENT");
			}
		}

		//3eme pas des options BIS
		//Si pareto est selectionné
		if (pareto)
		{
			ALLEGRO_EVENT event;
			al_wait_for_event(queue, &event);
			al_draw_scaled_bitmap(imagechoix, 0, 0, al_get_bitmap_width(imagechoix), al_get_bitmap_height(imagechoix), 0, 0, disp_data.width, disp_data.height, 0);
			al_draw_text(fontMatrix, al_map_rgb(100, 0, 0), disp_data.width / 2, disp_data.height / 8, ALLEGRO_ALIGN_CENTRE, "OPTIONS");
			int hauteur2 = disp_data.height / 4 + 160;
			int hauteur3 = hauteur2 + 80;
			int hauteur1 = hauteur2 - 80;
			int largeur = disp_data.width / 6;
			//Choix si il y a un cycle ou non
			al_draw_text(font8, al_map_rgb(100, 0, 0), disp_data.width / 6, hauteur1, ALLEGRO_ALIGN_CENTRE, "CYCLE :");
			al_draw_rectangle(1 * disp_data.width / 5 + 100, hauteur1, 1 * disp_data.width / 5 + 130, hauteur1 + 30, colorcase, 2);
			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				if (event.mouse.x >= 1 * disp_data.width / 5 + 100 && event.mouse.x < 1 * disp_data.width / 5 + 130 && event.mouse.y >= hauteur1 && event.mouse.y < hauteur1 + 30)
				{
					if (!menudonnees.cycle)
						menudonnees.cycle = true;
					else
						menudonnees.cycle = false;
				}
			}
			if (menudonnees.cycle)
				vline(((1 * disp_data.width / 5 + 100) + (1 * disp_data.width / 5 + 130)) / 2, (hauteur1 + hauteur1 + 30) / 2 + 5, colorcase);

			//Choix optimisation bi objectif
			int i = 0;
			for (auto poidActuel : menudonnees.poids)
			{
				int affichage = i + 1;
				al_draw_textf(font8, al_map_rgb(100, 0, 0), largeur+i*150, hauteur3, ALLEGRO_ALIGN_CENTRE, "poids : %d",affichage);
				al_draw_rectangle(largeur + i * 150+60, hauteur3, largeur + i * 150+90, hauteur3+30, colorcase, 2);

				if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
				{
					if (event.mouse.x >= largeur + i * 150 + 60 && event.mouse.x < largeur + i * 150 + 90 && event.mouse.y >= hauteur3 && event.mouse.y < hauteur3 + 30)
					{
						if (!poidActuel)
							poidActuel = true;
						else
							poidActuel = false;
					}
				}
				if (poidActuel)
					vline(((largeur + i * 150 + 60) + (largeur + i * 150 + 90)) / 2, (hauteur3 + hauteur3 + 30) / 2 + 5, colorcase);
				i++;
			}

			//Finir d'édieter les parametres
			if (event.mouse.x >= 5 * disp_data.width / 8 && event.mouse.x < 7 * disp_data.width / 8 + 20 && event.mouse.y >= 7 * disp_data.height / 8 - 50 && event.mouse.y < 7 * disp_data.height / 8 + 50)
			{
				al_draw_rounded_rectangle(5 * disp_data.width / 8, 7 * disp_data.height / 8 - 50, 7 * disp_data.width / 8 + 20, 7 * disp_data.height / 8 + 50, 50, 50, al_map_rgb(255, 0, 0), 10);
				al_draw_text(font8, al_map_rgb(255, 0, 0), ((5 * disp_data.width / 8) + (7 * disp_data.width / 8 + 20)) / 2, ((7 * disp_data.height / 8 - 50) + (7 * disp_data.height / 8 + 50)) / 2 - 10, ALLEGRO_ALIGN_CENTRE, "FIN");
				if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{
					cout << "sort";
					boucle = false;
					pareto = false;
					break;
				}
			}
			else
			{
				al_draw_rounded_rectangle(5 * disp_data.width / 8, 7 * disp_data.height / 8 - 50, 7 * disp_data.width / 8 + 20, 7 * disp_data.height / 8 + 50, 50, 50, al_map_rgb(0, 255, 0), 10);
				al_draw_text(font8, al_map_rgb(0, 255, 0), ((5 * disp_data.width / 8) + (7 * disp_data.width / 8 + 20)) / 2, ((7 * disp_data.height / 8 - 50) + (7 * disp_data.height / 8 + 50)) / 2 - 10, ALLEGRO_ALIGN_CENTRE, "FIN");
			}

			//Revenir au menu precedent
			if (event.mouse.x >= 1 * disp_data.width / 8 - 20 && event.mouse.x < 3 * disp_data.width / 8 && event.mouse.y >= 7 * disp_data.height / 8 - 50 && event.mouse.y < 7 * disp_data.height / 8 + 50)
			{
				al_draw_rounded_rectangle(1 * disp_data.width / 8 - 20, 7 * disp_data.height / 8 - 50, 3 * disp_data.width / 8, 7 * disp_data.height / 8 + 50, 50, 50, al_map_rgb(255, 0, 0), 10);
				al_draw_text(font8, al_map_rgb(255, 0, 0), ((3 * disp_data.width / 8) + (1 * disp_data.width / 8 - 20)) / 2, ((7 * disp_data.height / 8 - 50) + (7 * disp_data.height / 8 + 50)) / 2 - 10, ALLEGRO_ALIGN_CENTRE, "<-- PRECEDENT");
				if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{
					choixcase = true;
					pareto = false;
				}
			}
			else
			{
				al_draw_rounded_rectangle(1 * disp_data.width / 8 - 20, 7 * disp_data.height / 8 - 50, 3 * disp_data.width / 8, 7 * disp_data.height / 8 + 50, 50, 50, al_map_rgb(0, 255, 0), 10);
				al_draw_text(font8, al_map_rgb(0, 255, 0), ((3 * disp_data.width / 8) + (1 * disp_data.width / 8 - 20)) / 2, ((7 * disp_data.height / 8 - 50) + (7 * disp_data.height / 8 + 50)) / 2 - 10, ALLEGRO_ALIGN_CENTRE, "<-- PRECEDENT");
			}
		}
		
	}

	//al_draw_bitmap(imagepresentation, 100, 100, 0);
	//al_destroy_bitmap(imagepresentation);
}

//Code pour créer des boites de text dans Allegro 5 récupérer sur internet
//https://www.youtube.com/watch?v=EEowjItqdOc
//https://drive.google.com/file/d/0B-kt8cFQnmYNTURobFVsQlpTVE0/view
void textbox(int coordinate_x, int coordinate_y, int number_signs, int coordinate_command_prompt, int number_text_box)
{
	//Affichage de la feunetre d'ecriture
	al_draw_rectangle(coordinate_x - 2, coordinate_y - 2, coordinate_x + 16 * number_signs + 2, coordinate_y + 32, al_map_rgba(255, 255, 255, 255), 1);

	if ((mouse.x > coordinate_x - 2 && mouse.x < coordinate_x + 16 * number_signs) && (mouse.y > coordinate_y - 2 && mouse.y < coordinate_y + 32) && mouse.buttons == 1)
	{
		for (int i = 0; i < number_text_boxes; i++)
		{
			switch_text_boxes[i] = 0;
		}

		switch_text_boxes[number_text_box] = 1;		// activation of the textbox when press the rectangle  

		al_rest(0.15);
	}

	string Signs[47] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

	if (switch_text_boxes[number_text_box] == 1) 		// active the textbox
	{
		al_draw_line(coordinate_x - 42+ command_prompt[number_text_box]*1.8, coordinate_y - 1, coordinate_x-42+command_prompt[number_text_box]*1.8, coordinate_y + 31, al_map_rgba(255, 255, 255, 255), 1); // command prompt
		//al_draw_line()
		for (int i = 0; i < 47; i++)
		{
			if (al_key_down(&keyboard, i))
			{
				if (text_boxes[number_text_box].length() < number_signs)
				{
					text_boxes[number_text_box].insert((command_prompt[number_text_box] - coordinate_command_prompt) / 8, Signs[i - 1].c_str());
					command_prompt[number_text_box] += 8;
					al_rest(0.15);
				}
			}
		}

		if (al_key_down(&keyboard, ALLEGRO_KEY_BACKSPACE))
		{
			if (text_boxes[number_text_box].length() > 0 && command_prompt[number_text_box] != coordinate_command_prompt)
			{
				text_boxes[number_text_box] = text_boxes[number_text_box].erase(((command_prompt[number_text_box] - coordinate_command_prompt) / 8) - 1, 1);
			}

			if (command_prompt[number_text_box] > coordinate_command_prompt + 7)
			{
				command_prompt[number_text_box] -= 8;
			}

			al_rest(0.15);
		}

		if (al_key_down(&keyboard, ALLEGRO_KEY_LEFT))
		{
			if (command_prompt[number_text_box] > coordinate_command_prompt + 7)
			{
				command_prompt[number_text_box] -= 8;
			}
			al_rest(0.15);
		}

		if (al_key_down(&keyboard, ALLEGRO_KEY_RIGHT))
		{
			if (command_prompt[number_text_box] < coordinate_command_prompt + 8 * text_boxes[number_text_box].length())
			{
				command_prompt[number_text_box] += 8;
			}
			al_rest(0.15);
		}
	}

	al_draw_text(font8, al_map_rgb(255, 255, 255), coordinate_x, coordinate_y, 0, text_boxes[number_text_box].c_str());
}

//Fonction pour cocher une case avec un v
void vline(int x1, int y1,ALLEGRO_COLOR couleur)
{
	al_draw_line(x1, y1, x1 - 19, y1 - 19, couleur, 2);
	al_draw_line(x1, y1, x1 + 24, y1 - 24, couleur, 2);
}