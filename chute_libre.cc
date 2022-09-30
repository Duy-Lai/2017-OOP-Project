#include <iostream>
#include "TextViewer.h"
using namespace std;

int main() {
	TextViewer ecran(cout);
	Systeme s(Environnement(new Air),&ecran);
	s.ajout_grain(new GrainLJ_1(Vecteur3D(),Vecteur3D(5.0,0.0,7.0)));
	double dt(0.01), t(0.0);
	while (t <= 0.2) {
		cout << "======================  t = " << t << "  ======================" << endl << endl;
		s.dessine();
		s.evolue(dt);
        if (s.get_g_size() == 0) break;
		t += dt;
	}
	s.vide();
	return 0;
}
