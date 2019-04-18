#include <iostream>
#include "Graphe.h"

int main(int argc, char** argv) 
{
	Graphe gr("broadway", false, std::bitset<nombreMaxPoids>(2));

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

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_clear_to_color(al_map_rgb(133, 50, 50));

	ALLEGRO_FONT* font;
	font = al_load_font("simple_font.ttf", 30, 0);

	//TOUS LES SOUS GRAPHES CONNEXES AVEC OU SANS CYCLES
	if (false)
	{
		double start = al_get_time();
		std::vector<std::bitset<nombreMaxAretes>> tousLesSousGraphes;
		tousLesSousGraphes = gr.DeterminerSousGraphe(false);
		std::cout << "Temps d'execution : " << al_get_time() - start << std::endl;

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
		std::vector<std::bitset<nombreMaxAretes>> tousLesSousGraphes;
		tousLesSousGraphes = gr.TriPareto();
		std::cout << "Temps d'execution : " << al_get_time() - start << std::endl;

		int width = sqrt(disp_data.height*disp_data.width)/tousLesSousGraphes.size();
		int x = 0; 
		al_clear_to_color(al_map_rgb(133, 50, 50));
		for (auto ssg : tousLesSousGraphes)
		{
			ALLEGRO_BITMAP* graphe = gr.DessinerSousGraphe(ssg);
			al_set_target_backbuffer(display);

			al_draw_scaled_bitmap(graphe, 0, 0, al_get_bitmap_width(graphe), al_get_bitmap_height(graphe), x%(disp_data.width/width)*width, (x/(disp_data.height / width))*width, width, width, 0);
			std::cout << disp_data.width / width << " / " << disp_data.height / width << " (" << disp_data.height << ")\n";
			std::cout << x % (disp_data.width / width)* width << " " << (x / (disp_data.height / width)) * width << std::endl;
			//al_draw_bitmap(graphe, (x%3)*500, (x/3)*500, 0);
			al_draw_text(font, al_map_rgb(0, 0, 0), (x % 3) * 500, (x / 3) * 500+20, 0, ssg.to_string().c_str());
			//al_draw_text(font, al_map_rgb(0, 0, 0), 700, 80, 0, ((gr.isConnexe(ssg)) ? "co" : "paco"));
			//std::cout << ssg << std::endl;

			al_destroy_bitmap(graphe);
			x++;
		}
		al_flip_display();
		al_rest(0.01);
	}
	


	while (1)
	{
		ALLEGRO_EVENT ev;
		ALLEGRO_TIMEOUT timeout;
		al_init_timeout(&timeout, 0.06);

		bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);

		if (get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
	}

	al_destroy_display(display);
	al_destroy_event_queue(event_queue);


	return 0;
}