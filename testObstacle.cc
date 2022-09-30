#include <iostream>
#include <vector>
#include "Obstacle.h"
using namespace std;

int main() {
	vector<Obstacle*> plans;
	plans.push_back(new Plan(Vecteur3D(),Vecteur3D(0.0,0.0,2.0)));
	plans.push_back(new Plan(Vecteur3D(),Vecteur3D(0.0,1.0)));
	plans.push_back(new Plan(Vecteur3D(),Vecteur3D(1.0)));
	plans.push_back(new Plan(Vecteur3D(),Vecteur3D(1.0,1.0,1.0)));
	plans.push_back(new Plan(Vecteur3D(1.0,2.0,3.0),Vecteur3D(1.1,3.3,2.2)));
	vector<Vecteur3D*> points;
	points.push_back(new Vecteur3D(0.0,7.0));
	points.push_back(new Vecteur3D(0.0,0.0,10.0));
	points.push_back(new Vecteur3D(2.0));
	points.push_back(new Vecteur3D(5.0,-4.0,6.0));
	for (auto& p : plans) {
		cout << *p << " :" << endl;
		for (auto& q : points) {
			cout << "  distance à " << *q << " : " << p->point_plus_proche(*q) << endl;
		}
		cout << endl;
	}
	for (auto& p : plans) delete p;
	plans.clear();
	for (auto& q : points) delete q;
	points.clear(); 
	return 0;
}
