#include <iostream>
#include "TextViewer.h"
using namespace std;

int main() {
	TextViewer ecran(cout);
    Systeme s(Environnement(new Air, new Eau, new Separateur(Vecteur3D(0.0,0.0,3.0),Vecteur3D(0.0,0.0,270.0))),&ecran);
	s.ajout_dalle(new Dalle(Vecteur3D(-90.0,-23.0,290.0),Vecteur3D(0.0,0.0,0.1),180.0,150.0,Vecteur3D(4.0,0.0,3.0)));
	s.ajout_sphere(new Sphere(Vecteur3D(-3.0,50.0,270.0),52.0));
    s.ajout_source(new Source(new GrainLJ_1(Vecteur3D(),Vecteur3D(),0.5),Vecteur3D(-3.0,50.0,427.0),Vecteur3D(0.0,54.0,429.0)));
    double dt(0.01), t(0.0);
    while (t <= 0.7) {
		cout << "======================  t = " << t << "  ======================" << endl << endl;
        s.dessine();
        s.evolue(dt);
        if (s.get_g().size() == 0) break;
		t += dt;
    }
    s.vide();
	return 0;
}
