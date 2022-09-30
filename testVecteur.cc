#include <iostream>
#include "Vecteur3D.h"
using namespace std;

int main() {
	Vecteur3D v1(1.0,2.0,-0.1), v2(2.6,3.5,4.1), v3(v1), v4;
	cout << "Vecteur3D 1 : " << v1 << "         (v1)" << endl;
	cout << "Vecteur3D 2 : " << v2 << "      (v2)" << endl;
	cout << "Vecteur3D 3 : " << v3 << "         (v3)" << endl;
	cout << "Vecteur3D 4 : " << v4 << "            (v4)" << endl;
	cout << "Le vecteur 1 est ";
	if (v1 == v2) {
		cout << "égal au";
	} else {
		cout << "différent du";
	}
	cout << " vecteur 2," << endl << "et est ";
	if (v1 == v3) {
		cout << "égal au";
	} else {
		cout << "différent du";
	}
	cout << " vecteur 3." << endl;
	cout << "v1 + v2 = " << v1 + v2 << endl;
	cout << "v3 - v2 = " << v3 - v2 << endl;
	cout << "v1 * 2 = " << v1 * 2.0 << endl;
	cout << "v2 * v3 = " << v2 * v3 << endl;
	cout << "v1 ^ v2 = " << (v1 ^ v2) << endl;
	cout << "||v2||^2 = " << v2.norme2() << endl;
	cout << "||v2|| = " << v2.norme() << endl;
	return 0;
}
