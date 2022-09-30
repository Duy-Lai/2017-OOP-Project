#ifndef SYSTEME_H
#define SYSTEME_H

#include "Source.h"
#include "Environnement.h"

class Systeme : public Dessinable {
	public:
	Systeme(Environnement e, SupportADessin* sup = nullptr)
	: Dessinable(sup), env(e)
	{}
    virtual ~Systeme() {}
	std::vector<Grain*> get_g() const;
	std::vector<Dalle*> get_d() const;
	std::vector<Brique*> get_b() const;
    std::vector<Sphere*> get_s() const;
    void ajout_grain(Grain*);
	void ajout_dalle(Dalle*);
	void ajout_brique(Brique*);
	void ajout_sphere(Sphere*);
	void ajout_source(Source*);
	void evolue(double&);
    void vide();
	void affiche() const;
	virtual void dessine() override;
	private:
	std::vector<Grain*> grains;
	std::vector<Dalle*> dalles;
	std::vector<Brique*> briques;
	std::vector<Sphere*> spheres;
	std::vector<Source*> sources;
	Environnement env;
    Systeme(Systeme const&) = delete;
    void operator=(Systeme const&) = delete;
	void test_pas_de_temps(double&);
};

std::ostream& operator<<(std::ostream&, Systeme const&);

#endif
