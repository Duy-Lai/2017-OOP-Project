#ifndef SOURCE_H
#define SOURCE_H

#include "Aleatoire.h"
#include "Grain.h"

class Source {
	public:
	// constructeur & destructeur ====================================================
    Source(Grain* m = nullptr, Vecteur3D const& p = Vecteur3D(), Vecteur3D const& v = Vecteur3D(), double d_v = 5.0, double d_r = 0.01, int d = 1000.0)
	: modele(m), position(p), vitesse_init(v), d_vitesse(d_v), d_rayon(d_r), debit(d)
	{
		etat = true;
	}
	virtual ~Source() {}
	// méthodes ======================================================================
	void on();
	void off();
	void creation(std::vector<Grain*>&, double);
	private:
	Grain* modele;
	Vecteur3D position;
	Vecteur3D vitesse_init;
	double d_vitesse;
	double d_rayon;
	int debit;
	bool etat;
};

std::ostream& operator<<(std::ostream&, Source const&);

#endif
