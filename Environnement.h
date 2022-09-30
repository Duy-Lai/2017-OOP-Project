#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

#include <vector>
#include "Grain.h"

class Separateur {
	public:
	Separateur(Vecteur3D const& n, Vecteur3D const& o)
	: normale(n.normalise()), origine(o)
	{}
	virtual ~Separateur() {}
	bool cote(Vecteur3D const&) const; // retourner true si les coordonnées sont du même côté que le vecteur normal et false sinon
	private:
	Vecteur3D normale;
	Vecteur3D origine;
};

class Environnement {
	public:
	Environnement(Milieu* const m1)
	{
		milieux.push_back(m1);
		sep = nullptr;
	}
	Environnement(Milieu* const m1, Milieu* const m2, Separateur* const s)
	: sep(s)
	{
		milieux.push_back(m1);
		milieux.push_back(m2);
	}
	~Environnement() {}
	void set_milieu(Grain* grain);
	void vide();
	private:
	std::vector<Milieu*> milieux;
	Separateur* sep;
};

#endif
