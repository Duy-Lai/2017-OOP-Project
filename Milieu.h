#ifndef MILIEU_H
#define MILIEU_H

class Milieu {
	public:
	virtual ~Milieu() {}
	virtual std::string get_nom() const = 0;
	virtual double get_p() const = 0;   // masse volumique
	virtual double get_n() const = 0;   // viscosité dynamique
};

class Air : public Milieu {
	public:
	virtual ~Air() {}
	virtual std::string get_nom() const override { return "air"; }
	virtual double get_p() const override { return 1.3e-3; }
	virtual double get_n() const override { return 1.8e-2; }
};

class Eau : public Milieu {
	public:
	virtual ~Eau() {}
	virtual std::string get_nom() const override { return "eau"; }
	virtual double get_p() const override { return 1.0; }
	virtual double get_n() const override { return 1.0; }
};

#endif
