#include <iostream>
#include "Case.h"
#include "Grain.h"
using namespace std;

int Case::get_x() const {
	return x;
}

int Case::get_y() const {
	return y;
}

int Case::get_z() const {
	return z;
}

vector<Grain*> Case::get_g() const {
	return grains;
}

vector<Case*> Case::get_v() const {
	return voisines;
}

void Case::operator>(Grain* const g) {
	int x_(g->get_p().get_x()), y_(g->get_p().get_y()), z_(g->get_p().get_z());
	if (x_ == x and y_ == y and z_ == z) {
		grains.push_back(g);
		g->set_case(this);
	}
}

bool Case::operator==(Case const& c) const {
	if (x == c.x and y == c.y and z == c.z) return true;
	return false;
}
