#include <iostream>
#include <vector>
#include "Obstacle.h"
using namespace std;

Vecteur3D Obstacle::get_o() const {
	return origine;
}

Vecteur3D Plan::point_plus_proche(Vecteur3D const& x_i) const {
	return x_i + normale * ((origine - x_i) * normale);
}

void Plan::affiche() const {
	cout << " Plan d'origine " << origine << " et de normale " << normale;
}

double Dalle::get_lo() const {
	return longueur;
}

double Dalle::get_la() const {
	return largeur;
}

Vecteur3D Dalle::get_e_L() const {
	return e_L;
}

Vecteur3D Dalle::get_e_l() const {
	return e_l;
}

Vecteur3D Dalle::point_plus_proche(Vecteur3D const& x_i) const {
	Vecteur3D ppp(Plan::point_plus_proche(x_i));
	double x_kL((ppp-origine) * e_L), x_kl((ppp-origine) * e_l);
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
	e_L.set_z(-(normale.get_x()*e_L.get_x()+normale.get_y()*e_L.get_y())/normale.get_z());
}

vector<Dalle> Brique::get_f() const {
	return faces;
}

Vecteur3D Brique::point_plus_proche(Vecteur3D const& x_i) const {
	Vecteur3D ppp(faces[0].point_plus_proche(x_i));
	for (unsigned int i(1); i < faces.size(); ++i) {
		Vecteur3D temp(faces[i].point_plus_proche(x_i));
		if (temp.norme() < ppp.norme()) ppp = temp;
	}
	return ppp;
}

void Brique::affiche() const {
	cout << " Brique d'origine " << origine << ", de normale " << normale << ", de longueur " << longueur << " selon " << e_L << ", de largeur " << largeur << " selon " << e_l << " et de hauteur " << hauteur;
}

void Brique::dessine() {
	if (support != nullptr) support->dessine(*this);
}

double Sphere::get_r() const {
	return rayon;
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

ostream& operator<<(ostream& cout, Obstacle* const& o) {
	o->affiche();
	return cout;
}
