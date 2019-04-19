#include <iostream>
#include "Graphe.h"

int main(int argc, char** argv) 
{
	bool showGraphs = true;

	//Initialisation d'Allegro
	ALLEGRO_DISPLAY* display = NULL;
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

	double start = al_get_time();

	Graphe gr("manhattan", false, std::bitset<nombreMaxPoids>(2));


	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	
	display = al_create_display(disp_data.width, disp_data.height);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
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

	//TOUS LES SOUS GRAPHES CONNEXES AVEC OU SANS CYCLES
	if (false)
	{
		
		std::vector<std::bitset<nombreMaxAretes>> tousLesSousGraphes;
		tousLesSousGraphes = gr.DeterminerSousGraphe(false);

		for (auto ssg : tousLesSousGraphes)
		{
			ALLEGRO_BITMAP* graphe = gr.DessinerSousGraphe(ssg);
			al_set_target_backbuffer(display);

			al_clear_to_color(al_map_rgb(133, 50, 50));
			al_draw_bitmap(graphe, 500, 100, 0);
			al_draw_text(font, al_map_rgb(0, 0, 0), 500, 80, 0, ssg.to_string().c_str());
			//al_draw_text(font, al_map_rgb(0, 0, 0), 700, 80, 0, ((gr.isConnexe(ssg)) ? "co" : "paco"));
			//std::cout << ssg << std::endl;

			al_flip_display();
			al_rest(0.5);
			al_destroy_bitmap(graphe);
		}

		std::cout << "Temps d'execution : " << al_get_time() - start << std::endl;
	}
	
	//DIJKSTRA OU PRIM
	if (false)
	{
		//ALLEGRO_BITMAP* graphe = gr.DessinerGraphe(); // a virer
		ALLEGRO_BITMAP* graphe = gr.DessinerSousGraphe(gr.Dijkstra());
		//ALLEGRO_BITMAP* graphe = gr.DessinerSousGraphe(gr.Prim());
		al_set_target_backbuffer(display);

		al_clear_to_color(al_map_rgb(133, 50, 50));
		al_draw_bitmap(graphe, 500, 100, 0);
		//al_draw_text(font, al_map_rgb(0, 0, 0), 500, 80, 0, ssg.c_str());
		//al_draw_text(font, al_map_rgb(0, 0, 0), 700, 80, 0, ((gr.isConnexe(ssg)) ? "co" : "paco"));
		//std::cout << ssg << std::endl;

		al_flip_display();
		al_rest(0.3);
		al_destroy_bitmap(graphe);
	}
	
	//PARETO
	if (true)
	{
		double start = al_get_time();
		std::list<graphePareto>  tousLesSousGraphes{ gr.TriPareto() };

		int width = sqrt((disp_data.height*disp_data.width)/((int)tousLesSousGraphes.size()+1));
		
		if (width > disp_data.height / ((tousLesSousGraphes.size()+1) / (disp_data.width / width)))
			width = disp_data.height / ((tousLesSousGraphes.size() + 1) / (disp_data.width / width));
			
		int i = 0; 
		int x, y;
		al_clear_to_color(al_map_rgb(133, 50, 50));
		for (auto ssg : tousLesSousGraphes)
		{
			ALLEGRO_BITMAP* graphe = gr.DessinerSousGraphePar(ssg);
			al_set_target_backbuffer(display);

			x = i % (disp_data.width / width) * width + (disp_data.width - (disp_data.width / width) * width) / 2;
			y = (i / (disp_data.width / width)) * width + (disp_data.height - (((int)tousLesSousGraphes.size()-1) / (disp_data.width / width) +1) * width)/2 + disp_data.height / 200;
			al_draw_scaled_bitmap(graphe, 0, 0, al_get_bitmap_width(graphe), al_get_bitmap_height(graphe), x, y, width - disp_data.height/100, width - disp_data.height / 100, 0);

			al_destroy_bitmap(graphe);
			i++;
		}
		al_flip_display();
		std::cout << "Temps d'execution : " << al_get_time() - start << std::endl;
	}
	
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
		al_init_timeout(&timeout, 0.06);

		if (al_wait_for_event_until(event_queue, &ev, &timeout) && ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			break;
		}
	}

	al_destroy_display(display);
	al_destroy_event_queue(event_queue);


	return 0;
}