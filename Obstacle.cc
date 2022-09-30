#include <iostream>
#include <vector>
#include <cmath>
#include "Obstacle.h"
using namespace std;

Vecteur3D Plan::point_plus_proche(Vecteur3D const& x_i) const {
	return x_i + normale * ((origine - x_i) * normale);
}

void Plan::affiche() const {
	cout << " Plan d'origine " << origine << " et de normale " << normale;
}

void Plan::dessine() {
	if (support != nullptr) support->dessine(*this);
}

Vecteur3D Dalle::point_plus_proche(Vecteur3D const& x_i) const {
	Vecteur3D ppp(Plan::point_plus_proche(x_i));
	double x_kL((ppp - origine) * e_L), x_kl((ppp - origine) * e_l);
	if (x_kL > longueur) {
		ppp -= e_L * (x_kL - longueur);
	} else if (x_kL < 0.0) {
		ppp -= e_L * x_kL;
	}
	if (x_kl > largeur) {
		ppp -= e_l * (x_kl - largeur);
	} else if (x_kl < 0.0) {
		ppp -= e_l * x_kl;
	}
	return ppp;
}

void Dalle::affiche() const {
	cout << " Portion de plan d'origine " << origine << ", de normale " << normale << ", de longueur " << longueur << " selon " << e_L << " et de largeur " << largeur << " selon " << e_l;
}

void Dalle::dessine() {
	if (support != nullptr) support->dessine(*this);
}

void Dalle::set_ortho() {
	e_L.set_z(-(normale.get_x() * e_L.get_x() + normale.get_y() * e_L.get_y()) / normale.get_z());
}

Vecteur3D Brique::point_plus_proche(Vecteur3D const& x_i) const {
	vector<Dalle*> faces;
	faces.push_back(new Dalle(origine,normale,longueur,e_L,largeur,e_l));
	faces.push_back(new Dalle(origine,e_l*-1.0,hauteur,normale*-1.0,longueur,e_L));
	faces.push_back(new Dalle(origine,e_L*-1.0,largeur,e_l,hauteur,normale*-1.0));
	faces.push_back(new Dalle(origine+e_L*longueur,e_L,hauteur,normale*-1.0,largeur,e_l));
	faces.push_back(new Dalle(origine+e_l*largeur,e_l,longueur,e_L,hauteur,normale*-1.0));
	faces.push_back(new Dalle(origine-normale*hauteur,normale*-1.0,largeur,e_l,longueur,e_L));
	Vecteur3D ppp(faces[0]->point_plus_proche(x_i));
	for (unsigned int i(1); i < faces.size(); ++i) {
		Vecteur3D temp(faces[i]->point_plus_proche(x_i));
		if (temp.norme() < ppp.norme()) ppp = temp;
	}
	for (auto& f : faces) delete f;
	faces.clear();
	return ppp;
}

void Brique::affiche() const {
	cout << " Brique d'origine " << origine << ", de normale " << normale << ", de longueur " << longueur << " selon " << e_L << ", de largeur " << largeur << " selon " << e_l << " et de hauteur " << hauteur;
}

void Brique::dessine() {
	if (support != nullptr) support->dessine(*this);
}

Vecteur3D Sphere::point_plus_proche(Vecteur3D const& x_i) const {
	return origine + (x_i - origine).normalise() * rayon;
}

void Sphere::affiche() const {
	cout << " Sphère d'origine " << origine << " et de rayon " << rayon;
}

void Sphere::dessine() {
	if (support != nullptr) support->dessine(*this);
}

Vecteur3D Cylindre::point_plus_proche(Vecteur3D const& x_i) const {
	Vecteur3D e(x_i - origine), e_n(normale * (e * normale)), n(e_n.normalise());
	Vecteur3D e_u(e - e_n), u(e_u.normalise());
	if (abs(e * normale) < hauteur / 2.0) return origine + e_n + u * rayon;
	else {
		double m(e_u.norme());
		if (rayon < m) m = rayon;
		return origine + n * (hauteur / 2.0) + u * m;
	}
}

void Cylindre::affiche() const {
	cout << "Cylindre d'origine " << origine << ", de rayon " << rayon << ", de hauteur " << hauteur << " et de normale " << normale;
}

void Cylindre::dessine() {
	if (support != nullptr) support->dessine(*this);
}

ostream& operator<<(ostream& cout, Obstacle const& o) {
	o.affiche();
	return cout;
}
