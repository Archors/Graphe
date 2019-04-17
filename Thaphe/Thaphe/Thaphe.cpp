#include <iostream>
#include "Graphe.h"

int main(int argc, char** argv) 
{
	Graphe gr("cubetown", false);

	//Initialisation d'Allegro
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	display = al_create_display(1800, 1000);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();


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

	//std::cout << tousLesSousGraphes[tousLesSousGraphes.size() - 1] << " : " << ((gr.isConnexe(tousLesSousGraphes[tousLesSousGraphes.size() - 1])) ? "oui" : "fuck") << std::endl;
	if (false)
	{
		double start = al_get_time();
		std::vector<std::string> tousLesSousGraphes;
		tousLesSousGraphes = gr.DeterminerSousGraphe();
		std::cout << "Temps d'execution : " << al_get_time() - start << std::endl;

		for (auto ssg : tousLesSousGraphes)
		{
			ALLEGRO_BITMAP* graphe = gr.DessinerSousGraphe(ssg);
			al_set_target_backbuffer(display);

			al_clear_to_color(al_map_rgb(133, 50, 50));
			al_draw_bitmap(graphe, 500, 100, 0);
			al_draw_text(font, al_map_rgb(0, 0, 0), 500, 80, 0, ssg.c_str());
			//al_draw_text(font, al_map_rgb(0, 0, 0), 700, 80, 0, ((gr.isConnexe(ssg)) ? "co" : "paco"));
			//std::cout << ssg << std::endl;

			al_flip_display();
			al_rest(0.3);
			al_destroy_bitmap(graphe);
		}
	}
	

	if (true)
	{
		ALLEGRO_BITMAP* graphe = gr.DessinerSousGraphe(gr.Dijkstra());
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
	
	if (false)
	{
		double start = al_get_time();
		std::vector<std::string> tousLesSousGraphes;
		tousLesSousGraphes = gr.TriPareto();
		std::cout << "Temps d'execution : " << al_get_time() - start << std::endl;

		for (auto ssg : tousLesSousGraphes)
		{
			ALLEGRO_BITMAP* graphe = gr.DessinerSousGraphe(ssg);
			al_set_target_backbuffer(display);

			al_clear_to_color(al_map_rgb(133, 50, 50));
			al_draw_bitmap(graphe, 500, 100, 0);
			al_draw_text(font, al_map_rgb(0, 0, 0), 500, 80, 0, ssg.c_str());
			//al_draw_text(font, al_map_rgb(0, 0, 0), 700, 80, 0, ((gr.isConnexe(ssg)) ? "co" : "paco"));
			//std::cout << ssg << std::endl;

			al_flip_display();
			al_rest(0.01);
			al_destroy_bitmap(graphe);
		}
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

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.