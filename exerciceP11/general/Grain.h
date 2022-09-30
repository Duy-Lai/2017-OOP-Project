#ifndef GRAIN_H
#define GRAIN_H

#include "Obstacle.h"
#include "Milieu.h"

enum TypeGrain { LJ1, LJ2 };

class Grain : public Dessinable {
	public:
	// constructeur & destructeur ====================================================
	Grain(Vecteur3D const& p, Vecteur3D const& v, double m_v, double r, Milieu* m, SupportADessin* sup)
	: Dessinable(sup), position(p), vitesse(v), masse_vol(m_v), rayon(r), milieu(m)
	{
		set_m();
        ajouteForce();
	}
	virtual ~Grain() {}
	// méthodes get ==================================================================
	Vecteur3D get_p() const;
    Vecteur3D get_v() const;
	double get_r() const;
    double get_m() const;
    TypeGrain get_tg() const;
	// méthodes set ==================================================================
	void set_p(Vecteur3D const&);
	void set_v(Vecteur3D const&);
	void set_r(double);
	void set_m();
	void set_milieu(Milieu*);
	// méthodes utilitaires ==========================================================
	void ajouteForce();
	virtual void ajouteForce(Grain* const) = 0;
	virtual void ajouteForce(Obstacle* const) = 0;
	virtual void ajouteForce(Vecteur3D const&) = 0;
	virtual void bouger(double);
	void affiche() const;
	virtual void dessine() = 0;
	protected:
	// attributs =====================================================================
	Vecteur3D position;
	Vecteur3D vitesse;
	double masse_vol;
	double rayon;
	double masse;
	Vecteur3D force;
	Milieu* milieu;
    TypeGrain tg;
	// méthodes internes =============================================================
	double lambda() const;  // calcul du coefficient de frottement, mais PAS la force
};

class GrainLJ : public Grain {
	public:
	GrainLJ(Vecteur3D const& p, Vecteur3D const& v, double m_v, double r, Milieu* m, SupportADessin* sup)
	: Grain(p,v,m_v,r,m,sup)
	{}
	GrainLJ(Grain const& g)
	: Grain(g)
	{}
	virtual ~GrainLJ() {}
	virtual void ajouteForce(Grain* const) override;
	virtual void ajouteForce(Obstacle* const) override;
	virtual void ajouteForce(Vecteur3D const&)override;
	virtual void dessine() = 0;
	protected:
	const double epsilon = 25.0;
	const double sigma = 0.885;
	double forceLJ(double,double,double) const;
};

class GrainLJ_1 : public GrainLJ {
	public:
	GrainLJ_1(Vecteur3D const& p = Vecteur3D(), Vecteur3D const& v = Vecteur3D(), double m_v = 1.0, double r = 0.4, Milieu* m = new Air, SupportADessin* sup = nullptr)
	: GrainLJ(p,v,m_v,r,m,sup)
	{
        tg = LJ1;
	}
	GrainLJ_1(Grain const& g)
	: GrainLJ(g)
    {
        tg = LJ1;
	}
	virtual ~GrainLJ_1() {}
	virtual void dessine() override;
};

class GrainLJ_2 : public GrainLJ {
	public:
	GrainLJ_2(Vecteur3D const& p = Vecteur3D(), Vecteur3D const& v = Vecteur3D(), double m_v = 1.0, double r = 0.4, Milieu* m = new Air, SupportADessin* sup = nullptr)
	: GrainLJ(p,v,m_v,r,m,sup)
    {
        tg = LJ2;
	}
	GrainLJ_2(Grain const& g)
	: GrainLJ(g)
    {
        tg = LJ2;
	}
	virtual ~GrainLJ_2() {}
	virtual void dessine() override;
};

std::ostream& operator<<(std::ostream&, Grain const&);

#endif
