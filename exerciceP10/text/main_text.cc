#include <iostream>
#include "TextViewer.h"
using namespace std;

int main() {
	TextViewer ecran(cout);
    Systeme s(Environnement(new Air),&ecran);
    s.ajout_grain(new GrainLJ_1());
    s.ajout_grain(new GrainLJ_1(Vecteur3D(1.0)));
    s.ajout_grain(new GrainLJ_1(Vecteur3D(0.5,sqrt(3.0)/2.0)));
    s.ajout_grain(new GrainLJ_2(Vecteur3D(0.5,sqrt(3.0)/6.0,sqrt(6.0)/3.0)));
    s.ajout_dalle(new Dalle(Vecteur3D(4.0,-4.0,-0.9),Vecteur3D(0.0,0.0,0.1),8.0,8.0));
    double dt(0.01), t(0.0);
    while (t <= 2.0) {
		cout << "======================  t = " << t << "  ======================" << endl << endl;
        s.dessine();
        s.evolue(dt);
        if (s.get_g().size() == 0) break;
		t += dt;
	}
    s.vide();
	return 0;
}
