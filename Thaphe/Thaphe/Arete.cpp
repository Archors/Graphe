/**
 * \file Arrete.cpp
 * \brief Fonctions qui permettent d'effectuer des action sur les aretes
 * \date 21 avril 2019
 *
 * Ce programme utilise Allegro pour afficher un menu à l'écran de l'utilisateur
 * Contient le code de construction d'une arete
 * Contient la fonction pour créer les texts boxes
 * Contient la fonction pour cocher des cases
 */

#include "Arete.h"
 
 /**
  * \fn Arete::Arete(int id, Sommet* s1, Sommet* s2, std::vector<float> poids, bool oriente) : m_id(id), m_oriente(oriente), m_poids(poids)
  * \brief Constructeur de la classe Arete
  *
  * \param id : numéro d'identification de l'arête
  * \param s1 : Premier sommet de l'arête
  * \param s2 : Second sommet de l'arête
  * \param poids : Differents poids de l'arête
  * \param oriente : Si l'arête est orienté ou pas
  */
Arete::Arete(int id, Sommet* s1, Sommet* s2, std::vector<float> poids, bool oriente) : m_id(id), m_oriente(oriente), m_poids(poids)
{
	m_sommets = std::make_pair(s1, s2);
}

/**
  * \fn void Arete::Dessiner(ALLEGRO_BITMAP* bmp)
  * \brief Dessine l'arête sur une Bitmap
  *
  * \param bmp : Bitmap sur laquelle l'arête va être dessiné
  */
void Arete::Dessiner(ALLEGRO_BITMAP* bmp)
{
	al_set_target_bitmap(bmp);
	al_draw_line((float)m_sommets.first->getCoords().getX(), (float)m_sommets.first->getCoords().getY(), (float)m_sommets.second->getCoords().getX(), (float)m_sommets.second->getCoords().getY(), al_map_rgb(170, 170, 170), 5);
	if (m_oriente)
		al_draw_line((float)m_sommets.second->getCoords().getX(), (float)m_sommets.second->getCoords().getY(), (float)(m_sommets.second->getCoords().getX()-(m_sommets.second->getCoords().getX()- m_sommets.first->getCoords().getX())/2.5), (float)(m_sommets.second->getCoords().getY() - (m_sommets.second->getCoords().getY()-m_sommets.first->getCoords().getY())/2.5), al_map_rgb(230, 70, 30), 5);
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

/**
  * \fn std::pair<Sommet*, Sommet*> Arete::getSommets()
  * \brief Getter de Sommet
  *
  * \return : Renvoi une paire de sommet
  */
std::pair<Sommet*, Sommet*> Arete::getSommets()
{
	return m_sommets;
}

/**
  * \fn const float Arete::getPoids(int indice) const
  * \brief Getter de Poids
  * \param indice : Indice du poids à récupérer
  * \return : Renvoi une paire de sommet
  */
const float Arete::getPoids(int indice) const
{
	if (indice > m_poids.size()-1 || indice < 0)
		throw std::runtime_error("Probleme acces poids arete");
	return m_poids[indice];
}

/**
  * \fn const int Arete::getNombrePoids()
  * \brief Getter du nombre de Poids
  * 
  * \return : Renvoi le nombre de poids
  */
const int Arete::getNombrePoids()
{
	return m_poids.size();
}

/**
  * \fn const int Arete::getId() const
  * \brief Getter de l'id de l'arête
  *
  * \return : Renvoi l'id de l'arête
  */
const int Arete::getId() const
{
	return m_id;
}

/**
  * \fn Arete::~Arete()
  * \brief Fonction de destruction d'une arête
  */
Arete::~Arete()
{
}