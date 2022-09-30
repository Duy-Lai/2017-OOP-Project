#include <iostream>
#include "TextViewer.h"

void TextViewer::dessine(GrainLJ_1 const&) {}

void TextViewer::dessine(GrainLJ_2 const&) {}

void TextViewer::dessine(Plan const&) {}

void TextViewer::dessine(Dalle const&) {}

void TextViewer::dessine(Brique const&) {}

void TextViewer::dessine(Sphere const&) {}

void TextViewer::dessine(Cylindre const&) {}

void TextViewer::dessine(Systeme const& systeme) {
	flot << systeme << std::endl;
}
