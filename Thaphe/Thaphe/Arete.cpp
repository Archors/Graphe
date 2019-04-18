#include "Arete.h"

Arete::Arete(int id, Sommet* s1, Sommet* s2, std::vector<float> poids, bool oriente) : m_id(id), m_oriente(oriente), m_poids(poids)
{
	m_sommets = std::make_pair(s1, s2);
}


void Arete::Dessiner(ALLEGRO_BITMAP* bmp)
{
	al_set_target_bitmap(bmp);
	al_draw_line((float)m_sommets.first->getCoords().getX(), (float)m_sommets.first->getCoords().getY(), (float)m_sommets.second->getCoords().getX(), (float)m_sommets.second->getCoords().getY(), al_map_rgb(170, 170, 170), 5);
	
	ALLEGRO_FONT* font;
	font = al_load_font("simple_font.ttf", 14, 0);

	std::string strPoids = "";
	int i = 0;
	for (auto poids : m_poids)
	{
		std::ostringstream strs;
		strs << poids;
		strPoids = strPoids + ((i)?"; ":"") + strs.str();
		i = 1;
	}
	
	al_draw_text(font, al_map_rgb(30, 30, 30), (m_sommets.first->getCoords().getX()+ m_sommets.second->getCoords().getX())/2, (m_sommets.first->getCoords().getY()+ m_sommets.second->getCoords().getY())/2 - 14, ALLEGRO_ALIGN_CENTRE, strPoids.c_str() );
	al_destroy_font(font);
}

std::pair<Sommet*, Sommet*> Arete::getSommets()
{
	return m_sommets;
}

const float Arete::getPoids(int indice) const
{
	return m_poids[indice];
}

const int Arete::getNombrePoids()
{
	return m_poids.size();
}

const int Arete::getId() const
{
	return m_id;
}

Arete::~Arete()
{
}