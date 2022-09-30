#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <vector>
#include "Dessinable.h"
#include "SupportADessin.h"
#include "Vecteur3D.h"

class Obstacle : public Dessinable {
	public:
	// constructeur & destructeur ====================================================
	Obstacle(Vecteur3D const& o, SupportADessin* sup)
	: Dessinable(sup), origine(o)
	{}
	virtual ~Obstacle() {}
	// méthodes ======================================================================
	Vecteur3D get_o() const;
	virtual Vecteur3D point_plus_proche(Vecteur3D const&) const = 0;
	virtual void affiche() const = 0;
	virtual void dessine() = 0;
	protected:
	Vecteur3D origine;
};

class Plan : public virtual Obstacle {
	public:
	// constructeur & destructeur ====================================================
	Plan(Vecteur3D const& o = Vecteur3D(), Vecteur3D const& n = Vecteur3D(1.0), SupportADessin* sup = nullptr)
	: Obstacle(o,sup), normale(n.normalise())
	{}
	virtual ~Plan() {}
	// méthodes ======================================================================
	virtual Vecteur3D point_plus_proche(Vecteur3D const&) const override;
	virtual void affiche() const override;
	protected:
	Vecteur3D normale;
};

class Dalle : public Plan {
	public:
	// constructeur & destructeur ====================================================
	Dalle(Vecteur3D const& o = Vecteur3D(), Vecteur3D const& n = Vecteur3D(1.0), double l1 = 1.0, double l2 = 1.0, Vecteur3D const& e = Vecteur3D(0.0,1.0), SupportADessin* sup = nullptr)
    : Obstacle(o,sup), Plan(o,n,sup), longueur(l1), largeur(l2), e_L(e.normalise())
	{
		if (e_L * normale != 0.0) set_ortho();
		e_L = e_L.normalise();
		e_l = (normale ^ e_L);
		e_l = e_l.normalise();
	}
	Dalle(Vecteur3D const& o = Vecteur3D(), Vecteur3D const& n = Vecteur3D(1.0), double l1 = 1.0, Vecteur3D const& e1 = Vecteur3D(0.0,1.0), double l2 = 1.0, Vecteur3D const& e2 = Vecteur3D(0.0,0.0,1.0), SupportADessin* sup = nullptr)
    : Obstacle(o,sup), Plan(o,n,sup), longueur(l1), largeur(l2), e_L(e1), e_l(e2)
	{}
	virtual ~Dalle() {}
	// méthodes ======================================================================
	double get_lo() const;
	double get_la() const;
	Vecteur3D get_e_L() const;
	Vecteur3D get_e_l() const;
	virtual Vecteur3D point_plus_proche(Vecteur3D const&) const override;
	virtual void affiche() const override;
	virtual void dessine() override;
	protected:
	double longueur;
	double largeur;
	Vecteur3D e_L;
	Vecteur3D e_l;
	private:
	void set_ortho();
};

class Brique : public Dalle {
	public:
	Brique(Vecteur3D const& o = Vecteur3D(), Vecteur3D const& n = Vecteur3D(1.0), double h = 1.0, double l1 = 1.0, double l2 = 1.0, Vecteur3D const& e = Vecteur3D(0.0,1.0), SupportADessin* sup = nullptr)
    : Obstacle(o,sup), Dalle(o,n,l1,l2,e,sup), hauteur(h)
	{
		faces.push_back(Dalle(origine,normale,longueur,e_L,largeur,e_l));
		faces.push_back(Dalle(origine,e_l*-1.0,hauteur,normale*-1.0,longueur,e_L));
		faces.push_back(Dalle(origine,e_L*-1.0,largeur,e_l,hauteur,normale*-1.0));
		faces.push_back(Dalle(origine+e_L*longueur,e_L,hauteur,normale*-1.0,largeur,e_l));
		faces.push_back(Dalle(origine+e_l*largeur,e_l,longueur,e_L,hauteur,normale*-1.0));
		faces.push_back(Dalle(origine-normale*hauteur,normale*-1.0,largeur,e_l,longueur,e_L));
	}
	virtual ~Brique() {}
	// méthodes ======================================================================
	std::vector<Dalle> get_f() const;
	virtual Vecteur3D point_plus_proche(Vecteur3D const&) const override;
	virtual void affiche() const override;
	virtual void dessine() override;
	private:
	double hauteur;
	std::vector<Dalle> faces;
};

class Sphere : public virtual Obstacle {
	public:
	// constructeur & destructeur ====================================================
	Sphere(Vecteur3D const& o = Vecteur3D(), double r = 1.0, SupportADessin* sup = nullptr)
	: Obstacle(o,sup), rayon(r)
	{}
	virtual~Sphere() {}
	// méthodes ======================================================================
	double get_r() const;
	virtual Vecteur3D point_plus_proche(Vecteur3D const&) const override;
	virtual void affiche() const override;
	virtual void dessine() override;
	protected:
	double rayon;
};

class Cylindre : public Plan, public Sphere {
    public:
    // constructeur & destructeur ====================================================
    Cylindre(Vecteur3D const& o = Vecteur3D(), double r = 1.0, double h = 1.0, Vecteur3D const& n = Vecteur3D(1.0), SupportADessin* sup = nullptr)
    : Obstacle(o,sup), Plan(o,n,sup), Sphere(o,r,sup), hauteur(h)
    {}
    virtual ~Cylindre() {}
    // méthodes ======================================================================
    virtual Vecteur3D point_plus_proche(Vecteur3D const&) const override;
    virtual void affiche() const override;
    virtual void dessine() override;
    private:
    double hauteur;
};

std::ostream& operator<<(std::ostream&, Obstacle* const&);

#endif
