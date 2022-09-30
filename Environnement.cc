#include <iostream>
#include "Environnement.h"
using namespace std;

bool Separateur::cote(Vecteur3D const& point) const {
	if (normale.get_x() * (point.get_x() - origine.get_x()) + normale.get_y() * (point.get_y() - origine.get_y()) + normale.get_z() * (point.get_z() - origine.get_z()) >= 0.0) {
		return true;
	}
	return false;
}

void Environnement::set_milieu(Grain* grain) {
	if (milieux.size() == 1) grain->set_milieu(milieux[0]);
	else {
		if (sep->cote(grain->get_p())) grain->set_milieu(milieux[0]);
		else grain->set_milieu(milieux[1]);
	}
}

void Environnement::vide() {
	for (auto& m : milieux) delete m;
	milieux.clear();
	delete sep;
}
