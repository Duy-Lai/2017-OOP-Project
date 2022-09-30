#include <iostream>
#include <cmath>
#include "Vecteur3D.h"
using namespace std;

double Vecteur3D::get_x() const {
	return x;
}

double Vecteur3D::get_y() const {
	return y;
}

double Vecteur3D::get_z() const {
	return z;
}

void Vecteur3D::set_z(double a) {
	z = a;
}

bool Vecteur3D::operator==(Vecteur3D const& v) const {
	if (x == v.x and y == v.y and z == v.z) return true;
	return false;
}

void Vecteur3D::operator+=(Vecteur3D const& v) {
	x += v.x; y += v.y; z += v.z;
}

void Vecteur3D::operator-=(Vecteur3D const& v) {
	x -= v.x; y -= v.y; z -= v.z;
}

void Vecteur3D::operator*=(double k) {
	x *= k; y *= k; z *= k;
}

void Vecteur3D::operator/=(double k) {
	x /= k; y /= k; z /= k;
}

double Vecteur3D::norme2() const {
	return x*x + y*y + z*z;
}

double Vecteur3D::norme() const {
	return sqrt(norme2());
}

Vecteur3D Vecteur3D::normalise() const {
	if (norme() == 0.0) return *this;
	else return *this/this->norme();
}

ostream& operator<<(ostream& cout, Vecteur3D const& v) {
	cout << "(" << v.get_x() << " " << v.get_y() << " " << v.get_z() << ")";
	return cout;
}

Vecteur3D operator+(Vecteur3D a, Vecteur3D const& b) {
	a += b;
	return a;
}

Vecteur3D operator-(Vecteur3D a, Vecteur3D const& b) {
	a -= b;
	return a;
}

Vecteur3D operator*(Vecteur3D v, double k) {
	v *= k;
	return v;
}

Vecteur3D operator/(Vecteur3D v, double k) {
	v /= k;
	return v;
}

double operator*(Vecteur3D a, Vecteur3D const& b) {
	return a.get_x()*b.get_x() + a.get_y()*b.get_y() + a.get_z()*b.get_z();
}

Vecteur3D operator^(Vecteur3D a, Vecteur3D const& b) {
	return Vecteur3D(a.get_y()*b.get_z() - a.get_z()*b.get_y(), a.get_z()*b.get_x() - a.get_x()*b.get_z(), a.get_x()*b.get_y() - a.get_y()*b.get_x());
}
