#include <iostream>
#include <vector>
#include "Systeme.h"
using namespace std;

unsigned int Systeme::get_g_size() const {
	return grains.size();
}

void Systeme::ajout_grain(Grain* neu) {
	grains.push_back(neu);
}

void Systeme::ajout_obstacle(Obstacle* neu) {
	obstacles.push_back(neu);
}

void Systeme::ajout_source(Source* neu) {
	sources.push_back(neu);
}

void Systeme::evolue(double& dt) {
	for (auto& s : sources) s->creation(grains,dt);
	if (grains.size() > 0) {
		test_pas_de_temps(dt);
		for (unsigned int i(0); i < grains.size(); ++i) {
			if (grains[i]->get_p().norme() > 100.0) {
				swap(grains[i],grains.back());
				grains.pop_back();
				--i;
				cout << "## Suppression d'un grain éloigné ##" << endl << endl;
				break;
			}
			env.set_milieu(grains[i]);
			// verifie_cree_cases(grains[i]);
			grains[i]->ajouteForce();
			for (auto& o : obstacles) {
				grains[i]->ajouteForce(o);
			}
			/*for (auto& g : grains[i]->get_c()->get_g()) {
				grains[i]->ajouteForce(g);
			}
			for (auto& c : grains[i]->get_c()->get_v()) {
				for (auto& g : c->get_g()) grains[i]->ajouteForce(g);
			}*/
			for (unsigned int j(0); j < grains.size(); ++j) {
				if (i != j) grains[i]->ajouteForce(grains[j]);
			}
			grains[i]->bouger(dt);
		}
	}
    if (grains.size() > 250) {
		for (auto& s : sources) s->off();
	}
}

void Systeme::vide() {
	for (auto& g : grains) delete g;
	grains.clear();
	for (auto& o : obstacles) delete o;
	obstacles.clear();
	for (auto& s : sources) delete s;
	sources.clear();
	// for (auto& c : cases) delete c;
	cases.clear();
	env.vide();
}

void Systeme::affiche() const {
	cout << "Le système est constitué des " << grains.size() << " grains suivants :" << endl << endl;
	for (auto& g : grains) {
		cout << *g << endl;
	}
	cout << "et des " << obstacles.size() << " obstacles suivants :" << endl << endl;
	for (auto& o : obstacles) {
		cout << *o << endl;
	}
}

void Systeme::dessine() {
	if (support != nullptr) support->dessine(*this);
}

void Systeme::test_pas_de_temps(double& dt) {
	unsigned int k(0);
	double ecart_max(0.0);
	vector<Grain*> tab;
	for (auto& g : grains) {
		if (g->get_tg() == LJ1) tab.push_back(new GrainLJ_1(*g));
		if (g->get_tg() == LJ2) tab.push_back(new GrainLJ_2(*g));
	}
	for (unsigned int i(0); i < tab.size(); ++i) {
		env.set_milieu(tab[i]);
		tab[i]->ajouteForce();
		for (auto& o : obstacles) {
			tab[i]->ajouteForce(o);
		}
		for (unsigned int j(0); j < tab.size(); ++j) {
			if (i != j) tab[i]->ajouteForce(tab[j]);
		}
		tab[i]->bouger(dt);
		if ((tab[i]->get_p()-grains[i]->get_p()).norme() > ecart_max){
			ecart_max = (tab[i]->get_p() - grains[i]->get_p()).norme();
			k = i;
		}
	}
	if (ecart_max > tab[k]->get_r() / 2.0) {
		dt = ( tab[k]->get_r() / 2.0 ) / tab[k]->get_v().norme();  // dx = v * dt
	}
	for (auto& g : tab) {
		delete g;
	}
	tab.clear();
}

void Systeme::verifie_cree_cases(Grain* g) {
	int x(g->get_p().get_x()), y(g->get_p().get_y()), z(g->get_p().get_z());
	Case* cas(new Case(x,y,z));
	bool in(false);
	for (auto& c : cases) {
		if (*c == *cas) {
			in = true;
			delete cas;
			break;
		}
	}
	if (in == false) {
		for (auto& g : grains) *cas > g;
		cases.push_back(cas);
	}
}

ostream& operator<<(ostream& cout, Systeme const& sys) {
	sys.affiche();
	return cout;
}
