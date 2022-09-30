#ifndef TEXT_VIEWER_H
#define TEXT_VIEWER_H

#include <iostream>
#include "Systeme.h"

class TextViewer : public SupportADessin {
	public:
	TextViewer(std::ostream& flot)
    : flot(flot)
	{}
	virtual ~TextViewer() {}
	virtual void dessine(GrainLJ_1 const&) override;
	virtual void dessine(GrainLJ_2 const&) override;
	virtual void dessine(Plan const&) override;
	virtual void dessine(Dalle const&) override;
	virtual void dessine(Brique const&) override;
	virtual void dessine(Sphere const&) override;
	virtual void dessine(Cylindre const&) override;
	virtual void dessine(Systeme const&) override;
	private:
	std::ostream& flot;
};

#endif
