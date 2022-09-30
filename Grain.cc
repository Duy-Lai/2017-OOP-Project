#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "Grain.h"
using namespace std;

Vecteur3D Grain::get_p() const {
	return position;
}

Vecteur3D Grain::get_v() const {
	return vitesse;
}

double Grain::get_r() const {
	return rayon;
}

double Grain::get_m() const {
	return masse;
}

Case* Grain::get_c() const {
	return caxe;
}

TypeGrain Grain::get_tg() const {
	return tg;
}

void Grain::set_p(Vecteur3D const& p) {
	position = p;
}

void Grain::set_v(Vecteur3D const& v) {
	vitesse = v;
}

void Grain::set_r(double r) {
	rayon = r;
}

void Grain::set_m() {
	masse = (4.0 / 3.0) * M_PI * pow(rayon,3.0) * masse_vol;
}

void Grain::set_case(Case* c) {
	caxe = c;
}

void Grain::set_milieu(Milieu* m) {
	milieu = m;
}

void Grain::ajouteForce() {
	force = Vecteur3D();
	force -= Vecteur3D(0.0,0.0,9.81e3) * masse;  // pesanteur
	force -= vitesse * lambda();  // frottement de l'environnement
	force += Vecteur3D(0.0,0.0,9.81e3) * (4.0/3.0) * M_PI * pow(rayon,3.0) * milieu->get_p();  // poussée d'Archimède
}

void Grain::bouger(double pas) {
	vitesse += (force / masse) * pas;
	position += vitesse * pas;
}

void Grain::affiche() const {
	cout << " Grain L-J de type ";
	if (tg == LJ1) cout << "1";
	if (tg == LJ2) cout << "2";
	cout << " (" << this << ") dans l'" << milieu->get_nom() << " :";
	cout << " m = " << masse << ", r = " << rayon << endl;
	cout << "   f = " << force << endl;
	cout << "   v = " << vitesse << endl;
	cout << "   x = " << position << endl;
}

double Grain::lambda() const {
	if (vitesse.norme() <= (80.0 * milieu->get_n()) / (3.0 * milieu->get_p() * rayon)) {
		return 6.0 * M_PI * rayon * milieu->get_n();
	} else {
		return (9.0/40.0) * M_PI * pow(rayon,2.0) * milieu->get_p() * vitesse.norme();
	}
}

void GrainLJ::ajouteForce(Grain* const autre) {
	Vecteur3D distance(autre->get_p() - position), u(distance.normalise());
	double d_n(distance.norme()), d_min(autre->get_r() + rayon);
	if (d_n < d_min) {
		position -= u * (d_min - d_n);
		vitesse -= u * (vitesse * u);
		distance = autre->get_p() - position;
		u = distance.normalise();
		d_n = distance.norme();
	}
	Vecteur3D force_(u * forceLJ(d_n,rayon,autre->get_r()));
	force += force_;
	autre->ajouteForce(force_ * -1.0);
}

void GrainLJ::ajouteForce(Obstacle* const obs) {
	Vecteur3D distance(obs->point_plus_proche(position) - position), u(distance.normalise());
	double d_n(distance.norme());
	if (d_n < rayon) {
		position -= u * (rayon - d_n);
		vitesse -= u * (vitesse * u);
		distance = obs->point_plus_proche(position) - position;
		u = distance.normalise();
		d_n = distance.norme();
	}
	force += u * 2.0 * forceLJ(d_n,rayon,0.0);
}

void GrainLJ::ajouteForce(Vecteur3D const& v) {
	force += v;
}

double GrainLJ::forceLJ(double distance, double r1, double r2) const {
	double force_lj((24.0 * epsilon) / (sigma * sigma));
	double x(1.09 + (distance - r1 - r2) / sigma);
	if (x <= 1.0) return -force_lj;
	else if (x > 1.0 and x < 2) return force_lj * ((pow(x,6.0) - 2.0) / pow(x,13.0));
	else return 0.0;
}

void GrainLJ_1::dessine() {
	if (support != nullptr) support->dessine(*this);
}

void GrainLJ_2::dessine() {
	if (support != nullptr) support->dessine(*this);
}

ostream& operator<<(ostream& cout, Grain const& g) {
	g.affiche();
	return cout;
}
