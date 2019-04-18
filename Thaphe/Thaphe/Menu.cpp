#include "Menu.h"

using namespace std;

float FPS = 60;

int number_text_boxes = 2;	// the number of textboxes 

int* switch_text_boxes;
string* text_boxes;
int* command_prompt;

ALLEGRO_KEYBOARD_STATE keyboard;
ALLEGRO_FONT* font8;
ALLEGRO_MOUSE_STATE mouse;

void textbox(int coordinate_x, int coordinate_y, int number_signs, int coordinate_command_prompt, int number_text_box);

void leMenu(MenuDonnees menudonnees,ALLEGRO_DISPLAY* display)
{
	ALLEGRO_BITMAP* imagepresentation;
	ALLEGRO_BITMAP* imagechoix;
	ALLEGRO_BITMAP* choix1;
	bool boucle = true;
	bool pres = true;
	bool choix = false;
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
	font8 = al_create_builtin_font();
	bool redraw = true;

	text_boxes = new string[number_text_boxes];

	command_prompt = new int[number_text_boxes];
	for (int i = 0; i < number_text_boxes; i++)
	{
		command_prompt[i] = 25;	// the initial coordinates command prompts are the same as the coordinates x
	}


	while (boucle)
	{
		al_flip_display();
		if (pres)
		{
			ALLEGRO_EVENT event;
			al_wait_for_event(queue, &event);
			al_draw_bitmap(imagepresentation, 0, 0, 0);
			al_draw_text(fontMatrix, al_map_rgb(0, 255, 0), width / 2, height / 6, ALLEGRO_ALIGN_CENTRE, "Theorie des graphes");
			al_draw_rounded_rectangle(width / 4 + 20, height / 2 + 50, 3 * width / 4 - 20, height / 2 + 200, 50, 50, al_map_rgb(255, 0, 0), 10);
			//Ecriture de nos nom en bas de la page de garde
			al_draw_text(fontMatrixPetit, al_map_rgb(150, 0, 0), 20, height - 130, ALLEGRO_ALIGN_LEFT, "Combe Antoine");
			al_draw_text(fontMatrixPetit, al_map_rgb(150, 0, 0), 20, height - 90, ALLEGRO_ALIGN_LEFT, "De Malliard Jean");
			al_draw_text(fontMatrixPetit, al_map_rgb(150, 0, 0), 20, height - 50, ALLEGRO_ALIGN_LEFT, "Gaucher Matthieu");

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
			ALLEGRO_EVENT event;
			al_wait_for_event(queue, &event);
				if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				{
					choix = false;
					boucle = false;
				}
			al_draw_bitmap(imagechoix, 0, 0, 0);
			al_draw_text(fontMatrix, al_map_rgb(100, 0, 0), width/2, height/8, ALLEGRO_ALIGN_CENTRE, "OPTIONS");
			al_get_next_event(event_queue, &event);

			al_get_mouse_state(&mouse);
			al_get_keyboard_state(&keyboard);

			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);

			if (ev.type == ALLEGRO_EVENT_TIMER)
			{
				redraw = true;
			}
			textbox(25, 25, 20, 25, 0);
			menudonnees.graphe = text_boxes[0].c_str();
			cout << menudonnees.graphe<<endl;
			if (redraw && al_is_event_queue_empty(event_queue))
			{
				redraw = false;
				al_flip_display();
			}

			al_flip_display();

		}
		
	}

	//al_draw_bitmap(imagepresentation, 100, 100, 0);
	//al_destroy_bitmap(imagepresentation);
}

//Code pour créer des boites de text dans Allegro 5 récupérer sur internet

void textbox(int coordinate_x, int coordinate_y, int number_signs, int coordinate_command_prompt, int number_text_box)
{
	al_draw_rectangle(coordinate_x - 2, coordinate_y - 2, coordinate_x + 8 * number_signs + 2, coordinate_y + 10, al_map_rgba(255, 255, 255, 255), 1);	// border of the textbox

	if ((mouse.x > coordinate_x - 2 && mouse.x < coordinate_x + 8 * number_signs) && (mouse.y > coordinate_y - 2 && mouse.y < coordinate_y + 10) && mouse.buttons == 1)
	{
		for (int i = 0; i < number_text_boxes; i++)
		{
			switch_text_boxes[i] = 0;
		}

		switch_text_boxes[number_text_box] = 1;		// activation of the textbox when press the rectangle  

		al_rest(0.15);
	}

	string Signs[47] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

	if (switch_text_boxes[number_text_box] == 1) 		// active the textbox
	{
		al_draw_line(command_prompt[number_text_box], coordinate_y - 1, command_prompt[number_text_box], coordinate_y + 8, al_map_rgba(255, 255, 255, 255), 1); // command prompt

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
