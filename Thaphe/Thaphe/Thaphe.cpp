#include <iostream>
#include "Graphe.h"
#include "Menu.h"

int main(int argc, char** argv) 
{
	bool showGraphs = true;
	bool menu = true;

	//Initialisation d'Allegro
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_BITMAP* screen = NULL;
	ALLEGRO_DISPLAY_MODE   disp_data;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;

	if (!al_init())
		throw std::runtime_error("Probleme init allegro");
	if (!al_init_primitives_addon())
		throw std::runtime_error("Probleme init primitives addon");
	if (!al_init_font_addon())
		throw std::runtime_error("Probleme init font addon");
	if (!al_init_ttf_addon())
		throw std::runtime_error("Probleme init ttf addon");
	if (!al_init_image_addon())
		throw std::runtime_error("Probleme init image addon");

	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	
	display = al_create_display(disp_data.width, disp_data.height);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}
	screen = al_create_bitmap(disp_data.width, disp_data.height);
	if (!screen) {
		fprintf(stderr, "failed to create buffer!\n");
		return -1;
	}

	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}

	if(!al_install_keyboard())
		throw std::runtime_error("Impossible d'utiliser le clavier");
	if (!al_install_mouse())
		throw std::runtime_error("Impossible d'utiliser la souris");

	al_clear_to_color(al_map_rgb(133, 50, 50));

	ALLEGRO_FONT* font;
	font = al_load_font("simple_font.ttf", 30, 0);

	MenuDonnees choix{ ((std::string)"broadway"), ((std::string)"1"), 0, false, 4, 0, 3, false, std::bitset<nombreMaxPoids>(0),false };
	if (menu)
		leMenu(choix, display);
	else
		chargerChoixMenu(choix);

	double start = al_get_time();

	std::list<graphePareto> grapheResults;
	Graphe gr(choix);
	
	//Un switch ignore l'initialisation de grapheResults
	if (choix.algoChoix == 1)
		grapheResults.push_back(graphePareto{ {(float)gr.Dijkstra(choix.quelPoid, choix.depart, choix.arrivee).count()}, gr.Dijkstra(choix.quelPoid, choix.depart, choix.arrivee) });
	if (choix.algoChoix == 2)
		grapheResults.push_back(graphePareto{ {(float)gr.Prim(choix.quelPoid, choix.depart).count()}, gr.Prim(choix.quelPoid, choix.depart) });
	if (choix.algoChoix == 3)
		grapheResults = gr.TriPareto();
	if (choix.algoChoix == 4)
	{
		std::vector<std::bitset<nombreMaxAretes>> tousLesSousGraphes{ gr.DeterminerSousGraphe() };
		for (auto ssg : tousLesSousGraphes)
			grapheResults.push_back(graphePareto{ {(float)ssg.count()}, ssg });
	}
	if (choix.algoChoix == 5)
		grapheResults.push_back(graphePareto{ {(float)gr.getNombreAretes()}, std::bitset<nombreMaxAretes>(pow(2, gr.getNombreAretes())-1) });


	int width = 1;
	int nbGraphes = (int)grapheResults.size();
	std::vector<graphePareto> graphesToShow;
	if (!grapheResults.empty())
	{
		std::cout << "Temps de recherche des graphes : " << al_get_time() - start << " sec\n";

		gr.createColors();

		width = (double)((double)sqrt((double)((disp_data.height * disp_data.width) / nbGraphes) / (double)((double)disp_data.width / (double)disp_data.height)));

		//std::cout << width << "  " << (double)((double)disp_data.width / (double)disp_data.height) << std::endl;
		int i = 0, x, y, divx = (disp_data.width / width);
		if (divx > nbGraphes)
			divx = nbGraphes;

		al_set_target_bitmap(screen);
		al_clear_to_color(al_map_rgb(200, 250, 215));
		/*
		for (int j = 0; j < 6; j++)
			al_draw_filled_rectangle(disp_data.width - 6 * 10 + j * 10, disp_data.height - 10, disp_data.width - 5 * 10 + j * 10, disp_data.height, gr.m_colors[j]);*/

		for (auto ssg : grapheResults)
		{
			gr.Colorer(ssg.aretes);
			graphesToShow.push_back(ssg);
			ALLEGRO_BITMAP* graphe = gr.DessinerSousGraphePar(ssg);
			al_set_target_bitmap(screen);

			x = i % divx * width  /*(disp_data.width - divx * width) / 2 */ + disp_data.height / 200;
			y = (i / divx) * width  /*(disp_data.height - divy * width) / 2 */ + disp_data.height / 200;
			al_draw_scaled_bitmap(graphe, 0, 0, al_get_bitmap_width(graphe), al_get_bitmap_height(graphe), x, y, width - disp_data.height / 100, width - disp_data.height / 100, 0);

			al_destroy_bitmap(graphe);
			i++;
		}
	}
	else
		al_draw_text(font, al_map_rgb(255, 255, 255), 20, 20, 0, "Aucun graphe a afficher");

	al_set_target_backbuffer(display);
	al_draw_bitmap(screen, 0, 0, 0);
	al_flip_display();
	std::cout << "Temps d'execution total : " << al_get_time() - start << " sec\n";

	if (showGraphs)
	{
		al_register_event_source(event_queue, al_get_display_event_source(display));
		al_register_event_source(event_queue, al_get_mouse_event_source());
		al_register_event_source(event_queue, al_get_keyboard_event_source());
	}
	

	while (showGraphs)
	{
		ALLEGRO_EVENT ev;
		ALLEGRO_TIMEOUT timeout;

		if (al_wait_for_event_timed(event_queue, &ev, 0.5))
		{
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				if (al_get_pixel(screen, ev.mouse.x, ev.mouse.y).r != al_map_rgb(200, 250, 215).r && al_get_pixel(screen, ev.mouse.x, ev.mouse.y).g != al_map_rgb(200, 250, 215).g && al_get_pixel(screen, ev.mouse.x, ev.mouse.y).b != al_map_rgb(200, 250, 215).b)
				{
					al_draw_bitmap(screen, 0, 0, 0);

					int indice = ((int)ev.mouse.x / width + (int)(((int)disp_data.width / width) * ((int)ev.mouse.y / width)));
					int newWidth = (2 * disp_data.height) / 3;
					gr.Colorer(graphesToShow[indice].aretes);
					ALLEGRO_BITMAP * wantedGraphe = gr.DessinerSousGraphePar(graphesToShow[indice]);

					al_set_target_backbuffer(display);
					al_draw_scaled_bitmap(wantedGraphe, 0, 0, al_get_bitmap_width(wantedGraphe), al_get_bitmap_height(wantedGraphe), (disp_data.width - newWidth) / 2, (disp_data.height - newWidth) / 2, newWidth, newWidth, 0);
					al_flip_display();

					do
					{
						1;
					} while (!(al_wait_for_event_timed(event_queue, &ev, 0.5) && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN));

					al_draw_bitmap(screen, 0, 0, 0);
					al_flip_display();
				}
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
				break;
		}

		
	}

	al_clear_to_color(al_map_rgb(100, 100, 100));
	ALLEGRO_FONT* endFont = al_load_font("simple_font.ttf", 30, 0);
	al_draw_text(endFont, al_map_rgb(255, 255, 255), 10, 10, 0, "Fermeture de la fenetre en cours...");
	al_flip_display();

	al_destroy_display(display);
	al_destroy_event_queue(event_queue);


	return 0;
}