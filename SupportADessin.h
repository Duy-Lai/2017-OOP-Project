#ifndef SUPPORT_A_DESSIN
#define SUPPORT_A_DESSIN

class GrainLJ_1;
class GrainLJ_2;
class Plan;
class Dalle;
class Brique;
class Sphere;
class Cylindre;
class Systeme;

class SupportADessin {
	public:
	virtual ~SupportADessin() {}
	virtual void dessine(GrainLJ_1 const&) = 0;
	virtual void dessine(GrainLJ_2 const&) = 0;
	virtual void dessine(Plan const&) = 0;
	virtual void dessine(Dalle const&) = 0;
	virtual void dessine(Brique const&) = 0;
	virtual void dessine(Sphere const&) = 0;
	virtual void dessine(Cylindre const&) = 0;
	virtual void dessine(Systeme const&) = 0;
};

#endif
