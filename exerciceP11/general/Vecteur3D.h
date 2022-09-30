#ifndef VECTEUR_H
#define VECTEUR_H

class Vecteur3D {
	public:
	// constructeur & destructeur ====================================================
	Vecteur3D(double a = 0.0, double b = 0.0, double c = 0.0)
	: x(a), y(b), z(c)
	{}
	virtual ~Vecteur3D() {}
	// méthodes get & set ==================================================================
	double get_x() const;
	double get_y() const;
	double get_z() const;
	void set_z(double);
	// méthodes utilitaires ==========================================================
	double norme2() const;
	double norme() const;
	Vecteur3D normalise() const;
	// surcharges d'operateur ========================================================
	bool operator==(Vecteur3D const&) const;
	void operator+=(Vecteur3D const&);
	void operator-=(Vecteur3D const&);
	void operator*=(double);
	void operator/=(double);
	private:
	double x;
	double y;
	double z;
};

std::ostream& operator<<(std::ostream&, Vecteur3D const&);
Vecteur3D operator+(Vecteur3D, Vecteur3D const&);
Vecteur3D operator-(Vecteur3D, Vecteur3D const&);
Vecteur3D operator*(Vecteur3D, double);
double operator*(Vecteur3D, Vecteur3D const&);
Vecteur3D operator/(Vecteur3D, double);
Vecteur3D operator^(Vecteur3D, Vecteur3D const&);

#endif
