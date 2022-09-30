#ifndef CASE_H
#define CASE_H

#include <vector>
#include <array>

class Grain;

class Case {
	public:
	Case(int a, int b, int c)
	: x(a), y(b), z(c)
	{}
	int get_x() const;
	int get_y() const;
	int get_z() const;
	std::vector<Grain*> get_g() const;
	std::vector<Case*> get_v() const;
	void operator>(Grain* const);
	bool operator==(Case const&) const;
	private:
	int x;
	int y;
	int z;
	std::vector<Grain*> grains;
	std::vector<Case*> voisines;
};

#endif
