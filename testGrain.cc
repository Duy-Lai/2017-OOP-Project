#include <iostream>
#include "Grain.h"
using namespace std;

int main() {
	GrainLJ_1 g1(Vecteur3D(1.0,2.0,3.0), Vecteur3D(4.0,5.0,6.0), 1.3, 0.56), g2(g1), g3;
	cout << g1 << endl << g2 << endl << g3 << endl;
	return 0;
}
