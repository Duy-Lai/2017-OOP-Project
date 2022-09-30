#include <iostream>
#include "Systeme.h"
using namespace std;

int main() {
	Systeme s(Environnement(new Eau));
	s.ajout_grain(new GrainLJ_1());
	s.ajout_grain(new GrainLJ_1(Vecteur3D(1.0)));
	s.ajout_grain(new GrainLJ_1(Vecteur3D(0.5,sqrt(3.0)/2.0)));
	s.ajout_grain(new GrainLJ_2(Vecteur3D(0.5,sqrt(3.0)/6.0,sqrt(6.0)/3.0)));
	s.ajout_obstacle(new Plan(Vecteur3D(0.0,0.0,-0.9),Vecteur3D(0.0,0.0,0.1)));
	cout << s << endl;
	s.vide();
	return 0;
}
