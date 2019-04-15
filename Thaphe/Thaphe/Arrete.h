#include <string>
#include <vector>
#include <unordered_map>
#include "Sommet.h"

class Arrete
{
private:
	const std::string m_id;
	std::vector<float> m_poids;
	std::pair<const Sommet*, const Sommet*> m_sommets; //Si oriente, 1er = d�part, 2nd = arriv�e
	bool oriente;
public:
	Arrete();
	~Arrete();
};

