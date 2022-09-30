#include <iostream>
#include <vector>
#include "Source.h"
using namespace std;

int main() {
	GrainLJ_2 modele(Vecteur3D(3.0,1.0,6.0), Vecteur3D(), 2.453, 0.25);
	Source s(&modele,Vecteur3D(9.4,12.37,-5.04),Vecteur3D(36.05,-1.78,13.69),4.6,0.012,1284.0);
	vector<Grain*> pack;
	s.creation(pack,0.02);
	for (auto& grain : pack) {
		cout << *grain << endl;
	}
	return 0;
}
