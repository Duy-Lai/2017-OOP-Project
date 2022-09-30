#include <iostream>
#include "TextViewer.h"

void TextViewer::dessine(GrainLJ_1 const& grain) {
	flot << " Grain L-J de type 1 (" << &grain << ") :";
	grain.affiche();
}

void TextViewer::dessine(GrainLJ_2 const& grain) {
	flot << " Grain L-J de type 2 (" << &grain << ") :";
	grain.affiche();
}

void TextViewer::dessine(Dalle const& dalle) {
	dalle.affiche();
}

void TextViewer::dessine(Brique const& brique) {
	brique.affiche();
}

void TextViewer::dessine(Sphere const& sphere) {
	sphere.affiche();
}

void TextViewer::dessine(Systeme const& systeme) {
	flot << systeme << std::endl;
}
