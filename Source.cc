#include <iostream>
#include <vector>
#include "Source.h"
using namespace std;

void Source::on() {
	etat = true;
}

void Source::off() {
	etat = false;
}

void Source::creation(vector<Grain*>& pack, double dt) {
	if (modele != nullptr and etat) {
		Aleatoire generateur;
		double fraction(debit*dt);
		int nombre(fraction);
		fraction -= nombre;
		if (generateur.uniforme(0.0,1.0) < fraction) ++nombre;
		Grain* neu;
		for (int i(0); i < nombre; ++i) {
			if (modele->get_tg() == LJ1) neu = new GrainLJ_1(*modele);
			if (modele->get_tg() == LJ2) neu = new GrainLJ_2(*modele);
			neu->set_p(position);
			neu->set_v(Vecteur3D(generateur.gaussienne(vitesse_init.get_x(),d_vitesse),generateur.gaussienne(vitesse_init.get_y(),d_vitesse),generateur.gaussienne(vitesse_init.get_z(),d_vitesse)));
			neu->set_r(generateur.gaussienne(modele->get_r(),d_rayon));
			neu->set_m();       // mettre à jour la masse du grain lorsque son rayon est modifié
			neu->bouger(dt);
			pack.push_back(neu);
		}
	}
}
