#include "Menu.h"

using namespace std;

void leMenu(MenuDonnees menudonnees,ALLEGRO_DISPLAY* display)
{
	ALLEGRO_BITMAP* imagepresentation;
	ALLEGRO_BITMAP* choix1;
	bool boucle = true;
	bool pres = true;
	bool choix = false;
	if (!al_init_image_addon())
	{
		cout<<"couldn't initialize image addon\n";
	}
	imagepresentation = al_load_bitmap("presentation.png");
	if (!imagepresentation)
	{
		cout << "L'image de presentation ne peut pas etre charge" << endl;
		al_destroy_bitmap(imagepresentation);
		exit;
	}
	al_draw_bitmap(imagepresentation, 0, 0, 0);
	//Initialisation de la gestion d'evenements
	ALLEGRO_EVENT_QUEUE* queue;
	queue = al_create_event_queue();
	al_install_keyboard();
	al_install_mouse();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	ALLEGRO_FONT* fontMatrix;
	fontMatrix = al_load_font("Matrix.ttf", 100, 0);
	ALLEGRO_FONT* fontMatrixPetit;
	fontMatrixPetit = al_load_font("simple_font.ttf", 40, 0);



	while (boucle)
	{
		al_flip_display();
		if (pres)
		{
			ALLEGRO_EVENT event;
			al_wait_for_event(queue, &event);
			al_draw_text(fontMatrix, al_map_rgb(0, 255, 0), width / 2, height / 6, ALLEGRO_ALIGN_CENTRE, "Theorie des graphes");
			al_draw_rounded_rectangle(width / 4 + 20, height / 2 + 50, 3 * width / 4 - 20, height / 2 + 200, 50, 50, al_map_rgb(255, 0, 0), 10);
			//Ecriture de nos nom en bas de la page de garde
			al_draw_text(fontMatrixPetit, al_map_rgb(100, 0, 0), 20, height - 130, ALLEGRO_ALIGN_LEFT, "Combe Antoine");
			al_draw_text(fontMatrixPetit, al_map_rgb(100, 0, 0), 20, height - 90, ALLEGRO_ALIGN_LEFT, "De Malliard Jean");
			al_draw_text(fontMatrixPetit, al_map_rgb(100, 0, 0), 20, height - 50, ALLEGRO_ALIGN_LEFT, "Gaucher Matthieu");

			/*if (event.type == ALLEGRO_EVENT_KEY_UP)
			{
				al_draw_bitmap(imagepresentation, event.mouse.x, event.mouse.y, 0);
				if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
					pres = false;
			}*/
			if (event.mouse.x >= width / 4 + 20 && event.mouse.x < 3 * width / 4 - 20 && event.mouse.y >= height / 2 + 50 && event.mouse.y < height / 2 + 200)
			{
				al_draw_rounded_rectangle(width / 4 + 20, height / 2 + 50, 3 * width / 4 - 20, height / 2 + 200, 50, 50, al_map_rgb(255, 0, 0), 10);
				al_draw_text(fontMatrix, al_map_rgb(255, 0, 0), width / 2, ((height / 2 + 50) + (height / 2 + 200)) / 2 - 32, ALLEGRO_ALIGN_CENTRE, "Start");
			}
			else 
			{
				al_draw_rounded_rectangle(width / 4 + 20, height / 2 + 50, 3 * width / 4 - 20, height / 2 + 200, 50, 50, al_map_rgb(0, 255, 0), 10);
				al_draw_text(fontMatrix, al_map_rgb(0, 255, 0), width / 2, ((height / 2 + 50) + (height / 2 + 200)) / 2 - 32, ALLEGRO_ALIGN_CENTRE, "Start");
			}
			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				if (event.mouse.x >= width / 4 + 20 && event.mouse.x < 3 * width / 4 - 20 && event.mouse.y >= height / 2 + 50 && event.mouse.y < height / 2 + 200)
				{
					pres = false;
					choix = true;
				}
			}
		}
		if (choix)
		{

		}
	}

	//al_draw_bitmap(imagepresentation, 100, 100, 0);
	//al_destroy_bitmap(imagepresentation);
}