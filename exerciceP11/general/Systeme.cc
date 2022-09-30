#include <iostream>
#include <vector>
#include "Systeme.h"
using namespace std;

vector<Grain*> Systeme::get_g() const {
	return grains;
}

vector<Dalle*> Systeme::get_d() const {
	return dalles;
}

vector<Brique*> Systeme::get_b() const {
	return briques;
}

vector<Sphere*> Systeme::get_s() const {
	return spheres;
}

void Systeme::ajout_grain(Grain* neu) {
	env.set_milieu(neu);
    grains.push_back(neu);
}

void Systeme::ajout_dalle(Dalle* neu) {
	dalles.push_back(neu);
}

void Systeme::ajout_brique(Brique* neu) {
	briques.push_back(neu);
}

void Systeme::ajout_sphere(Sphere* neu) {
	spheres.push_back(neu);
}

void Systeme::ajout_source(Source* neu) {
	sources.push_back(neu);
}

void Systeme::evolue(double& dt) {
    for (auto& s : sources) s->creation(grains,dt);
    if (grains.size() > 0) {
        test_pas_de_temps(dt);
        for (unsigned int i(0); i < grains.size(); ++i) {
            if (grains[i]->get_p().norme() > 500.0) {
                swap(grains[i],grains.back());
                grains.pop_back();
                --i;
                cout << "## Suppression d'un grain éloigné ##" << endl << endl;
                break;
            }
			env.set_milieu(grains[i]);
            grains[i]->ajouteForce();
            for (auto& d : dalles) {
                grains[i]->ajouteForce(d);
            }
            for (auto& b : briques) {
                grains[i]->ajouteForce(b);
            }
            for (auto& s : spheres) {
                grains[i]->ajouteForce(s);
            }
            for (unsigned int j(0); j < grains.size(); ++j) {
                if (i != j) grains[i]->ajouteForce(grains[j]);
            }
            grains[i]->bouger(dt);
        }
    }
    if (grains.size() > 204) {
        for (auto& s : sources) s->off();
	}
}

void Systeme::vide() {
    for (auto& g : grains) delete g;
    grains.clear();
    for (auto& d : dalles) delete d;
    dalles.clear();
    for (auto& b : briques) delete b;
    briques.clear();
    for (auto& sp : spheres) delete sp;
    spheres.clear();
    for (auto& s : sources) delete s;
    sources.clear();
    env.vide();
}

void Systeme::affiche() const {
	cout << "Le système est constitué des " << grains.size() << " grains suivants :" << endl << endl;
	for (auto& g : grains) {
		cout << *g << endl;
	}
	cout << "et des " << dalles.size() + briques.size() + spheres.size() << " obstacles suivants :" << endl << endl;
	for (auto& d : dalles) {
		cout << d << endl;
	}
	for (auto& b : briques) {
		cout << b << endl;
	}
	for (auto& s : spheres) {
		cout << s << endl;
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
        for (auto& d : dalles) {
            tab[i]->ajouteForce(d);
        }
        for (auto& b : briques) {
            tab[i]->ajouteForce(b);
        }
        for (auto& s : spheres) {
            tab[i]->ajouteForce(s);
        }
        for (unsigned int j(0); j < tab.size(); ++j) {
            if (i != j) tab[i]->ajouteForce(tab[j]);
        }
        tab[i]->bouger(dt);
        if ((tab[i]->get_p()-grains[i]->get_p()).norme() > ecart_max){
            ecart_max = (tab[i]->get_p()-grains[i]->get_p()).norme();
            k = i;
        }
    }
    if (ecart_max > tab[k]->get_r()/2.0) {
        dt = (tab[k]->get_r() / 2.0) / tab[k]->get_v().norme();  // dx = v * dt
    }
}

ostream& operator<<(ostream& cout, Systeme const& sys) {
	sys.affiche();
	return cout;
}
