#ifndef SYSTEME_H
#define SYSTEME_H

#include "Source.h"
#include "Environnement.h"

class Systeme : public Dessinable {
	public:
	// constructeur et destructeur =================================================
	Systeme(Environnement e, SupportADessin* sup = nullptr)
	: Dessinable(sup), env(e)
	{}
	virtual ~Systeme() {}
	// méthodes utilitaires ========================================================
	unsigned int get_g_size() const;
	void ajout_grain(Grain*);
	void ajout_obstacle(Obstacle*);
	void ajout_source(Source*);
	void evolue(double&);
	void vide();
	void affiche() const;
	virtual void dessine() override;
	private:
	// attributs ===================================================================
	std::vector<Grain*> grains;
	std::vector<Obstacle*> obstacles;
	std::vector<Source*> sources;
	std::vector<Case*> cases;
	Environnement env;
	// d'autres choses privées =====================================================
	Systeme(Systeme const&) = delete;
	void operator=(Systeme const&) = delete;
	void test_pas_de_temps(double&); // vérifier et modifier le pas de temps appliqué au système
	void verifie_cree_cases(Grain*); // vérifier si le grain pointé est déjà dans une case et créer une sinon
};

std::ostream& operator<<(std::ostream&, Systeme const&);

#endif
